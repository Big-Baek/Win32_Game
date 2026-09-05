#pragma once
#include "CActor.h"
#include <Windows.h>

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

class CPlayer :public CActor
{
public:
	CPlayer();
	~CPlayer();

private:
	vector<CObject*> m_vecColObj;

	PLAYER_STATE m_eCurState;
	PLAYER_STATE m_ePrevState;
	int m_iDir;
	int m_iPrevDir;

	float m_vSpeed;

public:
	virtual void BeginPlay() override;
	virtual void update() override;
	void render(HDC _dc)override;

	void CreateMissile(int n);
	void update_state();
	void update_animation();

	virtual void OnCollisionEnter(CCollider* _pOther) override;

	CLONE(CPlayer);

};

