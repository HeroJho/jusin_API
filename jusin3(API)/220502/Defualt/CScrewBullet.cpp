#include "pch.h"
#include "CScrewBullet.h"


CScrewBullet::CScrewBullet()
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

	m_fSpeed = 5.f;

	m_fRotAngle = 0.f;
	m_fRotSpeed = 30.f;
	m_fRotDistance = 20.f;

	m_bStart = true;
}

int CScrewBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 처음에 한해서 센터의 좌표를 초기화.(처음의 m_tInfo 좌표는 포대 끝 위치)
	if (m_bStart)
	{
		m_ptCenter.x = (long)m_tInfo.fX;
		m_ptCenter.y = (long)m_tInfo.fY;
		m_bStart = false;
	}

	// 센터를 발사 방향으로 좌표 이동
	m_ptCenter.x += long(m_fSpeed * cosf((m_fAngle * PI) / 180.f));
	m_ptCenter.y -= long(m_fSpeed * sinf((m_fAngle * PI) / 180.f));

	// 센터를 기준으로 몇 도 회전할 건지
	m_fRotAngle += m_fRotSpeed;

	// 총알의 위치는 센터를 기준으로 n도 회전한 위치
	m_tInfo.fX = m_ptCenter.x + m_fRotDistance * cosf((m_fRotAngle)*PI / 180.f);
	m_tInfo.fY = m_ptCenter.y - m_fRotDistance * sinf((m_fRotAngle)*PI / 180.f);

	Update_Rect();

	return OBJ_NOEVENT;
}

void CScrewBullet::Late_Update(void)
{

}

void CScrewBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CScrewBullet::Release(void)
{

}
