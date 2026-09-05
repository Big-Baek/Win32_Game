#include "Global.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CActor.h"
#include "CTimeMgr.h"
#include "CCamera.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include <fstream>
#include <sstream>

CAnimation::CAnimation() :
	m_pAnimator(nullptr),
	m_pTex(nullptr),
	m_iCurFrm(0),
	m_fAccTime(0)
{}

CAnimation::~CAnimation()
{}

void CAnimation::update()
{

	m_fAccTime += fDT;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = 0;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}
}

void CAnimation::Tool_update()
{
	float DeltaTime = fDT;

	double OriginHZ = 1.0 / DeltaTime;
	double TargetHZ = 10.0;

	double factor = OriginHZ / TargetHZ;

	m_fAccTime += DeltaTime * factor;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = 0;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;
	}
}

void CAnimation::render(HDC _dc)
{

	CActor* pObj = m_pAnimator->GetOwner();
	Vec2 vPos = pObj->GetPos();
	vPos += m_vOffset;

	// 카메라 변환
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	Graphics g(_dc);

	// 스프라이트시트에서 잘라낼 영역
	Rect src(
		(int)m_vecFrm[m_iCurFrm].vLt.x,
		(int)m_vecFrm[m_iCurFrm].vLt.y,
		(int)m_vecFrm[m_iCurFrm].vSlice.x,
		(int)m_vecFrm[m_iCurFrm].vSlice.y
	);

	// 화면에 그릴 영역
	Rect dst(
		(int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f),
		(int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f),
		(int)m_vecFrm[m_iCurFrm].vSlice.x,
		(int)m_vecFrm[m_iCurFrm].vSlice.y
	);

	g.DrawImage(m_pTex->GetImg(), dst, src.X, src.Y, src.Width, src.Height, UnitPixel);
}

void CAnimation::accrender(HWND _dc)
{
	wchar_t szBuffer[255] = {};
	float a = fDT;
	swprintf_s(szBuffer, L"Acc: %f fdt: %f", m_fAccTime, a);
	SetWindowText(_dc, szBuffer);
}

void CAnimation::RenderOnTool(HDC _dc, int x, int y)
{
	Graphics g(_dc);

	tAnimFrm& frm = m_vecFrm[m_iCurFrm];

	// src: 스프라이트 시트에서 잘라낼 영역
	Rect src(
		(int)frm.vLt.x,
		(int)frm.vLt.y,
		(int)frm.vSlice.x,
		(int)frm.vSlice.y
	);

	// dst: Picture Control 안에 그릴 위치
	Rect dst(
		x,
		y,
		(int)frm.vSlice.x,
		(int)frm.vSlice.y
	);

	g.DrawImage(m_pTex->GetImg(), dst, src.X, src.Y, src.Width, src.Height, UnitPixel);
}

void CAnimation::Create(const wstring& Name, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vOffset, float _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;
	m_strName = Name;
	m_vOffset = _vOffset;

	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; i++)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLt.x = _vLT.x + (_vStep * (float)i);

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Save(const std::wstring& name)
{
	//저장할 위치
	std::wstring path = CPathMgr::GetInst()->GetContentPath();
	path += L"Animation\\";
	path += name;
	path += L".anim";

	std::wofstream file(path);
	if (!file.is_open())
	{
		// 여기서 메시지 띄우거나 그냥 return 해도 됨
		return;
	}

	file << L"[Animation Name]: " << m_strName << L"\n";
	file << L"[Texture Name]: " << m_pTex->GetKey() << L"\n";
	file << L"[Texture Path]: " << m_pTex->GetRelativePath() << L"\n";
	file << L"[Frame Count]: " << m_vecFrm.size() << L"\n";
	file << endl;

	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		const auto& frm = m_vecFrm[i];

		file << L"[Frame Index]: " << i << L"\n";
		file << L"[Left Top]: " << frm.vLt.x << L"," << frm.vLt.y << L"\n";
		file << L"[Slice Size]: " << frm.vSlice.x << L"," << frm.vSlice.y << L"\n";
		file << L"[Duration]: " << frm.fDuration << L"\n";
		file << endl;
	}
}

void CAnimation::Load(const wstring& name)
{
	//전체 경로를 통해서 파일을 열기
	wstring path = CPathMgr::GetInst()->GetContentPath();
	path += L"Animation\\";
	path += name;
	path += L".anim";

	wifstream file(path);
	if (!file.is_open())
		return;

	wstring line;

	//:뒤의 값만 추출
	auto GetValue = [&](const wstring& src)
		{
			size_t pos = src.find(L":");
			if (pos == wstring::npos) return wstring();

			wstring val = src.substr(pos + 1);

			// 앞뒤 공백 제거
			size_t start = val.find_first_not_of(L" \t");
			size_t end = val.find_last_not_of(L" \t");

			if (start == wstring::npos) return wstring();
			return val.substr(start, end - start + 1);
		};

	// [Animation Name]: Neo_Cold
	getline(file, line); //한라인을 읽음
	m_strName = GetValue(line); //라인에서 :앞쪽을 제거한 나머지 이름

	// [Texture Name]: Neo_Cold
	getline(file, line);
	wstring texKey = GetValue(line);

	// [Texture Path]: D:\...\Neo_Cold.png
	getline(file, line);
	wstring texPath = GetValue(line);

	m_pTex = CResMgr::GetInst()->CreateAbsolute(texKey, texPath);

	// [Frame Count]: 16
	getline(file, line);
	int frameCount = stoi(GetValue(line));

	getline(file, line); //빈 줄 스킵

	m_vecFrm.clear();
	m_vecFrm.reserve(frameCount);

	tAnimFrm frm{};

	for (int i = 0; i < frameCount; ++i)
	{
		wstring value;

		// [Frame Index]
		getline(file, line);

		// [Left Top]
		getline(file, line);
		value = GetValue(line);
		{
			wstringstream ss(value); 
			wchar_t comma;
			ss >> frm.vLt.x >> comma >> frm.vLt.y;
		}

		// [Slice Size]
		getline(file, line);
		value = GetValue(line);
		{
			wstringstream ss(value);
			wchar_t comma;
			ss >> frm.vSlice.x >> comma >> frm.vSlice.y;
		}

		// [Duration]
		getline(file, line);
		frm.fDuration = stof(GetValue(line));

		m_vecFrm.push_back(frm);

		// 빈 줄 스킵
		getline(file, line);
	}

}
