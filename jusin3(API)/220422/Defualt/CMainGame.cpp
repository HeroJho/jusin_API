#include "pch.h"

#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CollisionMgr.h"

CMainGame::CMainGame()
	: m_hDc(nullptr)
	, m_dwTime(GetTickCount())
	, m_rcWall{ 100, 100, WINCX - 100, WINCY - 100 }
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	m_iFPS = 0;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	// main�� �ִ� hWnd ID ���� ���´�
	m_hDc = GetDC(g_hWnd);

	// �߻� ���丮 ������ ����ؼ� Player ����.
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create());

	// ���� Player���� Main�� �Ѿ� ����Ʈ�� �Ѱ��ش�.
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_BulletList(&m_ObjList[OBJ_BULLET]);
	
}



void CMainGame::Update(void)
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
}

void CMainGame::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}

	CollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
}

void CMainGame::Render(void)
{
	// ū �׸� �׷��� ���� ������ �׸��� �����ش�.
	Rectangle(m_hDc, 0, 0, WINCX, WINCY);
	Rectangle(m_hDc, m_rcWall.left, m_rcWall.top, m_rcWall.right, m_rcWall.bottom);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_hDc);
	}


	// ��Ʈ ���

	//lstrcpy(m_szFPS, L"Hello");
	//TextOut(m_hDC, 50, 50, m_szFPS, lstrlen(m_szFPS));
	// 1. dc 2, 3. ����� ������ left, top ��ǥ, 4. ����� ���ڿ� 5. ���ڿ� ���� ũ��

	//RECT rc{ 0, 0, 50, 50 };
	//DrawText(m_hDC, m_szFPS, lstrlen(m_szFPS), &rc, DT_RIGHT);
	// 1. dc 2. ����� ���ڿ� 3. ���ڿ� ���� ũ�� 4. ����� ��Ʈ �ּ�, 5. ��� �ɼ�

	//TCHAR	szBuff[32] = L"";
	// �Ҽ��� �ڸ� ����� �Ұ����ϴ�. winapi ���̺귯������ �����ϴ� �Լ�
	//wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());

	// visual c++ ���̺귯������ ����(��� ���� ���ڸ� ����)
	//swprintf_s(szBuff, L"Bullet : %f", 3.14f);
	//TextOut(m_hDC, 50, 50, szBuff, lstrlen(szBuff));


	// FPS ���
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_hDc);
}







// �����ϼ� ����

// �浹ó��
//	������Ʈ >> �浹ó�� �ȵǴ� ������Ʈ�� �ִ�  X

// �ذ�
//	�浹 ó���� �ϴ� Ŭ������ �ʿ��� �� ����.
//	�浹 ó���� ����ϴ� Ŭ���� �Ŵ����� �����.

// ������ ������Ʈ �迭�� ���� �ּ� ������ ������ ���Ѵ�


// ����
// 1. �ﰢ�Լ� �����ϱ� (cos, sin, tan).
// 2. �÷��̾� ���� �߰��ϰ� ȸ���� ���Ѷ�.
// 3. ������ �������� ���ٿ� ������ �����δ�.


// 4�� ���� ���� ���� ��μ�
// ���� �ð� ���ϱ�
// ���Ϻ��� ����
// ȭ���Ͽ� ������ ��ǥ


// 1. ���̽��극��ŷ
// 2. ��¥ �ΰ��� ��� üũ (�Ѽ� ���°� �� �� ������)


// �ּ� 8�ð� (�����ð� ����)
// 1.��ǥ�ڷ�: ���ǥ(�����ϰ� ���)
// 2.���Һд�(�����ϰ�)
// 3.������ ����(�갡 �÷��̾� ������ ��ȹ�߰� ������ �Ѿ˻� ���� ���ߴ� ������ 30��)
// 4.������ �� ����x (������ ������ �̽��� ���ַ�)
// 5.ȸ�ǳ��� ���⸦ �̾Ƴ��� ��

// ���� ȸ���� ����ó��!!