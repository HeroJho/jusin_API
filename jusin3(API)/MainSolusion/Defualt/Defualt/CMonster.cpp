#include "pch.h"
#include "CMonster.h"


CMonster::CMonster()
	: m_pTarget(nullptr)
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

	double dY = m_pTarget->Get_Info().fY - m_tInfo.fY;

	if (0.f < dY)
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle);
		m_tInfo.fY += m_fSpeed * sinf(m_fAngle);
	}
	else
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle);
		m_tInfo.fY += -m_fSpeed * sinf(m_fAngle);
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	double dX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	double dY = m_pTarget->Get_Info().fY - m_tInfo.fY;

	float dis = sqrt((dX * dX) + (dY * dY));
    m_fAngle = acosf(dX / dis);
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


// 내일 감상평 마이크 사용