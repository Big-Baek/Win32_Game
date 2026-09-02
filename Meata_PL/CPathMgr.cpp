#include "Global.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr() :
	m_szContentPath{}
{}
CPathMgr::~CPathMgr()

{}

void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);//현재 경로를가져와 변수에 저장 (D:\Git Fork\Win32_Game_Metal\Debug)

	//상위폴더로 나가야됨
	int iLen = wcslen(m_szContentPath);

	for (int i = iLen - 1; i >= 0; i--)
	{
		if ('\\' == m_szContentPath[i])// \는 이스케이프 문자이기에 '\'를 탐지하기 위해서는 '\\'를 해야 알아먹는다.
		{
			m_szContentPath[i] = '\0'; // \Debug 를 잘라내고 반복 종료
			break;
		}
	}
	wcscat_s(m_szContentPath, 255, L"\\Content\\"); // Content를 붙인다.

	//MessageBox(NULL, m_szContentPath, L"CurrentPath", MB_OK);
}

//상대경로 반환
//wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
//{
//	wstring strFilePath = _filepath; //Content안에서 들어갈 폴더명
//
//	size_t iAbsLen = wcslen(m_szContentPath); //Content폴더까지의 경로길이
//	size_t iFullLen = strFilePath.length(); //들어갈 폴더경로 길이
//
//	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen-iAbsLen); //전체 경로 = Content폴더까지의 경로 + ???
//
//	return strRelativePath;
//}
