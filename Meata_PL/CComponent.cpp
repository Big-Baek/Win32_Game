#include "CComponent.h"

CComponent::CComponent():
	bEnable(true),
	m_pOwner(nullptr)
{}

CComponent::~CComponent()
{}

void CComponent::BeginPlay()
{}

void CComponent::update()
{
	if (!bEnable) return;
}

void CComponent::DebugRender(const wstring& _text)
{
	MessageBox(NULL, _text.c_str(), L"DebugRender in Component", MB_OK | MB_ICONWARNING);
}
