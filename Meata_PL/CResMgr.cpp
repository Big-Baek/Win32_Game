#include "Global.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CRes.h"

CResMgr::CResMgr()
{}

CResMgr::~CResMgr()
{}

void CResMgr::Release()
{
	auto iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); iter++)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}

	m_mapTex.clear();
}

CTexture* CResMgr::CreateAbsolute(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
	{
		return pTex;
	}

	pTex = new CTexture;
	pTex->CreateTexture(_strKey, _strRelativePath); //전체경로를 통해서 PNG로드

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::CreateRelative(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
	{
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath(); //Content폴더까지의 경로
	strFilePath += _strRelativePath; //Content + 원하는 파일까지 경로 더하기 = 전체경로

	pTex = new CTexture;
	pTex->CreateTexture(_strKey, strFilePath);//전체경로를 통해서 PNG로드

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
	{
		return pTex;
	}

	pTex = new CTexture;
	pTex->CreateBuffer(_strKey, _iWidth, _iHeight);
	pTex->SetKey(_strKey);

	//중복 방지. 이미 키값이 있으면 덮어쓰기 못함
	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring,CRes*>::iterator iter = m_mapTex.find(_strKey);
	
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return (CTexture*)iter->second;
}
