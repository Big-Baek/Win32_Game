#include "Global.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "CScene_Tool.h"


CSceneMgr::CSceneMgr() :
	m_pCurScene(nullptr),
	m_arrScene{}
{

}

CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (m_arrScene[i] != nullptr) delete m_arrScene[i];
	}
}

void CSceneMgr::init()
{
	//씬 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");

	//현재 Scene 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();
	m_pCurScene->Physics_update();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);

}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)_eNext]; 

	m_pCurScene->Enter();
}
