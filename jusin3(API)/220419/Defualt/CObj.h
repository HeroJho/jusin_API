#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void		Initialize(void)	PURE;
	virtual void		Update(void)		PURE;
	virtual void		Render(HDC hDC)		PURE;
	virtual void		Release(void)		PURE;

public:
	void			Update_Rect(void);
	INFO			GetInfo() { return m_tInfo; }

	void			SetDie() { m_bIsDie = true; }
	bool			GetDie() { return m_bIsDie; }

protected:
	INFO			m_tInfo;
	RECT			m_tRect;

	float			m_fSpeed;
	bool			m_bIsDie;
};

