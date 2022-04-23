#pragma once
#include "CObj.h"

class CShield :
    public CObj
{
public:
	CShield();
	virtual ~CShield();

public:
	void SetOwner(CObj* _pOwner) { m_pOwner = _pOwner; }
	virtual void OnCollision();

public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;


private:
	CObj*					m_pOwner;
    float					m_fDiagonal;


};

