#include "CPlayer.h"

#include "CMissile.h"
#include "CKeyMgr.h"

CPlayer::CPlayer()
	:m_eCurState(PLAYER_STATE::IDLE),
	m_iDir(1),
	m_iPrevDir(1),
	m_ePrevState(PLAYER_STATE::WALK)
{
	CreateRigidBody();
	CreateController();
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetOffSetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(40.f, 60.f));

	GetAnimator()->LoadAnimation(L"Neo_Cold");

	m_pRigidBody->EnableGravity(true); //중력 활성화
	GetAnimator()->Play(L"Neo_Cold", true);
}

CPlayer::~CPlayer()
{}

void CPlayer::BeginPlay()
{
	CActor::BeginPlay();
}

void CPlayer::update()
{
	m_pController->update();
	update_state();
	//update_animation();


	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));
	}

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	CActor::render(_dc);
}

void CPlayer::CreateMissile(int n)
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;
	for (int i = 1; i < n + 1; i++)
	{
		CMissile* pMissile = new CMissile;
		pMissile->SetName(L"Missile_Player");
		pMissile->SetPos(vMissilePos);
		pMissile->SetScale(Vec2(25.f, 25.f));
		pMissile->SetDir(n, i);//총 갯수, 몇번째인지

		CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
	}
}

void CPlayer::update_state()//이후 스테이트머신으로 변경예정
{
	if (KEY_HOLD(KEY::A))
	{
		m_iDir = -1;
		if (m_eCurState != PLAYER_STATE::JUMP)
			m_eCurState = PLAYER_STATE::WALK;
		return;
	}
	if (KEY_HOLD(KEY::D))
	{
		m_iDir = 1;
		if (m_eCurState != PLAYER_STATE::JUMP)
			m_eCurState = PLAYER_STATE::WALK;
		return;
	}
	if (GetRigidBody()->GetSpeed() == 0.f)
	{
		m_eCurState = PLAYER_STATE::IDLE;
		return;
	}
	if (KEY_TAP(KEY::SPACE))
	{
		m_eCurState = PLAYER_STATE::JUMP;
		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -300.f));
		}
	}
}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir) return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir == -1)GetAnimator()->Play(L"IDLE_LEFT", true);
		else GetAnimator()->Play(L"IDLE_RIGHT", true);
	}
	break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == -1)GetAnimator()->Play(L"WALK_LEFT", true);
		else GetAnimator()->Play(L"WALK_RIGHT", true);
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		if (m_iDir == -1)GetAnimator()->Play(L"WALK_LEFT", true);
		else GetAnimator()->Play(L"WALK_RIGHT", true);
	}
	break;

	case PLAYER_STATE::ATTACK:
		break;
	case PLAYER_STATE::DEAD:
		break;


	default:
		break;
	}
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (_pOther->GetObj()->GetName() == L"Ground")
	{
		Vec2 vPos = GetPos();
		if (vPos.y <= pOtherObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;

		}
	}
}