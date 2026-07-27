#include "Global.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CRes.h"

//절대경로, 상대경로 인자
CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
	{
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	//중복 방지. 이미 키값이 있으면 덮어쓰기 못함
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
	pTex->Create(_iWidth, _iHeight);
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

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
	auto iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); iter++)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
		}
	}

	m_mapTex.clear();

	//Safe_Delete_Map(m_mapTex);
}
