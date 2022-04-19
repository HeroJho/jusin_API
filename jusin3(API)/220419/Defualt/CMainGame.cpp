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
	// main에 있는 hWnd ID 값을 얻어온다
	m_hDc = GetDC(g_hWnd);


	// Player 생성
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
	// 큰 네모를 그려서 이전 프레임 그림을 덮어준다.
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



// 컴객체 (최소 하드웨어 정보 가지는 객체)

// Delete와 Reals의 차이
//		복사한 주소를 Delete하면 전부 삭제된다
//		컴객체를 Delete하면 다른 곳에서 못 쓰게 된다.
//		레퍼런스 카운터  >> 사본이 생길 때 마다 카운트를 한다.
//		릴리즈하면 카운트를 감소한다
//		릴리즈가 0이 될 때 delete한다

// 즉, Release는 모든 사본이 없어질 때 Delete가 된다.

// MS가 스마트 포인터를 정식으로 사용하기 시작함
// 스마트 포인터 >>  메모리 누수 알아서 해제 도구


