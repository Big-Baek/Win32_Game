#pragma once

class CActor;
class CGravity;


class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();

private:
	CActor* m_pOwner;
	CGravity* m_pGravity;


	Vec2 m_vForce; //힘, 방향
	Vec2 m_vAccel; //가속도
	Vec2 m_vAccelA; //가속도 추가량
	Vec2 m_vVelocity;
	Vec2 m_vMaxVelocity; //최대 속도
	float m_fMass; //질량
	float m_fFriction; //마찰계수

	bool m_bGravity; //중력 적용 여부
	bool m_bGround; //땅에 붙어있는지
private:
	void Move();
public:

	void update();
	void finalupdate();

	void EnableGravity(bool _b);
	void SetGround(bool _b);


	void AddForce(Vec2 _vF) { m_vForce += _vF; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }

	void SetMass(float _fMass) { m_fMass = _fMass; }
	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	void SetMaxVelocity(Vec2 _v) { m_vMaxVelocity = _v; }
	void SetAccelAlpha(Vec2 _vAccel) { m_vAccelA = _vAccel; }

	float GetMass() { return m_fMass; }
	float GetSpeed() { return m_vVelocity.Length(); }
	Vec2 GetVelocity() { return m_vVelocity; }

	friend class CActor;
};

