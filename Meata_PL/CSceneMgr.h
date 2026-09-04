#pragma once
#include "CScene.h"


class CSceneMgr
{

	SINGLE(CSceneMgr);

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END]; //¸ðµç ¾À ¸ñ·Ï
	vector<CScene*> m_vecScene;
	CScene* m_pCurScene;

public:

	void init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurScene() { return m_pCurScene; }

private:
	void ChangeScene(SCENE_TYPE _eNext);

	friend class CEventMgr; 
};

