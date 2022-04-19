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
	// �Ѿ� ���� ��ġ�� �÷��̾�
	m_tInfo.fX = m_pOwner->GetInfo().fX;
	m_tInfo.fY = m_pOwner->GetInfo().fY;

	m_tInfo.fCX = 50.f;	// �Ѿ� ���� ������
	m_tInfo.fCY = 50.f;	// �Ѿ� ���� ������

	m_fSpeed = 10.f;
}

void CBullet::Update(void)
{
	// ���ʿ��� ���� �Ǵ� �������� ��ȭ�� ���� ������ Update_Rect�Լ��� ȣ��
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


	// ���� �Ѿ�� �����Ѵ�
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
