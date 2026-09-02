#include "Global.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

CCamera::CCamera() :
	m_pTargetObj(nullptr),
	m_fTime(0.5f),
	m_fSpeed(0.5f),
	m_fAccTime(0.5f),
	m_pVeilTex(nullptr)
{
}
CCamera::~CCamera()
{
}
void CCamera::init()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil",
		(UINT)vResolution.x,
		(UINT)vResolution.y);
}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}
	else
	{
		if (KEY_HOLD(KEY::UP)) m_vLookAt.y -= 500.f * fDT;
		if (KEY_HOLD(KEY::DOWN)) m_vLookAt.y += 500.f * fDT;
		if (KEY_HOLD(KEY::LEFT)) m_vLookAt.x -= 500.f * fDT;
		if (KEY_HOLD(KEY::RIGHT)) m_vLookAt.x += 500.f * fDT;
	}
	if (KEY_HOLD(KEY::B))
	{
		if (m_pTargetObj) m_pTargetObj = nullptr;
		else m_pTargetObj = Player;
	}

	//화면 중앙좌표와 카메라 LookAt 좌표간의 차이 계산
	CalDiff();

}

void CCamera::render(HDC _dc)
{
	if (m_listCamEffect.empty()) return;

	//시간 누적값
	tCamEffect& ef = m_listCamEffect.front();
	ef.fCurTime += fDT;

	float fRatio = 0.f; //이펙트 진행비율
	fRatio = ef.fCurTime / ef.fDuration;

	if (fRatio < 0.f) fRatio = 0.f;
	if (fRatio > 1.f) fRatio = 1.f;

	int iAlpha = 0;

	if (ef.eEffect == CAM_EFFECT::FAFE_OUT)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if (ef.eEffect == CAM_EFFECT::FADE_IN)
	{
		iAlpha = (int)(255.f * (1.f - fRatio));
	}


	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;//투명도

	//AlphaBlend(_dc, 0, 0,
	//	(int)m_pVeilTex->Width(),
	//	(int)m_pVeilTex->Height(),
	//	m_pVeilTex->GetDC(), 0, 0,
	//	(int)m_pVeilTex->Width(),
	//	(int)m_pVeilTex->Height(),
	//	bf);

	if (ef.fDuration < ef.fCurTime)
	{
		//효과 종료
		m_listCamEffect.pop_front();
	}
}

void CCamera::CalDiff()
{
	//이전 LookAt 와 현재 Look 의 차이값을 보정해서 현재의 LookAt를 구한다.

	m_fAccTime += fDT;
	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		}
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2; //화면 정중앙 위치

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}