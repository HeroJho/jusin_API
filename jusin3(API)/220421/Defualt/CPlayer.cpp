#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"

CPlayer::CPlayer()
	: m_Theta(0.f)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;		// 중점 X
	m_tInfo.fY = 300.f;		// 중점 Y

	m_tInfo.fCX = 100.f;	// 플레이어 가로 사이즈
	m_tInfo.fCY = 100.f;	// 플레이어 세로 사이즈

	m_fSpeed = 10.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 연산을 진행
	Key_Input();

	// 위쪽에서 중점 또는 사이즈의 변화를 끝낸 다음에 Update_Rect함수를 호출
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{

}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	float x = m_tInfo.fX + cosf(m_Theta) * 100.f;
	float y = m_tInfo.fY + sinf(m_Theta) * 100.f;
	LineTo(hDC, x, y);
}

void CPlayer::Release(void)
{

}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (DPI < m_Theta)
			m_Theta = 0.f;
		
		m_Theta -= 0.1f;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (DPI < m_Theta)
			m_Theta = 0.f;

		m_Theta += 0.1f;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fX += cosf(m_Theta) * m_fSpeed;
		m_tInfo.fY += sinf(m_Theta) * m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fX -= cosf(m_Theta) * m_fSpeed;
		m_tInfo.fY -= sinf(m_Theta) * m_fSpeed;
	}

	// 총알 생성
	if (GetAsyncKeyState('W'))
		m_pBullet->push_back(Create_Bullet(DIR_UP));

	if (GetAsyncKeyState('A'))
		m_pBullet->push_back(Create_Bullet(DIR_LEFT));

	if (GetAsyncKeyState('S'))
		m_pBullet->push_back(Create_Bullet(DIR_DOWN));

	if (GetAsyncKeyState('D'))
		m_pBullet->push_back(Create_Bullet(DIR_RIGHT));

}


CObj* CPlayer::Create_Bullet(DIRECTION eDir)
{
	/*CObj*		pBullet = new CBullet;
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	pBullet->Initialize();
	pBullet->Set_Dir(eDir);*/

	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, eDir);

	return pBullet;
}