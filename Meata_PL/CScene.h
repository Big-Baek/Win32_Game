#pragma once
#include "CMonFactory.h"

class CObject;
class CActor;

class CScene
{
public:
	CScene();
	virtual ~CScene();

private:
	wstring	m_strName;

	UINT m_iTileX;
	UINT m_iTileY;

	CActor* m_pPlayer;

	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; //그룹갯수만큼 벡터선언



public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	CActor* GetPlayer() { return m_pPlayer; }

	virtual void BeginPlay();
	virtual void update();
	virtual void Physics_update();

	virtual void render(HDC _dc);
	void render_background(HDC _dc);
	void render_tile(HDC _dc);

	virtual void Enter() = 0;//해당 Scene 진입시 호출
	virtual void Exit() = 0;//탈출시 호출

public:

	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }
	void RegisterPlayer(CActor* _pPlayer) { m_pPlayer = _pPlayer; }
	

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	vector<CActor*> GetActorOfGroup(GROUP_TYPE _eType);

	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }
};