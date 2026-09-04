#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore);

private:
	HWND m_hWnd;// 메인 윈도우 핸들
	POINT m_ptResolution; //윈도우 해상도
	HDC m_hDC;
	HDC m_memDC;
	CTexture* m_pMemTex; //백버퍼 텍스쳐


	//HBITMAP m_hBit;
	//HDC m_memDC;

	//자주쓸 GDI Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

	//메뉴
	HMENU m_hMenu; //ToolScene에서만 사용
public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockingMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC GetMainDC() { return m_hDC; }

	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

};

