#include "pch.h"
#include "CScrewBullet.h"

CScrewBullet::CScrewBullet()
	: m_satTheta(0.f)
{
}

CScrewBullet::~CScrewBullet()
{
	Release();
}

void CScrewBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fDiagonal = 20.f;
	m_fSpeed = 10.f;
}

int CScrewBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_satTheta += m_fSpeed;

	m_tCenter.x += 2.f * cosf((m_fAngle * PI) / 180.f);
	m_tCenter.y -= 2.f * sinf((m_fAngle * PI) / 180.f);

	m_tInfo.fX = m_tCenter.x + m_fDiagonal * cosf((m_satTheta * PI) / 180.f);
	m_tInfo.fY = m_tCenter.y + m_fDiagonal * sinf((m_satTheta * PI) / 180.f);


	Update_Rect();

	return OBJ_NOEVENT;
}

void CScrewBullet::Late_Update(void)
{
	if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right ||
		100 >= m_tRect.top || WINCY - 100 <= m_tRect.bottom)
		m_bDead = true;
}

void CScrewBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CScrewBullet::Release(void)
{

}

void CScrewBullet::OnCollision()
{

}