#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* m_pFocusUI;



public:

	void update();
	CUI* GetFocusUI();
	void SetFocusUI(CUI* _pUI);
private:
	//부모 UI 내에서 실제로 타겟팅 된 UI를 찾아 반환
	CUI* GetTargetedUI(CUI* _pParentUI);


};

