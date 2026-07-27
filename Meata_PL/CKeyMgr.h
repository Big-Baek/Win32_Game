#pragma once

enum class KEY_STATE
{
	TAP, //막 누른 시점
	HOLD,//누르고 있는
	AWAY, //막 뗀 시점
	NONE //아무것도 아닌 상태
};

enum class KEY
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,H,J,K,L,
	Z,X,C,V,B,N,M,
	ALT,
	CTRL,
	LSHIFT,
	RSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST
};

struct tKeyinfo
{
	KEY_STATE eState;//어떻게 눌린 상태인지
	bool bPrev; //이전 프레임에 눌렸는지
};


class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyinfo> m_vecKey;//인덱스 = 키
	Vec2 m_vCurMousePos;


public:
	void init();
	void update();

	KEY_STATE GetKeyState(KEY e_KEY);
	Vec2 GetMousePos() { return m_vCurMousePos; }

private:
	CKeyMgr(const CKeyMgr&) = delete;
	CKeyMgr operator = (const CKeyMgr&) = delete;
};

