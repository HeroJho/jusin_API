#pragma once

#include "CObj.h"
#include "CBullet.h"

class CPlayer :
    public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void	Set_BulletList(list<CObj*>* pBullet)
	{
		m_pBullet = pBullet;
	}
	void	Set_ShieldList(list<CObj*>* pShield) { m_pShield = pShield; }

public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)		override;

private:
	void		Key_Input(void);

	CObj* Create_Shield(void);

	template<typename T>
	CObj*       Create_Bullet(void);

private:
	typedef list<CObj*>		BULLETLIST;
	BULLETLIST* m_pBullet;
	float m_Theta;

	list<CObj*>* m_pShield;

	POINT					m_tPosin;
	float					m_fDiagonal;
	float					m_velX;
	float					m_velY;
};

