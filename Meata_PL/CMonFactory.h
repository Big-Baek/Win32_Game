#pragma once

class CMonster;

enum class MON_TYPE
{
	NORMAL,
	RANGE,

};

class CMonFactory
{
private:
	CMonFactory();
	~CMonFactory();

public:
	static CMonster* CreaterMonster(MON_TYPE _eType, Vec2 _vPos);



};

