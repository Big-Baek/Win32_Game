 #pragma once
#include "CRes.h"



class CTexture:public CRes
{
public:
	CTexture();
	virtual ~CTexture();

private:
	HDC m_dc;
	HBITMAP m_hbit;  
	BITMAP m_bitInfo;

public:
	Gdiplus::Image* m_pImg;
	bool m_bUseGDIPlus;

public:


	void Load(const wstring& _strFilePath);
	void PNG_Load(const wstring& _strFilePath);

	void Create(UINT _iWidth, UINT _iHeight);
	void render(HDC hdc, int x, int y);
	UINT Width() { return m_bitInfo.bmWidth; }
	UINT Height() { return m_bitInfo.bmHeight; }

	HDC GetDC() { return m_dc; }
	Image* GetImg() { return m_pImg; }

	friend class CResMgr;//ResMgr를 통해서만 객체생성 가능
};

