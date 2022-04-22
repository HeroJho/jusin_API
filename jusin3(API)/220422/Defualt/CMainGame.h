#pragma once

#include "Include.h"

#include "CPlayer.h""
#include "CMonster.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	RECT GetRecWall() { return m_rcWall; }

public:
	void Initialize(void);		// 데이터를 초기화하는 함수
	void Update(void);			// 매 프레임마다 갱신하는 함수
	void Late_Update(void);
	void Render(void);			// 매 프레임마다 출력하는 함수
	void Release(void);			// 객체 파괴 시 메모리 해제 함수


private:
	HDC				m_hDc;

	list<CObj*>	m_ObjList[OBJ_END]; 	// 반복자(이터레이터)패턴

	TCHAR		m_szFPS[64];			// 멀티 바이트 기반에서는 CHAR로 유니 코드 기반에서는 유니코드로 처리해주는 매크로
	int			m_iFPS;
	DWORD		m_dwTime;

	RECT		m_rcWall;
};
