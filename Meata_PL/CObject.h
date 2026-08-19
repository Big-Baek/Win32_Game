#pragma once
#include "Global.h"
#include "CCamera.h"

class CTexture;
class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;

class CObject
{
public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

private:
	//자식한테도 공개하지 않는 함수
	void SetDead() { m__bAlive = false; }
protected:
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

	CTexture* m_pTex;
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;
	CRigidBody* m_pRigidBody;
	CGravity* m_pGravity;

	bool m__bAlive; //살아있는지 죽어있는지 트리거
public:

	virtual void Start() {}; //Scene이 시작되기 전에 호출
	virtual void update() = 0; //상태 업데이트
	virtual void Physics_update(); //물리 업데이트
	virtual void render(HDC _dc);

	virtual void OnCollision(CCollider* _pOther){}
	virtual void OnCollisionEnter(CCollider* _pOther){}
	virtual void OnCollisionExit(CCollider* _pOther){} 


	void ComponentRender(HDC _dc);

	virtual CObject* O_Clone() = 0; //복제를 만드는 함수

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CGravity* GetGravity() { return m_pGravity; }

	bool IsDead() { return !m__bAlive; }
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetName(const wstring& _strName) { m_strName = _strName; }



	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	const wstring& GetName() { return m_strName; }

public:
	

	friend class CEventMgr;
};

