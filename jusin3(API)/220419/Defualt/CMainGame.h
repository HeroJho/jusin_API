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
	void Initialize(void);		// �����͸� �ʱ�ȭ�ϴ� �Լ�
	void Update(void);			// �� �����Ӹ��� �����ϴ� �Լ�
	void Render(void);			// �� �����Ӹ��� ����ϴ� �Լ�
	void Release(void);			// ��ü �ı� �� �޸� ���� �Լ�


public:
	void CreateObj(CObj* _pObj);
	void DeleteObj(CObj* _pObj);

private:
	HDC				m_hDc;

	vector<CObj*>	m_vecObj;
};