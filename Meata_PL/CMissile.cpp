#include "CMissile.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include <cmath>
#include <numbers>

CMissile::CMissile() :
	m_fMisSpeed(300.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMissile::~CMissile()
{
}

void CMissile::SetDir(int _iDir, int count)//총갯수, 몇번째인지
{

	//각도는 쏠 180 / 미사일+1 로 알 수 있다
	//1발 쏠거라면 위로만 가니 180 / 1+1 = 90 이런식으로
	float angle = 180 / ((float)_iDir+1);

	/*
	* c++의 삼각함수는 라디안을 인자로 받는다.
	* 1라디안은 호의길이 == 반지름일때의 각도로 항상 일정하다(57.3).
	* 2 pi r = 전체호의 길이 = 360도 이므로
	* r = 360/2 pi = 1라디안이 나온다
	*/

	//  rad = angle x pi / 180
	//  degree = rad x 180 / pi
	double radian = angle * count *  std::numbers::pi/ 180.f;
	m_fDir.x = -1 * cos(radian);//x좌표는 r x cos() 이므로 -1은 반지름
	m_fDir.y = -1 * sin(radian);
}

void CMissile::update()
{
	Vec2 vPos = GetPos();
	vPos.x += m_fDir.x * m_fMisSpeed * fDT;
	vPos.y += m_fDir.y * m_fMisSpeed * fDT;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Ellipse(_dc, (int)(m_vPos.x - m_vScale.x / 2.f), (int)(m_vPos.y - m_vScale.y / 2.f),
		(int)(m_vPos.x + m_vScale.x / 2.f), (int)(m_vPos.y + m_vScale.y / 2.f));

	ComponentRender(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}
