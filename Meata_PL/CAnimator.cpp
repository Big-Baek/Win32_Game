#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator() :
	m_pOwner(nullptr),
	m_pCurAnim(nullptr)
{}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::CreateAnimation
(const wstring& _strName, CTexture* _pTex,
	Vec2 _vLT, //왼쪽 상단
	Vec2 _vSliceSize, //자를 크기
	float _vStep,//다음 프레임까지의 거리
	float _fDuration,
	UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);
	if (pAnim != nullptr)
	{
		MessageBox
		(
			nullptr,
			L"이미 애니메이션이 있습니다",
			L"오류",
			MB_OK | MB_ICONWARNING
		);
	}
	//	assert(pAnim == nullptr);

	pAnim = new CAnimation;
	pAnim->m_pAnimator = this;
	pAnim->Create(_strName, _pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}

void CAnimator::LoadAnimation(const wstring& _Name)
{
	CAnimation* pAnim = new CAnimation;
	pAnim->Load(_Name);
	pAnim->m_pAnimator = this;

	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end()) return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat) //재생할 애니메이션, 반복여부
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}


void CAnimator::update()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->update();
		if (!m_bRepeat) return;

	}

}

void CAnimator::finalupdate()
{

}

void CAnimator::render(HDC _dc)
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->render(_dc);
	}
}