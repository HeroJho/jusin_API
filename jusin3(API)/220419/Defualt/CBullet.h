#pragma once
#include "CObj.h"


class CBullet :
    public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void SetOwner(CObj* _pObj) { m_pOwner = _pObj; }
	void SetDir(DIR _eDir) { m_eDir = _eDir; }

private:
	CObj*	m_pOwner;
	DIR		m_eDir;
};

