#pragma once
class CCollider;

union COLLIDER_ID
{
	struct
	{
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};


class CCollisionMgr
{
	SINGLE(CCollisionMgr)

private:

	//충돌체 간의 이전프레임 충돌 정보

	map<ULONGLONG, bool> m_mapColInfo; //충돌체간의 이전프레임 충돌 정보

	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; //그룹간 충돌체크 매트릭스
public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset();

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);

};

