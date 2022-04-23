#include "pch.h"
#include "CShield.h"


CShield::CShield()
{
}

CShield::~CShield()
{
	Release();
}

void CShield::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fDiagonal = 100.f;
	m_fSpeed = .5f;
}

int CShield::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	INFO sInfo = m_pOwner->Get_Info();

	m_fAngle += m_fSpeed;

	sInfo.fX += m_fDiagonal * cosf((m_fAngle * PI) / 180.f);
	sInfo.fY -= m_fDiagonal * sinf((m_fAngle * PI) / 180.f);

	m_tInfo.fX = sInfo.fX;
	m_tInfo.fY = sInfo.fY;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CShield::Late_Update(void)
{
	if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right ||
		100 >= m_tRect.top || WINCY - 100 <= m_tRect.bottom)
		m_bDead = true;
}

void CShield::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield::Release(void)
{

}

void CShield::OnCollision()
{
	
}