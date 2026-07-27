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
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\BPlayer.bmp");


	CreateCollider();
	GetCollider()->SetOffSetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(40.f, 60.f));

	CreateRigidBody();

	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Jelda1.bmp");

	CreateAnimator();

	//GetAnimator()->LoadAnimation(L"animation\\player_idle_left.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_idle_right.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_walk_right.anim");


	//GetAnimator()->CreateAnimation(L"IDLE_LEFT", m_pTex, Vec2(0.f, 65.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 3);
	//GetAnimator()->CreateAnimation(L"IDLE_RIGHT", m_pTex, Vec2(0.f, 195.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 3);
	//GetAnimator()->CreateAnimation(L"WALK_LEFT", m_pTex, Vec2(0.f, 325.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	//GetAnimator()->CreateAnimation(L"WALK_RIGHT", m_pTex, Vec2(0.f, 455.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);

	////애니메이션 저장해보기
	//GetAnimator()->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player_idle_left.anim");
	//GetAnimator()->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player_idle_right.anim");
	//GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player_walk_left.anim");
	//GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player_walk_right.anim");





	CreateGravity();

	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	//pAnim->GetFrame(0).vOffset = Vec2(0.f ,- 20.f); //오프셋 적용 -> 0프레임만 Y축 -20만큼 적용
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	update_move();
	update_state();
	update_animation();



	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));
	}

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
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

void CPlayer::update_state()
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

void CPlayer::render(HDC _dc)
{

	//컴포넌트(충돌체, etc 등등)
	ComponentRender(_dc);
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\BPlayer.bmp");

	//Vec2 vPos = GetPos();
	//vPos = CCamera::GetInst()->GetRealPOs(vPos);

	//float width = (float)pTex->Width();
	//float height = (float)pTex->Height();

	//BLENDFUNCTION bf = {};

	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 127;//투명도

	//AlphaBlend(_dc,
	//	int(vPos.x - width / 2.f),
	//	int(vPos.y - height / 2.f),
	//	int(width), int(height),
	//	pTex->GetDC(),
	//	0, 0, int(width), int(height),
	//	bf);
}


//기존 렌더 함수
// 
//좌상단의 경우 좌표가 음수가 될수 있어 int로 캐스팅
//int iWidth = (int)m_pTex->Width();
//int iHeight = (int)m_pTex->Height();

//Vec2 vPos = GetPos();

//BitBlt(_dc,
//	int(vPos.x - (float)(iWidth / 2)),
//	int(vPos.y - (float)(iHeight / 2)),
//	iWidth, iHeight,
//	m_pTex->GetDC(),
//	0, 0, SRCCOPY);

//TransparentBlt(_dc,
//	int(vPos.x - (float)(iWidth / 2)),
//	int(vPos.y - (float)(iHeight / 2)),
//	iWidth, iHeight,
//	m_pTex->GetDC(),
//	0, 0, iWidth, iHeight,
//	RGB(255, 0, 255));