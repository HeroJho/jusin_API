#include "pch.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;
	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth = abs(pObj->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = abs(pObj->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	if ((eID >= OBJ_END) || (nullptr == pObj))
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}

	CollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]);
	CollisionMgr::Collision_Sphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}
}