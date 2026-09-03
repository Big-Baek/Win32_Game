#pragma once

class CAnimator;
class CTexture;


struct tAnimFrm
{
	Vec2 vLt; //좌상단
	Vec2 vSlice; //우하단
	float fDuration;
};

class CAnimation
{
private:

	wstring				m_strName;		//애니메이션 이름
	CAnimator*			m_pAnimator;	//자신을 사용하는 애니메이터
	CTexture*		    m_pTex;			//스프라이트 시트 텍스쳐
	int					m_iCurFrm;		//현재 프레임
	float				m_fAccTime;		//프레임간 시간
	Vec2				m_vOffset;		//기준좌표로부터의 상대좌표	

public:
	vector<tAnimFrm>	m_vecFrm;		//매 프레임정보 벡터

	void SetName(const wstring& _strName) { m_strName = _strName; }
	void SetFrame(int _iFrameInx)
	{
		m_iCurFrm = _iFrameInx;
		m_fAccTime = 0.f;
	}

	const wstring& GetName() { return m_strName; }
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }

public:

	void update();
	void Tool_update();

	void render(HDC _dc);
	void accrender(HWND _dc);
	void RenderOnTool(HDC _dc, int x, int y);

	void Create(const wstring& Name, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vOffset, float _vStep, float _fDuration, UINT _iFrameCount);
	//이름, 텍스쳐, 좌상단, 우하단, 상대좌표, 다음 프레임 간격, 프레임간 시간, 전체 프레임수
	
	void Save(const wstring& _Name); //파일이름만 받아서 Content폴더 안에 저장
	void Load(const wstring& _strRelativePath);

public:

	CAnimation();
	~CAnimation();

	friend class CAnimator;
	friend class AnimTool;
};

