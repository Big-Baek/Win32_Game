#pragma once
#include "Global.h"

class CActor;

class CComponent
{
public:
	CComponent();
	~CComponent();

protected:
	CActor* m_pOwner;
	bool bEnable;
	COMPONENT_TYPE m_eType;

public:

	void Enable(bool _bEnable) { bEnable = _bEnable; }
	virtual void BeginPlay();
	virtual void update();
	virtual void render(HDC _dc) {};

	virtual CActor* GetOwner() {
		if (!m_pOwner) return nullptr;
		return m_pOwner;
	}

	void DebugRender(const wstring& _text);

	friend class CActor;
};