#pragma once

#include "Include.h"

#include "CPlayer.h""

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(void);		// �����͸� �ʱ�ȭ�ϴ� �Լ�
	void Update(void);			// �� �����Ӹ��� �����ϴ� �Լ�
	void Late_Update(void);
	void Render(void);			// �� �����Ӹ��� ����ϴ� �Լ�
	void Release(void);			// ��ü �ı� �� �޸� ���� �Լ�


private:
	HDC				m_hDc;

	// �ݺ���(���ͷ�����)����
	list<CObj*>	m_ObjList[OBJ_END];

	TCHAR		m_szFPS[64];	// ��Ƽ ����Ʈ ��ݿ����� CHAR�� ���� �ڵ� ��ݿ����� �����ڵ�� ó�����ִ� ��ũ��
	int			m_iFPS;
	DWORD		m_dwTime;
};

// ������ ���� : �ڵ��� �������� ������ ���·� ����� �����ϱ� ���ϰ� ���� ����

// �߻� ���丮 ���� : ���� ������ �� ������� �ν��Ͻ��� ����� ������ �߻�ȭ�ϴ� ������ �ǹ��Ѵ�.
// ���� ���� �� ���������� ������ �۾��� �߻�ȭ��Ű�� ����� �ǹ��Ѵ�.

// �ݺ���(���ͷ�����)���� : ���� ǥ�� ����� �������� �ʰ� �������� ���� ����� �����ϴ� ������ �ǹ��Ѵ�.