#include "Global.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CCamera.h"
#include "CPathMgr.h"
#include "CResMgr.h"

CAnimation::CAnimation() :
	m_pAnimator(nullptr),
	m_pTex(nullptr),
	m_iCurFrm(0)
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

void CAnimation::render(HDC _dc)
{

	CObject* pObj = m_pAnimator->Getobj();
	Vec2 vPos = pObj->GetPos();
	vPos += m_vecFrm[m_iCurFrm].vOffset;

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


void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, float _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; i++)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLt.x = _vLT.x + (_vStep * (float)i);

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);


	//Animation의 이름 저장
	fprintf(pFile, "[Aniation Name]\n");
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	//Animation이 사용하는 Texture
	fprintf(pFile, "[Texture Name]\n");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");


	//SaveWString(m_pTex->GetKey(), pFile);
	//SaveWString(m_pTex->GetRelativePath(), pFile);

	//프레임 갯수
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, " %d\n", m_vecFrm.size());


	//모든 프레임 정보
	for (size_t i = 0; i < m_vecFrm.size(); i++)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n", (int)i);

		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d,%d\n", (int)m_vecFrm[i].vLt.x, (int)m_vecFrm[i].vLt.y);

		fprintf(pFile, "[Slice Size]\n");
		fprintf(pFile, "%d,%d\n", (int)m_vecFrm[i].vSlice.x, (int)m_vecFrm[i].vSlice.y);

		fprintf(pFile, "[OffSet]\n");
		fprintf(pFile, "%d,%d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", m_vecFrm[i].fDuration);
	}


	//size_t iFrameCount = m_vecFrm.size();
	//fwrite(&iFrameCount, sizeof(size_t), 1, pFile);

	//모든 프레임 정보
	//fwrite(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);
	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	//Animation 이름 읽기
	string str;
	char szBuff[256] = {};

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;

	m_strName = wstring(str.begin(), str.end());

	//참조하는 텍스쳐 이름 및 경로
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;

	wstring strTexKey = wstring(str.begin(), str.end());

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;

	wstring strTexPath = wstring(str.begin(), str.end());

	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);


	//프레임 갯수
	FScanf(szBuff, pFile);
	int iFrameCount = 0;
	fscanf_s(pFile, "%d", &iFrameCount);

	//모든 프레임 정보
	for (size_t i = 0; i < iFrameCount; i++)
	{
		POINT pt = {};

		while (true)
		{
			FScanf(szBuff, pFile);

			if (!strcmp("[Frame Index]", szBuff))
			{
				//fscanf_s(pFile,"%d", )
			}
			else if (!strcmp("[Left Top]", szBuff))
			{

			}
		}
	}
	fclose(pFile);
}
