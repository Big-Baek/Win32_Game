#pragma once
#include "CState.h"

class CTraceStae : public CState
{
public:
	CTraceStae();
	~CTraceStae();

private:



public:

	virtual void update();
	virtual void Enter();
	virtual void Exit();

};

