#include "Global.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "resource.h"

CCore::CCore() :
	m_hWnd(0),
	m_ptResolution{},
	m_hDC(0),
	m_memDC(0),
	m_arrBrush{},
	m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution; //해상도

	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	//메뉴 생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_MEATAPL));

	m_hDC = GetDC(m_hWnd);

	//이중 버퍼링 용도 비트맵, DC
	m_pMemTex = CResMgr::GetInst()->CreateBuffer(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
	m_memDC = m_pMemTex->GetDC();
	//화면 dc와 호환되는 비트맵 생성
	//m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	//메모리상에 dc를생성. 실제화면 대신 메모리에 먼저 그림을 그림
	//m_memDC = CreateCompatibleDC(m_hDC);
	//메모리 DC에 비트맵을 연결
	//HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	//DeleteObject(hOldBit);

	CreateBrushPen();

	//Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();

	return S_OK;
}

void CCore::progress()
{
	//Manager Update
	CTimeMgr::GetInst()->update(); //DT 계산
	CKeyMgr::GetInst()->update();  //키보드, 마우스 입력상태 갱신
	CCamera::GetInst()->update();  //카메라 위치 갱신

	CSceneMgr::GetInst()->update();
	CCollisionMgr::GetInst()->update();
	CUIMgr::GetInst()->update();

	Clear(); //그리기전에 도화지 초기화

	CSceneMgr::GetInst()->render(m_memDC);
	CCamera::GetInst()->render(m_memDC);
	BitBlt(
		m_hDC,              // 목적지 DC = 실제 화면
		0, 0,               // 목적지 좌표 (화면의 0,0)
		m_ptResolution.x,   // 복사할 너비 = 1280
		m_ptResolution.y,   // 복사할 높이 = 768
		m_memDC,            // 원본 DC = 메모리 DC
		0, 0,               // 원본 좌표 (메모리 비트맵의 0,0)
		SRCCOPY             // 복사 방식 = 그대로 복사
	);

	CTimeMgr::GetInst()->render();
	//이벤트 지연처리
	CEventMgr::GetInst()->update();
}

void CCore::Clear()
{
	//SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK); //배경색 결정
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	//Hollow Brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//Red Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::DockingMenu()
{
	SetMenu(m_hWnd,m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0,0,(long)_vResolution.x,(long)_vResolution.y };//해상도 크기 설정

	//윈도우 스타일고려하여 실제크기 계산 (타이틀바, 등등 스타일에 맞게 RT값이 변경됨)
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);

	//윈도우 위치와 크기 최종설정(시작했을 때 윈도우 위치를 잡아줌 좌상단 0,0 에서 우하단 RT만큼)
	//만약 우하단을 내가 정한사이즈보다 키워도 사용가능영역은 내가 설정한값 그대로임
	SetWindowPos(
		m_hWnd,
		nullptr,
		100, 0,
		rt.right - rt.left,
		rt.bottom - rt.top, 0);//윈도우창 크기 결정
}
