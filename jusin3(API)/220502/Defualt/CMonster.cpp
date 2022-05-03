#include "pch.h"
#include "CMonster.h"


CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fX = 600.f;		// ���� X
	m_tInfo.fY = 300.f;		// ���� Y

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 1.f;

	m_eDir = DIR_LEFT;
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	//double dX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	//double dY = m_pTarget->Get_Info().fY - m_tInfo.fY;

	// acos�� ����ؼ� 0~180 ������ ���� ���ϱ�
	//float dis = sqrt((dX * dX) + (dY * dY));
	//m_fAngle = acosf(dX / dis);

	// �÷��̾ ���ͺ��� �Ʒ��� �ִٸ� ������ ������ �ش�.
	//if (m_pTarget->Get_Info().fY > m_tInfo.fY)  // (������ ��ǥ��)
	//	m_fAngle *= -1.f;

	// ������ ��ǥ���̱⶧���� y�� ���ش�.
	//m_tInfo.fX += m_fSpeed * cosf(m_fAngle);
	//m_tInfo.fY -= m_fSpeed * sinf(m_fAngle);
	

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{

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
	// m_bDead = true;
}