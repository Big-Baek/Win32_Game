#include "CController.h"
#include "CKeyMgr.h"
#include "CActor.h"
#include "CRigidBody.h"
#include "CStateMachine.h"

CController::CController()
{
	m_eType = COMPONENT_TYPE::CONTROLLER;
}

CController::~CController()
{}

void CController::BeginPlay()
{
	m_pRigid = m_pOwner->GetRigidBody();
	m_pStateMachine = m_pOwner->GetStateMachine();
}

void CController::update()
{
	CComponent::update();

	if (KEY_HOLD(KEY::A))
	{
		m_pRigid->AddForce(Vec2(-200.f, 0.f));

	}
	if (KEY_HOLD(KEY::D))
	{
		m_pRigid->AddForce(Vec2(200.f, 0.f));
	}
	if (KEY_TAP(KEY::A))
	{
		//pRigid->AddForce(Vec2(200.f, 0.f));
		m_pRigid->SetVelocity(Vec2(-100.f, m_pRigid->GetVelocity().y));
	}
	if (KEY_HOLD(KEY::D))
	{
		//pRigid->AddForce(Vec2(200.f, 0.f));
		m_pRigid->SetVelocity(Vec2(100.f, m_pRigid->GetVelocity().y));
	}
}

//if (KEY_HOLD(KEY::A))
//{
//	m_iDir = -1;
//	if (m_eCurState != PLAYER_STATE::JUMP)
//		m_eCurState = PLAYER_STATE::WALK;
//	return;
//}
//if (KEY_HOLD(KEY::D))
//{
//	m_iDir = 1;
//	if (m_eCurState != PLAYER_STATE::JUMP)
//		m_eCurState = PLAYER_STATE::WALK;
//	return;
//}
//if (GetRigidBody()->GetSpeed() == 0.f)
//{
//	m_eCurState = PLAYER_STATE::IDLE;
//	return;
//}
//if (KEY_TAP(KEY::SPACE))
//{
//	m_eCurState = PLAYER_STATE::JUMP;
//	if (GetRigidBody())
//	{
//		GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -300.f));
//	}
//}