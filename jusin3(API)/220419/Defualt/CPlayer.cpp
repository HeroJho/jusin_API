#include "pch.h"
#include "CMainGame.h"
#include "CPlayer.h"
#include "CBullet.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;		// ���� X
	m_tInfo.fY = 300.f;		// ���� Y

	m_tInfo.fCX = 100.f;	// �÷��̾� ���� ������
	m_tInfo.fCY = 100.f;	// �÷��̾� ���� ������

	m_fSpeed = 10.f;
}

void CPlayer::Update(void)
{
	Key_Input();

	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��
	Update_Rect();
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release(void)
{

}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}

	if (GetAsyncKeyState('W'))
	{
		CBullet* pBullet = new CBullet;
		pBullet->SetOwner(this);
		pBullet->Initialize();
		pBullet->SetDir(DIR::UP);
		CMainGame::GetInst()->CreateObj(pBullet);
	}
	else if (GetAsyncKeyState('S'))
	{
		CBullet* pBullet = new CBullet;
		pBullet->SetOwner(this);
		pBullet->Initialize();
		pBullet->SetDir(DIR::DOWN);
		CMainGame::GetInst()->CreateObj(pBullet);
	}
	else if (GetAsyncKeyState('A'))
	{
		CBullet* pBullet = new CBullet;
		pBullet->SetOwner(this);
		pBullet->Initialize();
		pBullet->SetDir(DIR::LEFT);
		CMainGame::GetInst()->CreateObj(pBullet);
	}
	else if (GetAsyncKeyState('D'))
	{
		CBullet* pBullet = new CBullet;
		pBullet->SetOwner(this);
		pBullet->Initialize();
		pBullet->SetDir(DIR::RIGHT);
		CMainGame::GetInst()->CreateObj(pBullet);
	}
}
