#include "CActor.h"

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

void CActor::BeginPlay()
{
	for (CComponent* pComp : m_vecComponent)
	{
		pComp->BeginPlay();
	}
}

void CActor::render(HDC _dc)
{
	//CObject::render(_dc);
	ComponentRender(_dc);
}

void CActor::Component_update()
{
	if (m_pAnimator) m_pAnimator->update();

	if (m_pRigidBody) m_pRigidBody->update();

	if (m_pCollider) m_pCollider->update();
}

void CActor::ComponentRender(HDC _dc)
{
	for (auto comp : m_vecComponent)
	{
		if (comp->m_eType == COMPONENT_TYPE::ANIMATOR || comp->m_eType == COMPONENT_TYPE::COLLIDER)
		{
			comp->render(_dc);
		}
	}
}

void CActor::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
	m_vecComponent.push_back(m_pCollider);
}

void CActor::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
	m_vecComponent.push_back(m_pAnimator);
}

void CActor::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
	m_vecComponent.push_back(m_pRigidBody);
}

void CActor::CreateController()
{
	m_pController = new CController;
	m_pController->m_pOwner = this;
	m_vecComponent.push_back(m_pController);
}

void CActor::CreateStateMachine()
{
	m_pStateMachine = new CStateMachine;
	m_pStateMachine->m_pOwner = this;
	m_vecComponent.push_back(m_pStateMachine);
}
