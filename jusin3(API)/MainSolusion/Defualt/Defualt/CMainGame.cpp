#include "pch.h"
#include "CMainGame.h"

#include "CPlayer.h"

CMainGame* CMainGame::m_pInst = nullptr;

CMainGame::CMainGame()
	: m_hDc(nullptr)
{
}

CMainGame::~CMainGame()
{
	Release();
}


void CMainGame::Initialize(void)
{
	// main�� �ִ� hWnd ID ���� ���´�
	m_hDc = GetDC(g_hWnd);


	// Player ����
	CObj* pObj= new CPlayer;
	pObj->Initialize();
	CreateObj(pObj);
	
}

void CMainGame::Update(void)
{
	for (int i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->Update();
	}
}

void CMainGame::Render(void)
{
	// ū �׸� �׷��� ���� ������ �׸��� �����ش�.
	Rectangle(m_hDc, 0, 0, WINCX, WINCY);
	Rectangle(m_hDc, 0 + 20, 0 + 20, WINCX - 20, WINCY - 20);

	for (vector<CObj*>::iterator iter = m_vecObj.begin();
		iter != m_vecObj.end();)
	{
		if (!(*iter)->GetDie())
		{
			(*iter)->Render(m_hDc);
			++iter;
		}
		else
		{
			Safe_Delete<CObj*>(*iter);
			iter = m_vecObj.erase(iter);
		}
	}
}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_hDc);

	for (int i = 0; i < m_vecObj.size(); ++i)
	{
		Safe_Delete<CObj*>(m_vecObj[i]);
	}
	m_vecObj.clear();
}


void CMainGame::CreateObj(CObj* _pObj)
{
	m_vecObj.push_back(_pObj);
}

void CMainGame::DeleteObj(CObj* _pObj)
{
	_pObj->SetDie();
}



// �İ�ü (�ּ� �ϵ���� ���� ������ ��ü)

// Delete�� Reals�� ����
//		������ �ּҸ� Delete�ϸ� ���� �����ȴ�
//		�İ�ü�� Delete�ϸ� �ٸ� ������ �� ���� �ȴ�.
//		���۷��� ī����  >> �纻�� ���� �� ���� ī��Ʈ�� �Ѵ�.
//		�������ϸ� ī��Ʈ�� �����Ѵ�
//		����� 0�� �� �� delete�Ѵ�

// ��, Release�� ��� �纻�� ������ �� Delete�� �ȴ�.

// MS�� ����Ʈ �����͸� �������� ����ϱ� ������
// ����Ʈ ������ >>  �޸� ���� �˾Ƽ� ���� ����


