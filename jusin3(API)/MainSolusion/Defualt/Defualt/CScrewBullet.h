#pragma once
#include "CObj.h"
class CScrewBullet :
    public CObj
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();

public:
	void SetCenter(float _fX, float _fY) { m_tCenter.x = _fX; m_tCenter.y = _fY; }
	virtual void OnCollision();

public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;


private:
	POINT					m_tCenter;
	float					m_fDiagonal;
	float					m_satTheta;


};

