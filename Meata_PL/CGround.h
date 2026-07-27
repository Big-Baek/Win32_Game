#pragma once
#include "CObject.h"

class CGround: public CObject
{
public:

	CGround();
	~CGround();

private:
	virtual void Start() override;
	virtual void update();


public:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther)override;
	virtual void OnCollisionExit(CCollider* _pOther)override;

	CLONE(CGround);
};

