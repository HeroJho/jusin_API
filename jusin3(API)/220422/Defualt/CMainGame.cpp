#include "pch.h"

#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CollisionMgr.h"

CMainGame::CMainGame()
	: m_hDc(nullptr)
	, m_dwTime(GetTickCount())
	, m_rcWall{ 100, 100, WINCX - 100, WINCY - 100 }
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	m_iFPS = 0;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	// main에 있는 hWnd ID 값을 얻어온다
	m_hDc = GetDC(g_hWnd);

	// 추상 펙토리 패턴을 사용해서 Player 생성.
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create());

	// 만든 Player한테 Main의 총알 리스트를 넘겨준다.
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_BulletList(&m_ObjList[OBJ_BULLET]);
	
}



void CMainGame::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CMainGame::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}

	CollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
}

void CMainGame::Render(void)
{
	// 큰 네모를 그려서 이전 프레임 그림을 덮어준다.
	Rectangle(m_hDc, 0, 0, WINCX, WINCY);
	Rectangle(m_hDc, m_rcWall.left, m_rcWall.top, m_rcWall.right, m_rcWall.bottom);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_hDc);
	}


	// 폰트 출력

	//lstrcpy(m_szFPS, L"Hello");
	//TextOut(m_hDC, 50, 50, m_szFPS, lstrlen(m_szFPS));
	// 1. dc 2, 3. 출력할 윈도우 left, top 좌표, 4. 출력할 문자열 5. 문자열 버퍼 크기

	//RECT rc{ 0, 0, 50, 50 };
	//DrawText(m_hDC, m_szFPS, lstrlen(m_szFPS), &rc, DT_RIGHT);
	// 1. dc 2. 출력할 문자열 3. 문자열 버퍼 크기 4. 출력할 렉트 주소, 5. 출력 옵션

	//TCHAR	szBuff[32] = L"";
	// 소수점 자리 출력이 불가능하다. winapi 라이브러리에서 제공하는 함수
	//wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());

	// visual c++ 라이브러리에서 제공(모든 서식 문자를 지원)
	//swprintf_s(szBuff, L"Bullet : %f", 3.14f);
	//TextOut(m_hDC, 50, 50, szBuff, lstrlen(szBuff));


	// FPS 출력
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_hDc);
}







// 벽력일섬 구현

// 충돌처리
//	오브젝트 >> 충돌처리 안되는 오브젝트도 있다  X

// 해결
//	충돌 처리만 하는 클래스가 필요할 것 같다.
//	충돌 처리를 담당하는 클래스 매니저를 만든다.

// 랜더링 오브젝트 배열을 따로 둬서 랜더링 순서를 정한다


// 숙제
// 1. 삼각함수 공부하기 (cos, sin, tan).
// 2. 플레이어 포신 추가하고 회전을 시켜라.
// 3. 포신의 방향으로 업다운 누르면 움직인다.


// 4조 영웅 세은 석균 김민성
// 공부 시간 정하기
// 내일부터 적용
// 화요일에 팀과제 발표


// 1. 아이스브레이킹
// 2. 진짜 민감한 언어 체크 (한숨 쉬는거 등 말 말고도)


// 최소 8시간 (수업시간 포함)
// 1.발표자료: 출결표(세세하게 기록)
// 2.역할분담(세세하게)
// 3.공정률 산출(얘가 플레이어 뭐뭐를 계획했고 하지만 총알뿐 구현 못했다 공정률 30퍼)
// 4.게임을 다 설명x (팀과제 도중의 이슈들 위주로)
// 5.회의내용 서기를 뽑아놔도 됨

// 실제 회사의 팀장처럼!!