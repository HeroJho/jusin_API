#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"

#include "CScrewBullet.h"

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
		m_tInfo.fX += -m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY -= -m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		CObj* s = CAbstractFactory<CScrewBullet>::Create(0.f, 0.f, m_fAngle);
		((CScrewBullet*)s)->SetCenter((float)m_tInfo.fX, (float)m_tInfo.fY);
		m_pBullet->push_back(s);
 	}
		
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



