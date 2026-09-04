#pragma once
#include "CObject.h"

class CTexture;
class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;

class CActor: public CObject
{
public:
	CActor();
	CActor(const CActor& _origin);
	~CActor();

protected:
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;
	CRigidBody* m_pRigidBody;
	//CGravity* m_pGravity;

public:
	void virtual update() override;
	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	//CGravity* GetGravity() { return m_pGravity; }

	virtual void Physics_update(); //물리 업데이트
	virtual void render(HDC _dc);

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}
	void ComponentRender(HDC _dc);

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	//void CreateGravity();


};

