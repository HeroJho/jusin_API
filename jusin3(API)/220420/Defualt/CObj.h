#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }

public:
	virtual		void		Initialize(void)	PURE;
	virtual		int			Update(void)		PURE;
	virtual		void		Late_Update(void)	PURE;
	virtual		void		Render(HDC hDC)		PURE;
	virtual		void		Release(void)		PURE;

public:
	void			Update_Rect(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	float		m_fSpeed;
	DIRECTION	m_eDir;
	bool		m_bDead;
};

