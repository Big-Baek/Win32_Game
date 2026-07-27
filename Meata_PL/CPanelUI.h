#pragma once
#include "CUI.h"
class CPanelUI :public CUI
{
public:
	CPanelUI();
	~CPanelUI();

private:

	Vec2 m_vDragStart;


public:

	virtual void update() override;
	//virtual void render(HDC _dc) override;


	virtual void MouseOn() override;
	virtual void MouseLbtnDown() override;
	virtual void MouseLbtnUp() override;
	virtual void MouseLbtnClicked() override;

	CLONE(CPanelUI);
};

