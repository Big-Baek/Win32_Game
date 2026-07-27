#include "Global.h"
#include "CUIMgr.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CUI.h"

#include "CKeyMgr.h"
CUIMgr::CUIMgr() :
	m_pFocusUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// 1. FocusUI 확인
	m_pFocusUI = GetFocusUI();

	if (!m_pFocusUI) return;

	//2. FocusUI에서 부모 UI포함, 자식 UI들 중 실제 타겟UI를 가져옴
	CUI* pTargetUI = GetTargetedUI(m_pFocusUI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_WAWAY(KEY::LBTN);

	if (pTargetUI != nullptr)
	{
		pTargetUI->MouseOn();
		if (bLbtnTap) //마우스를 눌렀을 때
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)//마우스를 땠을때
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}
			pTargetUI->m_bLbtnDown = false;
		}
	}

}

CUI* CUIMgr::GetFocusUI()
{
	CScene* pCUrScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCUrScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	// 기존 포커싱 UI를 받아둠
	CUI* pFocusUI = m_pFocusUI;

	if (!bLbtnTap) return pFocusUI;

	vector<CObject*>::iterator targetiter = vecUI.end();
	//vector<CObject*>::iterator it = vecUI.begin();
	vector<CObject*>::reverse_iterator it2 = vecUI.rbegin();


	//for (; it != vecUI.end(); it++)
	//{
	//	if (((CUI*)*it)->IsMouseOn())
	//	{
	//		targetiter = it;
	//	}
	//}

	for (auto it2 = vecUI.rbegin(); it2 != vecUI.rend(); ++it2)
	{
		CUI* pUI = (CUI*)(*it2);

		if (pUI->IsMouseOn())
		{
			// reverse_iterator → iterator 변환
			auto it = it2.base();
			--it;  // 실제 요소 위치

			targetiter = it;
			break;
		}
	}

	if (targetiter == vecUI.end())
	{
		return nullptr;
	}

	pFocusUI = (CUI*)*targetiter;
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusUI);

	return pFocusUI;
}

void CUIMgr::SetFocusUI(CUI* _pUI)
{
	if (_pUI == m_pFocusUI || _pUI == nullptr)
	{
		m_pFocusUI = _pUI;
		return;
	}

	m_pFocusUI = _pUI;

	CScene* pCUrScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCUrScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter) //이렇게 해도 iter의 실제값은 변함
	{
		if (m_pFocusUI == *iter)
		{
			break;
		}
	}
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusUI);
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	static queue<CUI*> que;
	static vector<CUI*> vecNoneTarget;

	vecNoneTarget.clear();
	que = queue<CUI*>();

	CUI* pTargetUI = nullptr;
	bool bLbtnAway = KEY_WAWAY(KEY::LBTN);

	que.push(_pParentUI);

	while (!que.empty())
	{
		CUI* pUI = que.front();
		que.pop();

		if (pUI->IsMouseOn()) //호버되어 있다면 그 자식들 큐에 삽입
		{
			if (pTargetUI != nullptr)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;


		}
		else //호버 안될경우
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (CUI* uiui : vecChild)
		{
			que.push(uiui);
		}

	}

	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); i++)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}
	return pTargetUI;
}
