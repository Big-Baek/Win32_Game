#pragma once
#include "CUI.h"
#include "CScene.h"

typedef void(*BTN_Func)(DWORD_PTR, DWORD_PTR); //함수 포인터
typedef void(CScene::*SCENE_MEMFUNC)(void); //멤버함수 포인터

class CBtnUI : public CUI
{
public:
	CBtnUI();
	~CBtnUI();

private:
	BTN_Func m_pFunc;
	DWORD_PTR m_param1;
	DWORD_PTR m_param2;


	SCENE_MEMFUNC m_pSceneFunc;
	CScene* m_pSceneInst;
public:

	virtual void MouseOn();
	virtual void MouseLbtnDown() override;
	virtual void MouseLbtnUp() override;
	virtual void MouseLbtnClicked() override;



	void SetClickedCallBack(BTN_Func _pFUNC, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		m_pFunc = _pFUNC;
		m_param1 = _param1;
		m_param2 = _param2;
	}
	void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);



	CLONE(CBtnUI);
};

