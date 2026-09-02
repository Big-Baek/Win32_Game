#pragma once

class CTexture;
class CRes;

class CResMgr
{
	SINGLE(CResMgr)


private:
	map<wstring, CRes*> m_mapTex;

public:

	void Release(); //프로그램이 종료되기전 리소스를 모두 반환하는 함수

	CTexture* CreateAbsolute(const wstring& _strKey, const wstring& _strRelativePath); //절대경로를통해 텍스쳐이미지를 불러오는 함수
	CTexture* CreateRelative(const wstring& _strKey, const wstring& _strRelativePath); //상대경로를통해 텍스쳐이미지를 불러오는 함수
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight); //백버퍼, 카메라 생성용도

	CTexture* FindTexture(const wstring& _strKey);

};

