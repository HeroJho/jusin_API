#pragma once

#include "Include.h"

class CObj;

class CMainGame
{
private:
	static CMainGame* m_pInst;
public:
	static CMainGame* GetInst()
	{
		if (m_pInst == nullptr)
			m_pInst = new CMainGame;

		return m_pInst;
	}

public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(void);		// 데이터를 초기화하는 함수
	void Update(void);			// 매 프레임마다 갱신하는 함수
	void Render(void);			// 매 프레임마다 출력하는 함수
	void Release(void);			// 객체 파괴 시 메모리 해제 함수


public:
	void CreateObj(CObj* _pObj);
	void DeleteObj(CObj* _pObj);

private:
	HDC				m_hDc;

	vector<CObj*>	m_vecObj;
};