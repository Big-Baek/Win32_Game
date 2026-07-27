#pragma once
#include "CObject.h"

class CTexture;

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	WALK_RIGHT,
	ATTACK,
	JUMP,
	DEAD
};

enum class PLAYER_ATTACK_STATE
{
	NORMAL_ATT_1,
	NORMAL_ATT_2,
	NORMAL_ATT_3,
};


class CPlayer :public CObject
{
private:
	vector<CObject*> m_vecColObj;

	PLAYER_STATE m_eCurState;
	PLAYER_STATE m_ePrevState;
	int m_iDir;
	int m_iPrevDir;

	float m_vSpeed;


public:
	virtual void update() override;
	virtual void render(HDC _dc) override;

	void CreateMissile(int n);
	void update_state();
	void update_move();
	void update_animation();
	void update_Gravity();

	virtual void OnCollisionEnter(CCollider* _pOther) override;

	CLONE(CPlayer);

public:
	CPlayer();
	~CPlayer();
};

