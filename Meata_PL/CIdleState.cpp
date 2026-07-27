#include "Global.h"

#include "CIdleState.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"

CIdleState::CIdleState() :
	CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	//player 위치 체크
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayer = pPlayer->GetPos();


	// 몬스터 범위안에 들어오면 추적으로 전환
	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 vDiff = vPlayer - vMonPos;
	float fLen = vDiff.Length();


	//플레이어가 인식범위안으로 진입
	if (fLen < pMonster->GetInfo().m_fPerceptionRange)
	{
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}


}

void CIdleState::Enter()
{

}

void CIdleState::Exit()
{

}