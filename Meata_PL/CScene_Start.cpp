#include "Global.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CActor.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"
#include "CKeyMgr.h" 
#include "CSceneMgr.h"

#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CRigidBody.h"

#include "CGround.h"
#include "CActor.h"

CScene_Start::CScene_Start() :
	m_bUseForce(false),
	m_fForceRadius(500.f),
	m_fForce(500.f),
	m_fCurRadius(0.f)
{
	//CCollisionMgr::GetInst()->Reset();
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{

	//if (KEY_TAP(KEY::ENTER))
	//{
	//	ChangeScene(SCENE_TYPE::TOOL);
	//}

	if (KEY_TAP(KEY::LBTN))
	{
		/*	Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
			CCamera::GetInst()->SetLookAt(vLookAt);*/
	}

	if (KEY_HOLD(KEY::LBTN)) //힘을 생성
	{
		m_bUseForce = true;
		CreateForce();
	}//비생성
	else
	{
		m_bUseForce = false;
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		const vector<CActor*>& vecObj = GetActorOfGroup((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); j++)
		{
			if (!vecObj[j]->IsDead())
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();
					if (vDiff.Length() < m_fForceRadius)
					{
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce * fRatio;

						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
					}
				}


				vecObj[j]->update();
			}
		}
	}
}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);

	if (!m_bUseForce) return;

	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurRadius += m_fForceRadius * 2.f * fDT;
	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}

	Vec2 RenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

	Ellipse(_dc,
		(int)(RenderPos.x - m_fCurRadius),
		(int)(RenderPos.y - m_fCurRadius),
		(int)(RenderPos.x + m_fCurRadius),
		(int)(RenderPos.y + m_fCurRadius));


}

void CScene_Start::Enter()
{
	CCore::GetInst()->DockingMenu();

	//플레이어 배치
	CActor* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(10.f, 10.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);

	//카메라 
	//CCamera::GetInst()->SetTarget(pObj);


	//몬스터 배치
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	//CMonster* pMon = CMonFactory::CreaterMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	//AddObject(pMon, GROUP_TYPE::MONSTER);

	//땅 배치
	CObject* pGround = new CGround;
	pGround->SetName(L"Ground");
	pGround->SetPos(Vec2(640.f, 584.f));
	pGround->SetScale(Vec2(200.f, 60.f));
	AddObject(pGround, GROUP_TYPE::GROUND);




	//int iMonsterCount = 1; //몬스터 갯수
	//float fObjectScale = 50.f; //크기
	//AI* pAI = new AI;
	//pAI->AddState(new CIdleState);
	//Vec2 vResolution = CCore::GetInst()->GetResolution();
	//CMonster* pMonsterObj = nullptr;
	//for (int i = 0; i < iMonsterCount; i++)
	//{
	//	//Monster Object 추가
	//	pMonsterObj = new CMonster;
	//	pMonsterObj->SetName(L"Monster");
	//	pMonsterObj->SetScale(Vec2(fObjectScale, fObjectScale));
	//	pMonsterObj->SetPos(vResolution / 2.f - Vec2(0.f, 300.f));
	//	pMonsterObj->SetAI(pAI);
	//	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	//}

	//타일 로딩
	//LoadTile(L"Tile\\Start.tile");

	//충돌지정
	// Player 그룹과 Monster 그룹간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);


	//카메라 look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	//카메라 효과 지정
	//CCamera::GetInst()->FadeOut(5.f);
	//CCamera::GetInst()->FadeIn(5.f);
	Start();
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);




}



