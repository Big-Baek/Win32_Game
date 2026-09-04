#pragma once
#include "CObject.h"

class CUI: public CObject
{
private:
	vector<CUI*> m_vecChildUI; // 가지고있는 자식 UI들
	CUI* m_pParentUI; //부모 UI
	Vec2 m_vFinalPos; //부모로부터 상대위치

	bool m_bCamAffect; //카메라 영향 유무 체크
	bool m_bMouseOn; //UI위에 마우스가 있는지
	bool m_bLbtnDown;

public:
	Vec2 GetFinalPos() { return m_vFinalPos; }
	CUI* GetParent() { return m_pParentUI; }
	bool IsMouseOn() { return m_bMouseOn; }
	bool IsLbtnDown() { return m_bLbtnDown; }


	void AddChild(CUI* _pUI)
	{
		m_vecChildUI.push_back(_pUI);
		_pUI->m_pParentUI = this;
	}
	const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

public:


	void update();
	void finalupdate(); //자기 위치를 결정
	void render(HDC _dc);

	virtual void MouseOn(); //마우스 호버링
	virtual void MouseLbtnDown(); //마우스 눌렀을때
	virtual void MouseLbtnUp(); //마우스 땠을때
	virtual void MouseLbtnClicked(); //마우스 클릭했을때(눌렀다 땜)

	virtual CUI* O_Clone() = 0;
private:
	void update_child(); //자식 UI들 업데이트
	void finalupdate_child();
	void render_child(HDC _dc);
	void MouseOnCheck();

public:

	CUI(bool _bCamAff);
	CUI(const CUI& _origin);
	virtual ~CUI();

	friend class CUIMgr;

};

