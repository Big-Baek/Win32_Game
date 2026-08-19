#include "Global.h"
#include "AnimTool.h"
#include "Resource.h"
#include "CAnimation.h"
#include "CTexture.h"

AnimTool* AnimTool::s_pThis = nullptr;

float GetDlgFloat(HWND hDlg, int nID)
{
	wchar_t szBuf[64] = {};
	GetDlgItemText(hDlg, nID, szBuf, 64);
	return static_cast<float>(_wtof(szBuf));
}


AnimTool::AnimTool() :
	m_pImage(nullptr),
	b_Play(false)
{
	m_pAnim = new CAnimation;
}


AnimTool::~AnimTool()
{
	delete m_pAnim;
	delete m_pImage;
}

void AnimTool::m_LoadImage(const wchar_t* path)
{
	if (m_pImage)
	{
		delete m_pImage;
		if (m_pImage)
		{
			m_pImage = nullptr;
		}
		
	}

	m_pImage = new Gdiplus::Image(path);
}

void AnimTool::Apply(HWND hDlg)
{
	CTexture* Tex = new CTexture;
	Tex->m_pImg = m_pImage;
	m_pAnim->Create(
		Tex,														    //스프라이트시트
		Vec2(GetDlgFloat(hDlg, IDC_SP_X), GetDlgFloat(hDlg, IDC_SP_Y)), //좌상단 좌표
		Vec2(GetDlgFloat(hDlg, IDC_EP_X), GetDlgFloat(hDlg, IDC_EP_Y)), //우하단 좌표
		GetDlgFloat(hDlg, IDC_Step),								    //스텝간격
		GetDlgFloat(hDlg, IDC_Duration),							    //프레임간 재생간격
		GetDlgFloat(hDlg, IDC_Count));								    //총 프레임갯수
}


INT_PTR CALLBACK EditorProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		AnimTool::s_pThis = new AnimTool;
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_SheetFind:
		{
			OPENFILENAME ofn = { 0 };
			wchar_t szFile[MAX_PATH] = { 0 };

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFilter = L"PNG Files\0*.png\0";
			ofn.lpstrInitialDir = L"D:\\Git Fork\\Win32_Game_Metal\\Content\\Texture";
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

			if (GetOpenFileName(&ofn))
			{
				AnimTool::s_pThis->m_LoadImage(szFile);
			}
		}
		return TRUE;

		case IDApply: //적용
			AnimTool::s_pThis->Apply(hDlg);
			SetTimer(hDlg, 1, 100, NULL);
			break;

		case IDSave: //적용후 저장
			AnimTool::s_pThis->Apply(hDlg);

			break;
		case IDCANCEL:
			break;
		}

		break;

	case WM_TIMER:
		if (AnimTool::s_pThis->m_pAnim)
		{
			//AnimTool::s_pThis->m_pAnim->NextFrame();
			InvalidateRect(hDlg, NULL, FALSE);
		}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hDlg, &ps);

		HWND hDisplay = GetDlgItem(hDlg, IDC_DISPLAY);
		HDC hdcDisplay = GetDC(hDisplay);
		 
		RECT rc;
		GetClientRect(hDisplay, &rc);
		int width = rc.right;
		int height = rc.bottom;

		// 더블버퍼
		HDC memDC = CreateCompatibleDC(hdcDisplay);
		HBITMAP memBmp = CreateCompatibleBitmap(hdcDisplay, width, height);
		HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, memBmp);

		Graphics g(memDC);
		g.Clear(Color(255, 255, 255));

		if (AnimTool::s_pThis->m_pAnim && !AnimTool::s_pThis->m_pAnim->m_vecFrm.empty())
		{
			AnimTool::s_pThis->m_pAnim->RenderOnTool(memDC, 0, 0);
		}

		BitBlt(hdcDisplay, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

		SelectObject(memDC, oldBmp);
		DeleteObject(memBmp);
		DeleteDC(memDC);

		ReleaseDC(hDisplay, hdcDisplay);
		EndPaint(hDlg, &ps);
	}
	return TRUE;

	break;
	case WM_CLOSE:
		delete AnimTool::s_pThis;
		AnimTool::s_pThis = nullptr;
		EndDialog(hDlg, 0);
		return TRUE;
	}

	return FALSE;
}

