#include "Global.h"
#include "func.h"
#include "CEventMgr.h"
#include "AI.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.LParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.LParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.LParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeAIState(AI* _AI, STATE _eNextStae)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CHANGE_AI_STATE;
	evn.LParam = (DWORD_PTR)_AI;
	evn.wParam = (DWORD_PTR)_eNextStae;

	CEventMgr::GetInst()->AddEvent(evn);
}

void FScanf(char* _pOutBuff, FILE* _pFile)
{
	int i = 0;
	while (true)
	{
		char c = (char)getc(_pFile);
		if (c == '\n')
		{
			_pOutBuff[i++] = '\0';
			break;
		}

		_pOutBuff[++i] = c;
	}
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
	//Animation 이름저장
	const wchar_t* pStrName = _str.c_str();
	size_t iLen = _str.length();

	//문자 길이 저장
	fwrite(&iLen, sizeof(size_t), 1, _pFile);

	//문자열  저장
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);
	wchar_t szBuff[256] = {};

	fread(szBuff, sizeof(wchar_t), iLen, _pFile);

	_str = szBuff;
}
