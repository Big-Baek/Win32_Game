#include "Global.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr() :
	m_llPrevCount{},
	m_llCurCount{},
	m_llFrequency{},
	m_dDT(0.0),
	iFPS(0)
{}
CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	//현재까지 카운트 (누적카운트)
	QueryPerformanceCounter(&m_llPrevCount);
	//초당 카운트 횟수(카운트 / 초)
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	
	//정수 나눗셈하면 무조건 0만 나오니 실수형으로 변환
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) 
		  / (double)m_llFrequency.QuadPart;

	// FPS = dDT의 역수
	// 누적 카운트 / 초당카운트 = 현재까지의 시간
	// 누적카운트 - 이전까지카운트 / 초당 카운트 = 카운트 사이의 찰나의 시간

	m_llPrevCount = m_llCurCount;


	//디버그모드에서만 사용가능


#ifdef _DEBUG

	if (m_dDT > (1. / 60.))
	{
		m_dDT = (1. / 60.);
	}

#endif
}

void CTimeMgr::render()//fps 렌더링
{
	++m_iCallCount;
	m_dAcc += m_dDT;// DT 누적
	if (m_dAcc >= 1.)//1초에 한번씩 호출횟수 확인
	{
		iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;


		wchar_t szBuffer[255] = {};


		swprintf_s(szBuffer, L"FPS: %d, DT: %f", iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
