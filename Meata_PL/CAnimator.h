#pragma once
#include "Global.h"


class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:

	map<wstring, CAnimation*> m_mapAnim;  //모든 anim
	CAnimation*				  m_pCurAnim; //현재 재생중인 anim
	CObject*				  m_pOwner;   //소유 obh
	bool m_bRepeat; //반복재생 여부

public:
	CObject* Getobj() { return m_pOwner; }



	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT,Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	void LoadAnimation(const wstring& _strRelativePath);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName ,bool _bRepeat); //이 애니메이션을 플레이


	void update();
	void finalupdate();
	void render(HDC _dc);

	
public:
	CAnimator();
	~CAnimator();

	friend class CObject;

};

