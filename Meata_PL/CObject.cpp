#include "CObject.h"
#include "CTexture.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"

CObject::CObject() :
	m_pTex(nullptr),
	m_vPos{},
	m_vScale{},
	m__bAlive(true)
{}

CObject::CObject(const CObject& _origin) :
	m_pTex(_origin.m_pTex),
	m_strName(_origin.m_strName),
	m_vPos(_origin.m_vPos),
	m_vScale(_origin.m_vScale),
	m__bAlive(true)
{}

CObject::~CObject()
{}

void CObject::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos); //카메라가 개입됨으로써 렌더될 위치

	Rectangle(_dc,
		(int)(vRenderPos.x - m_vScale.x / 2.f),
		(int)(vRenderPos.y - m_vScale.y / 2.f),
		(int)(vRenderPos.x + m_vScale.x / 2.f), 
		(int)(vRenderPos.y + m_vScale.y / 2.f));
}