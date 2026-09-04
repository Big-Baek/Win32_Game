#pragma once
//#include "Global.h"

class CMonster;
class CState;


class AI
{
public:
	AI();
	~AI();

	CMonster* m_pOwner;

private:
	map<STATE, CState*> m_mapState;
	CState* m_pCurState;

public:
	void update();

	void AddState(CState* _pState);
	CState* GetState(STATE _eState);
	CMonster* GetOwner() { return m_pOwner; }

	void ChangeState(STATE _eNextState);

	void SetCurState(STATE _eState);
public:
};

