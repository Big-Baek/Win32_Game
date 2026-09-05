#pragma once
#include "CActor.h"

class CGround: public CActor
{
public:

	CGround();
	~CGround();

private:
	virtual void BeginPlay() override;
	virtual void update();


public:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther)override;
	virtual void OnCollisionExit(CCollider* _pOther)override;

	CLONE(CGround);
};

