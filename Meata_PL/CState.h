#pragma once
#include "Global.h"
#include "CMonster.h"

class AI;
class CMonster;

class CState
{
public:
	CState(STATE _eState);
	virtual ~CState();

public: //변수
	AI* m_pAI;
	STATE m_eState;
	CMonster* m_pOwner;

public: //함수
	AI* GetAI() { return m_pAI; }
	STATE GetType() { return m_eState; }
	CMonster* GetMonster();
public:

	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
};

