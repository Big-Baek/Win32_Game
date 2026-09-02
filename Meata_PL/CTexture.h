#pragma once
#include "CRes.h"




//백버퍼를 위한용도가 제일 클듯
class CTexture :public CRes
{
public:
	CTexture();
	virtual ~CTexture();

private:

	HDC m_dc;
	HBITMAP m_hbit;
	Image* m_pImg;

public:

	bool CreateTexture(const wstring& _Name, const wstring& _strFilePath); //이미지 호출용
	void CreateBuffer(const wstring& _Name, UINT _iWidth, UINT _iHeight); //백버퍼생성용

	void render(HDC hdc, int x, int y);

	HDC GetDC() { return m_dc; }
	Image* GetImg()
	{
		if (m_pImg) return m_pImg;
	}

	friend class CResMgr;//ResMgr를 통해서만 객체생성 가능
};

