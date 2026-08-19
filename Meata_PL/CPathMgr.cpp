#include "Global.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr() :
	m_szContentPath{}
{}
CPathMgr::~CPathMgr()

{}

void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);//현재 경로를가져와 변수에 저장

	//상위폴더로 나가야됨
	int iLen = wcslen(m_szContentPath);

	for (int i = iLen - 1; i >= 0; i--)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}
	wcscat_s(m_szContentPath, 255, L"\\Content\\");

	//MessageBox(NULL, m_szContentPath, L"CurrentPath", MB_OK);
}

//상대경로 반환
wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;

	size_t iAbsLen = wcslen(m_szContentPath);
	size_t iFullLen = strFilePath.length();

	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen-iAbsLen);

	return strRelativePath;
}
