#include "CTraceStae.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CTimeMgr.h"

CTraceStae::CTraceStae() :
	CState(MON_STATE::TRACE)
{
}

CTraceStae::~CTraceStae()
{
}

void CTraceStae::update()
{
	//타겟팅된 플레이어 추적

	//CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	//Vec2 vPlyaerPos = pPlayer->GetPos();

	//Vec2 vMonPos = GetMonster()->GetPos();

	//Vec2 vMonDir = vPlyaerPos - vMonPos;
	//vMonDir.Normalize();

	//vMonPos += vMonDir * GetMonster()->GetInfo().m_fSpeed * fDT;

	//GetMonster()->SetPos(vMonPos);
}

void CTraceStae::Enter()
{

}

void CTraceStae::Exit()
{

}