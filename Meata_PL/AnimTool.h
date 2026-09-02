#pragma once

class CAnimation;
class CTexture;

class AnimTool
{
public:
	AnimTool();
	~AnimTool();

public:
	CAnimation* m_pAnim;
	static AnimTool* s_pThis;

	CTexture* m_pTex;
	wstring m_strTexPath;
	wchar_t AnimName[256];

	void m_LoadImage(wchar_t* path);
	void Apply(HWND hDlg);

};

