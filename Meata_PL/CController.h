#pragma once
#include "CComponent.h"

class CActor;
class CRigidBody;
class CStateMachine;

class CController : public CComponent
{
public:
	CController();
	~CController();

private:
	CRigidBody* m_pRigid;
	CStateMachine* m_pStateMachine;
	CActor* m_pOwner;

public:

	virtual void BeginPlay() override;
	virtual void update() override;


	friend class CActor;
};

