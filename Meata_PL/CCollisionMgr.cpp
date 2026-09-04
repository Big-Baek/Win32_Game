#include "Global.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CActor.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr() :
	m_arrCheck{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::init()
{

}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	//행,열로 표를 작성

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	//둘중 더 작은그룹값으로 행을 지정
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	//인덱스가 행. 값이 열
	//정수로 표현하면 42억까지의 변수 한개를 표현할 수 있지만
	//비트로 표현하면 0~1의 체크박스 32개를 표현할수 있다
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

void CCollisionMgr:: Reset()
{
	//vector초기화와 비슷한동작.
	//인자1. 초기화할 메모리 시작주소, 2. 채울값, 3. 채울 바이트 수
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	map<ULONGLONG, bool>::iterator iter;

	const vector<CActor*>& vecLeft = pCurScene->GetActorOfGroup(_eLeft);
	const vector<CActor*>& vecRight = pCurScene->GetActorOfGroup(_eRight);

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		if (vecLeft[i]->GetCollider() == nullptr) continue;
		for (size_t j = 0; j < vecRight.size(); j++)
		{
			//충돌체가 없거나 자기자신과 충돌일 경우
			if (vecRight[j]->GetCollider() == nullptr || vecLeft[i] == vecRight[j]) continue;

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();
			//두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);
			if (iter == m_mapColInfo.end())//못찾음 == 이전프레임에 충돌 안함
			{
				m_mapColInfo[ID.ID] = false;
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			//충돌할경우
			if (IsCollision(pLeftCol, pRightCol))
			{
				if (iter->second)//이전에도 충돌
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else//첫 충돌
				{
					//둘중 하나가 삭제예정이라면 충돌하지 않은걸로 처리
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else//충돌 안함
			{
				if (iter->second)//이전에는 충돌
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f &&
		abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}
	return false;
}