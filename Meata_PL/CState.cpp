#include "Global.h"
#include "CState.h"
#include "AI.h"

CState::CState(STATE _eState) :
	m_eState(_eState)
{
}

CState::~CState()
{
}

CMonster* CState::GetMonster()
{
	return 	m_pAI->GetOwner();
}

void CState::update()
{

}