#pragma once
#include "CState.h"

class CIdleState : public CState
{
public:
	CIdleState();
	~CIdleState();

private:


public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();


};

