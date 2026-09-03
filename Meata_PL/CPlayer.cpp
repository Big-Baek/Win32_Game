#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CTexture.h"
#include "CCore.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"


CPlayer::CPlayer()
	:m_eCurState(PLAYER_STATE::IDLE),
	m_iDir(1),
	m_iPrevDir(1),
	m_ePrevState(PLAYER_STATE::WALK)
{
	//texture 로딩

	CreateCollider();
	CreateRigidBody();
	CreateAnimator();

	GetCollider()->SetOffSetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(40.f, 60.f));

	GetAnimator()->LoadAnimation(L"Neo_Cold");

	//m_pTex = CResMgr::GetInst()->CreateRelative(L"Neo_Cold", L"Texture\\Neo_Cold.png");
	//GetAnimator()->CreateAnimation(L"Cold", m_pTex, Vec2(0.f, 0.f), Vec2(35.f, 35.f), 35.f, 0.1f, 16);

	CreateGravity();
	GetAnimator()->Play(L"Neo_Cold", true);
}

CPlayer::~CPlayer()
{}

void CPlayer::update()
{
	update_move();
	update_state();
	//update_animation();


	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));
	}

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	CObject::render(_dc);

	//if (m_pTex && m_pTex->m_pImg)
	//{
	//	Gdiplus::Graphics g(_dc);
	//	g.DrawImage(m_pTex->m_pImg, m_vPos.x, m_vPos.y);
	//}
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

void CPlayer::update_state()//이후 컨트롤러로 이전
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

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}
	if (KEY_TAP(KEY::A))
	{
		//pRigid->AddForce(Vec2(200.f, 0.f));
		pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}
	if (KEY_HOLD(KEY::D))
	{
		//pRigid->AddForce(Vec2(200.f, 0.f));
		pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
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

void CPlayer::update_Gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f, 500.f));
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

//void CPlayer::Player_render(HDC _dc)
//{
//	CObject::render(_dc);
//
//	if (m_pTex && m_pTex->m_pImg)
//	{
//		Gdiplus::Graphics g(_dc);
//		g.DrawImage(m_pTex->m_pImg, m_vPos.x, m_vPos.y);
//	}
//}

//void CPlayer::p_render(HDC _dc)
//{
//
//		if (m_pTex && m_pTex->m_pImg)
//		{
//			Graphics g(_dc);
//			g.DrawImage(m_pTex->m_pImg, m_vPos.x, m_vPos.y);
//		}
//	
//}