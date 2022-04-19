#include "pch.h"
#include "CBullet.h"
#include "CMainGame.h"


CBullet::CBullet()
	: m_pOwner(nullptr)
	, m_eDir(DIR::NONE)
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	// 총알 생성 위치는 플레이어
	m_tInfo.fX = m_pOwner->GetInfo().fX;
	m_tInfo.fY = m_pOwner->GetInfo().fY;

	m_tInfo.fCX = 50.f;	// 총알 가로 사이즈
	m_tInfo.fCY = 50.f;	// 총알 세로 사이즈

	m_fSpeed = 10.f;
}

void CBullet::Update(void)
{
	// 위쪽에서 중점 또는 사이즈의 변화를 끝낸 다음에 Update_Rect함수를 호출
	Update_Rect();

	switch (m_eDir)
	{
	case DIR::UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case DIR::DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	case DIR::LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case DIR::RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	}


	// 벽을 넘어가면 삭제한다
	if (20 > m_tInfo.fX || WINCX - 20 < m_tInfo.fX
		|| 20 > m_tInfo.fY || WINCY - 20 < m_tInfo.fY)
	{
		CMainGame::GetInst()->DeleteObj(this);
	}
}

void CBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{

}
