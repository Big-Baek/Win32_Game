#include "Global.h"
#include "AnimTool.h"
#include "Resource.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CResMgr.h"

AnimTool* AnimTool::s_pThis;

float GetDlgFloat(HWND hDlg, int nID)
{
	wchar_t szBuf[64] = {};
	GetDlgItemText(hDlg, nID, szBuf, 64);
	return static_cast<float>(_wtof(szBuf));
}

AnimTool::AnimTool() :
	m_pTex(nullptr),
	m_pAnim(nullptr)
{}


AnimTool::~AnimTool()
{
	if (m_pAnim) delete m_pAnim;
}

void AnimTool::m_LoadImage(wchar_t* _path)
{
	m_strTexPath = _path;
}

void AnimTool::Apply(HWND hDlg)
{
	GetDlgItemText(hDlg, IDC_Name, AnimName, 256);

	m_pTex = CResMgr::GetInst()->CreateAbsolute(AnimName, m_strTexPath);
	if (m_pAnim)
	{
		delete m_pAnim;
	}

	m_pAnim = new CAnimation;
	m_pAnim->Create(
		AnimName,
		m_pTex,														    //스프라이트시트
		Vec2(GetDlgFloat(hDlg, IDC_SP_X), GetDlgFloat(hDlg, IDC_SP_Y)), //좌상단 좌표
		Vec2(GetDlgFloat(hDlg, IDC_EP_X), GetDlgFloat(hDlg, IDC_EP_Y)), //우하단 좌표
		GetDlgFloat(hDlg, IDC_Step),								    //스텝간격
		GetDlgFloat(hDlg, IDC_Duration),							    //프레임간 재생간격
		GetDlgFloat(hDlg, IDC_Count));									//총 프레임갯수

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
		case IDC_SheetFind: //스프라이트 시트 선택후 m_pImage로 저장
		{
			OPENFILENAME ofn = { 0 };
			wchar_t szFile[MAX_PATH] = { 0 };

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFilter = L"PNG Files\0*.png\0"; //탐색할 파일형식
			ofn.lpstrInitialDir = L"D:\\Git Fork\\Win32_Game_Metal\\Content\\Texture"; //초기화 주소
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST; //확인 or 취소

			if (GetOpenFileName(&ofn))
			{
				AnimTool::s_pThis->m_LoadImage(szFile);
			}
		}
		return TRUE;

		case IDApply: //적용
			AnimTool::s_pThis->Apply(hDlg);//애니메이션 생성
			SetTimer(hDlg, 1, 100, NULL); //타이머를 100ms 마다 호출 (애니메이션 재생)
			break;

		case IDSave: //저장
			AnimTool::s_pThis->Apply(hDlg);
			AnimTool::s_pThis->m_pAnim->Save(AnimTool::s_pThis->AnimName);
			break;
		case IDCANCEL:
			break;
		}

		break;

	case WM_TIMER: //0.1초마다 호출, WM_PAINT를 호출하며 애니메이션 재생
		if (AnimTool::s_pThis->m_pAnim)
		{
			AnimTool::s_pThis->m_pAnim->Tool_update(); //애니메이션 업데이트(프레임 이동)
			InvalidateRect(hDlg, NULL, FALSE); //WM_PAINT 호출
		}
		AnimTool::s_pThis->m_pAnim->accrender(hDlg);

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hDlg, &ps);

		HWND hDisplay = GetDlgItem(hDlg, IDC_DISPLAY); //다이어그램 윈도우 핸들 가져오기
		HDC hdcDisplay = GetDC(hDisplay); //다이어그램 DC 가져오기

		RECT rc;
		GetClientRect(hDisplay, &rc); //다이어그램 좌표정보 가져오기
		int width = rc.right;
		int height = rc.bottom;

		// 더블버퍼
		HDC memDC = CreateCompatibleDC(hdcDisplay); //메모리 DC 생성
		HBITMAP memBmp = CreateCompatibleBitmap(hdcDisplay, width, height); //비트맵 생성
		HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, memBmp);

		Graphics g(memDC);
		g.Clear(Color(255, 255, 255));

		if (AnimTool::s_pThis && AnimTool::s_pThis->m_pAnim && !AnimTool::s_pThis->m_pAnim->m_vecFrm.empty())
		{
			AnimTool::s_pThis->m_pAnim->RenderOnTool(memDC, width/2.f, height/2.f);
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
		DestroyWindow(hDlg);
		return TRUE;
	}

	return FALSE;
}

