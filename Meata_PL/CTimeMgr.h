#pragma once

//매순간 Delta Time을 구해야함
//Delta Time은 프레임당 시간

// 1초 / fps

/*
* ex) 1초에 100을 이동해야하는데 200FPS가 나온다면
* 매 프레임 0.5씩 이동해야한다
* 100*Delta Time 하면 된다
*/



class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDT;
	double m_dAcc;
	UINT m_iCallCount;
	UINT iFPS;


public:
	void init();
	void update();
	void render();


	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }


	//FPS:		 1초당 프레임
	//DeltaTime: 1프레임당 시간
};

