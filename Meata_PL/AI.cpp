#include "Global.h"
#include "AI.h"
#include "CState.h"

AI::AI()
{
	m_eType = COMPONENT_TYPE::AI;
}

AI::~AI()
{
}

void AI::update()
{
	CComponent::update();
	m_pCurState->update();
}

void AI::AddState(CState* _pState)
{
	CState* pState = GetState(_pState->GetType());
	assert(!pState);
	

	m_mapState.insert(make_pair(_pState->GetType(), _pState));
	_pState->m_pAI = this;
}

CState* AI::GetState(STATE _eState)
{
	map<STATE, CState*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end()) return nullptr;

	return iter->second;
}

void AI::ChangeState(STATE _eNextState)
{
	CState* pNextState = GetState(_eNextState);

	assert(m_pCurState != pNextState);
	m_pCurState->Exit();
	m_pCurState = pNextState;
	m_pCurState->Enter();
}

void AI::SetCurState(STATE _eState)
{
	m_pCurState = GetState(_eState);
	assert(m_pCurState);

}


