#include "Global.h"
#include "CMonFactory.h"
#include "CMonster.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceStae.h"
#include "CRigidBody.h"

CMonFactory::CMonFactory()
{
}

CMonFactory::~CMonFactory()
{
}

CMonster* CMonFactory::CreaterMonster(MON_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMon = nullptr;

	switch (_eType)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.m_fAtt = 10.f;
		info.m_fHP = 10.f;
		info.m_fAttRange = 50.f;
		info.m_fPerceptionRange = 300.f; info.m_fHP = 100.f;
		info.m_fSpeed = 150.f;
		pMon->SetMonInfo(info);

		//RigidBody
		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);



		//AI
		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceStae);
		pAI->SetCurState(STATE::IDLE);
		//pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::RANGE:
		break;
	default:
		break;
	}
	assert(pMon);
	return pMon;
}
