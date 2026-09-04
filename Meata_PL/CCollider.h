#pragma once

class CActor;

class CCollider
{
private:
	static UINT g_iNextID;

	CActor* m_pOwner;//충돌체를 가진 오브젝트

	Vec2 m_vOffsetPos; //오브젝트로부터 상대위치. 일정하다
	Vec2 m_vFinalPos; //매 프레임 계산
	Vec2 m_vScale;

	UINT m_iID; //충돌체 고유아이디
	int  m_iCol; //충돌중인 숫자

	bool m_bActive;
public:

	void SetOffSetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }

	CActor* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

	void SetPen(PEN_TYPE _Pen);
	void SetBrush(BRUSH_TYPE _Brush);


	void finalupdate();
	void render(HDC _dc);

	void OnCollision(CCollider* _pOther);//충돌 중인 경우 호출
	void OnCollisionEnter(CCollider* _pOther);//충돌진입시
	void OnCollisionExit(CCollider* _pOther);//충돌탈출시

	PEN_TYPE _ePenType;
	BRUSH_TYPE _eBrushType;

	CCollider& operator = (CCollider& _origin) = delete; //대입연산자 구현 방어(대입불가)

public:
	CCollider();
	CCollider(const CCollider& _origin); //복사생성자

	~CCollider();

	friend class CActor;

};

