#pragma once

#include "CObj.h"


// 추상 팩토리 패턴 : 생성 패턴의 한 방법으로 인스턴스를 만드는 절차를 추상화하는 패턴을 의미한다.
// 객세 생성 시 공통적으로 수행할 작업을 추상화시키는 방식을 의미한다.

// 템플릿으로 사용한다 >> 인라인으로 작성
template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {};
	~CAbstractFactory() {};

public:
	static CObj* Create(void)
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, DIRECTION eDir = DIR_END)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		if (DIR_END >= eDir)
			pObj->Set_Dir(eDir);

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
};

