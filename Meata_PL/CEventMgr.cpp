#include "Global.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUIMgr.h"
#include "AI.h"
#include "CState.h"

CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
}

void CEventMgr::update()
{
	//이전 프레임에서 등록한 Dead Obj들 삭제
	for (auto& obj : m_vecDead)
	{
		delete obj;
	}
	m_vecDead.clear();

	//플레이어와 충돌중 삭제되면 예외가 발생 수정 필요



	// ==========
	// Event 처리
	// ==========
	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	_eve.eEven;
	switch (_eve.eEven)
	{
		//오브젝트생성경우
	case EVENT_TYPE::CREATE_OBJECT:
	{
		//LParam : object adress
		//WParam : Group Type
		CObject* pNewObj = (CObject*)_eve.LParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);

	}
	break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		//LParam : 삭제할 object adress
		//Object를 Dead상태로 변경하고 vector에 모아둔다

		CObject* pDeadObj = (CObject*)_eve.LParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
	break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		//LParam = Next Scene Type
		//Scene 변경
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.LParam);
		//Focus UI 해제
		CUIMgr::GetInst()->SetFocusUI(nullptr);
	}
	break;
	case EVENT_TYPE::CHANGE_AI_STATE:
	{
		//lParm: AI
		//wParam: NextType

		AI* pAI = (AI*)_eve.LParam;
		STATE eNextState = (STATE)_eve.wParam;
		pAI->ChangeState(eNextState);

	}

	}

}

