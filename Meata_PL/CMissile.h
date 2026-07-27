#pragma once
#include "CObject.h"
class CMissile :public CObject
{
private:
	Vec2 m_fDir; //방향
	float m_fMisSpeed;


public:
	void SetDir(int _iDir, int count);//0~180으로 사격각도 조정

	//Vec2 GetPos();

	void update();
	virtual void render(HDC _dc);


	virtual void OnCollisionEnter(CCollider* _pOther) override;

	CLONE(CMissile);
public:
	CMissile();
	~CMissile();

};

