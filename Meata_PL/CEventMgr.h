#pragma once


struct tEvent
{
	EVENT_TYPE eEven; //이벤트 타입
	DWORD_PTR LParam; //오브젝트 주소
	DWORD_PTR wParam; //오브젝트 타입
};

class CEventMgr
{
	SINGLE(CEventMgr)
private:

	vector<tEvent> m_vecEvent; //이벤트가 발생한 오브젝트들을 모아두는
	vector<CObject*> m_vecDead; //삭제될 오브젝트들을 모아두는

public:
	void update();//이벤트 일괄적용
	void AddEvent(tEvent& _eve) { m_vecEvent.push_back(_eve); }//이번트 추가


private:
	void Excute(const tEvent& _eve);
	
};

