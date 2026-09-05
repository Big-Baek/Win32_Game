#pragma once
#include "CComponent.h"

class CMonster;
class CState;


class AI: public CComponent
{
public:
	AI();
	~AI();
private:
	map<STATE, CState*> m_mapState;
	CState* m_pCurState;

public:
	virtual void update() override;

	void AddState(CState* _pState);
	CState* GetState(STATE _eState);

	void ChangeState(STATE _eNextState);

	void SetCurState(STATE _eState);

	friend class CMonster;
};

