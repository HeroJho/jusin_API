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
	void Initialize(void);		// �����͸� �ʱ�ȭ�ϴ� �Լ�
	void Update(void);			// �� �����Ӹ��� �����ϴ� �Լ�
	void Late_Update(void);
	void Render(void);			// �� �����Ӹ��� ����ϴ� �Լ�
	void Release(void);			// ��ü �ı� �� �޸� ���� �Լ�


private:
	HDC				m_hDc;

	list<CObj*>	m_ObjList[OBJ_END]; 	// �ݺ���(���ͷ�����)����

	TCHAR		m_szFPS[64];			// ��Ƽ ����Ʈ ��ݿ����� CHAR�� ���� �ڵ� ��ݿ����� �����ڵ�� ó�����ִ� ��ũ��
	int			m_iFPS;
	DWORD		m_dwTime;

	RECT		m_rcWall;
};
