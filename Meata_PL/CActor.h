#pragma once
#include "CObject.h"

#include "CController.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CStateMachine.h"

class CActor: public CObject
{
public:
	CActor();
	CActor(const CActor& _origin);
	~CActor();

protected:
	CCollider*		m_pCollider;
	CAnimator*		m_pAnimator;
	CRigidBody*		m_pRigidBody;
	CController*	m_pController;
	CStateMachine* m_pStateMachine;

	vector<CComponent*> m_vecComponent;

public:

	virtual void BeginPlay() override;
	virtual void render(HDC _dc);
	void ComponentRender(HDC _dc);

	virtual void Component_update();

	virtual void OnCollisionEnter(CCollider* _pOther) {} //충돌시작
	virtual void OnCollision(CCollider* _pOther) {}		 //충돌중
	virtual void OnCollisionExit(CCollider* _pOther) {}  //충돌끝

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; } 
	CStateMachine* GetStateMachine() { return m_pStateMachine; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateController();
	void CreateStateMachine();
};