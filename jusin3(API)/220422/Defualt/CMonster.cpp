#include "pch.h"
#include "CMonster.h"


CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fX = 400.f;		// 중점 X
	m_tInfo.fY = 150.f;		// 중점 Y

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 1.f;

	m_eDir = DIR_LEFT;
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	}
	

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	// 왼 오 벽에 닿았냐
	if (100 >= m_tRect.left)
		m_eDir = DIR_RIGHT;
	else if (WINCX - 100 <= m_tRect.right)
		m_eDir = DIR_LEFT;	

}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{

}

void CMonster::OnCollision()
{
	m_bDead = true;
}
