#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN, //최대로 어둡게
	FAFE_OUT, //최대로 밝게
	NONE
};

struct tCamEffect
{
	CAM_EFFECT eEffect; //카메라 효과
	float fDuration; //효과 진행시간
	float fCurTime; //카메라 효과 현재 진행된 시간
};

class CCamera
{
	SINGLE(CCamera);


private:
	Vec2			   m_vLookAt;//카메라가 보는 위치
	Vec2			   m_vCurLookAt; //이전위치와 현재위치 보정위치
	Vec2			   m_vPrevLookAt; //카메라가 보는 이전프레임 위치
					   
	CObject*		   m_pTargetObj; //카메라 타겟
	CObject*		   Player;
	Vec2			   m_vDiff; //해상도 중심위치와, 카메라, LookAt간의 차이값
					   
	float			   m_fTime; //타겟을 따라가는데 걸리는 시간
	float			   m_fSpeed;
	float			   m_fAccTime;

	list<tCamEffect> m_listCamEffect;
	CTexture* m_pVeilTex; //가림막 텍스처

public:

	void SetLookAt(Vec2 _vLook)
	{
		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();//실제 이동거리 계산
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	} //카메라 위치
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; Player = _pTarget; } //카메라 타겟
	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

	void FadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (_fDuration == 0.f) assert(nullptr);
	}
	void FadeOut(float _fDuration) //몇초에 걸쳐서 할지
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FAFE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (_fDuration == 0.f) assert(nullptr);
	}
public:
	void init();
	void update();
	void render(HDC _dc);


private:
	void CalDiff();

};

