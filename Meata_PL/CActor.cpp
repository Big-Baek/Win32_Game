#include "CActor.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"

CActor::CActor() :
	m_pCollider(nullptr),
	m_pAnimator(nullptr),
	m_pRigidBody(nullptr)
{}

CActor::CActor(const CActor& _origin) :
	m_pCollider(nullptr),
	m_pAnimator(nullptr),
	m_pRigidBody(nullptr)
{
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
	if (_origin.m_pRigidBody)
	{
		m_pRigidBody = new CRigidBody(*_origin.m_pRigidBody);
		m_pRigidBody->m_pOwner = this;
	}
}

CActor::~CActor()
{
	if (m_pCollider != nullptr) delete m_pCollider;

	if (m_pAnimator != nullptr) delete m_pAnimator;

	if (m_pRigidBody != nullptr) delete m_pRigidBody;
}

void CActor::update()
{
}

void CActor::Physics_update()
{
	if (m_pAnimator) m_pAnimator->finalupdate();

	//if (m_pGravity) m_pGravity->finalupdate();

	if (m_pRigidBody) m_pRigidBody->finalupdate();

	if (m_pCollider) m_pCollider->finalupdate();

}

void CActor::render(HDC _dc)
{
	CObject::render(_dc);
	ComponentRender(_dc);
}

void CActor::ComponentRender(HDC _dc)
{
	this;
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->render(_dc);
	}
	if (m_pCollider != nullptr)
	{
		m_pCollider->render(_dc);
	}
}

void CActor::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CActor::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

void CActor::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}