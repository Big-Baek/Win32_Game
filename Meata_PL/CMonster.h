#pragma once
#include "CObject.h"

struct tMonInfo
{
	float m_fSpeed;			  //속도
	float m_fHP;			  //체력
	float m_fPerceptionRange; //인지범위
	float m_fAttRange;		  //사거리
	float m_fAtt;			  //공격력

};

class CTexture;
class AI;

class CMonster : public CObject
{
public:
	CMonster();
	~CMonster();

private:
	tMonInfo m_tInfo;
	AI* m_pAI;

public:
	float GetSpeed() { return m_tInfo.m_fSpeed; }
	const tMonInfo& GetInfo() { return m_tInfo; }

	void  SetSpeed(float _f) { m_tInfo.m_fSpeed = _f; }
	void SetAI(AI* _AI);
private:
	void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }


public:
	virtual void update();
	CLONE(CMonster);
	virtual void OnCollisionEnter(CCollider* _pOther) override;

	friend class CMonFactory;
};

