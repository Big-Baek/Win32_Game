#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CGravity.h"

CObject::CObject() :
	m_vPos{},
	m_vScale{},
	m_pCollider(nullptr),
	m_pAnimator(nullptr),
	m_pRigidBody(nullptr),
	m__bAlive(true),
	m_pGravity(nullptr)
{
}

CObject::CObject(const CObject& _origin) :
	m_strName(_origin.m_strName),
	m_vPos(_origin.m_vPos),
	m_vScale(_origin.m_vScale),
	m_pCollider(nullptr),
	m__bAlive(true),
	m_pAnimator(nullptr)
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
	
	if (_origin.m_pGravity)
	{
		m_pGravity = new CGravity(*_origin.m_pGravity);
		m_pGravity->m_pOwner = this;
	}
}

CObject::~CObject()
{
	if (m_pCollider != nullptr) delete m_pCollider;

	if (m_pAnimator != nullptr) delete m_pAnimator;

	if (m_pRigidBody != nullptr) delete m_pRigidBody;

	if (m_pGravity != nullptr) delete m_pGravity;
}

void CObject::finalupdate()
{

	if (m_pAnimator) m_pAnimator->finalupdate();

	if (m_pGravity) m_pGravity->finalupdate();

	if(m_pRigidBody) m_pRigidBody->finalupdate();

	if (m_pCollider) m_pCollider->finalupdate();

}


void CObject::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos); //카메라가 개입됨으로써 렌더될 위치

	Rectangle(_dc,
		(int)(vRenderPos.x - m_vScale.x / 2.f),
		(int)(vRenderPos.y - m_vScale.y / 2.f),
		(int)(vRenderPos.x + m_vScale.x / 2.f), 
		(int)(vRenderPos.y + m_vScale.y / 2.f));

	ComponentRender(_dc);
}

void CObject::ComponentRender(HDC _dc)
{
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->render(_dc);
	}

	if (m_pCollider != nullptr)
	{
		m_pCollider->render(_dc);
	}
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;

}

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}

void CObject::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}

