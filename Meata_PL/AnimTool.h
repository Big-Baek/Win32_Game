#pragma once

class CAnimation;

class AnimTool
{
public:
	AnimTool();
	~AnimTool();

public:
	CAnimation* m_pAnim;
	static AnimTool* s_pThis;

	Image* m_pImage;

	Vec2 m_vLt;
	Vec2 m_vRb;
	float Step;
	float Duration;
	float AnimCount;

	bool b_Play;

	void m_LoadImage(const wchar_t* path);
	void Apply(HWND hDlg);

};

