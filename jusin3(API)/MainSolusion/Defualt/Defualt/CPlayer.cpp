#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"

#include "CShield.h"
#include "CScrewBullet.h"

CPlayer::CPlayer()
	: m_Theta(0.f)
	, m_velX(0)
	, m_velY(0)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 10.f;

	m_fDiagonal = 100.f;  // 포신의 길이
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
	m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf((m_fAngle * PI) / 180.f));
	m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf((m_fAngle * PI) / 180.f));
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	
	// 포신 그리기
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tPosin.x, (int)m_tPosin.y);
}

void CPlayer::Release(void)
{

}

void CPlayer::Key_Input(void)
{

	if (GetAsyncKeyState(VK_LEFT))
		m_fAngle += 5.f;

	if (GetAsyncKeyState(VK_RIGHT))
		m_fAngle -= 5.f;

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);

	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_velX += -m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_velY -= -m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		//m_velX += 50.f * cosf((m_fAngle * PI) / 180.f);
		//m_velY -= 50.f * sinf((m_fAngle * PI) / 180.f);
	}
	
	if (GetAsyncKeyState('D'))
		m_pShield->push_back(Create_Shield());


	//m_tInfo.fX += m_velX;
	//m_tInfo.fY += m_velY;

	//if (500.f > m_tInfo.fY)
	//{
	//	m_velY += 9.8 / 60.f;
	//}
	//else
	//{
	//	m_velY = 0.f;
	//}
}


template<typename T>
CObj* CPlayer::Create_Bullet(void)
{
	CObj* pBullet = CAbstractFactory<T>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle);

	return pBullet;
}

CObj* CPlayer::Create_Shield(void)
{
	CObj* pShield = CAbstractFactory<CShield>::Create();
	pShield->Set_Target(this);

	return pShield;
}
