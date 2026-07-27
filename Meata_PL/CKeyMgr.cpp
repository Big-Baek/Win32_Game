#include "Global.h"
#include "CKeyMgr.h"
#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_RSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
	
	VK_LBUTTON,
	VK_RBUTTON,
};


CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{

	m_vecKey = vector<tKeyinfo>((int)KEY::LAST, tKeyinfo{ KEY_STATE::NONE, false });


}

void CKeyMgr::update()
{
	HWND hMainWnd = CCore::GetInst()->GetMainHwnd();

	HWND hWnd = GetFocus();//현재 포커싱 윈도우 확인

	if (hWnd != nullptr)//포커싱되고있다면
	{
		for (int i = 0; i < (int)KEY::LAST; i++)//계속해서 현재 키상태를 변경
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrev)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrev = true;
			}
			else
			{
				if (m_vecKey[i].bPrev)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrev = false;
			}
		}

		//Mouse 위치 계산
		POINT ptPos = {};
		GetCursorPos(&ptPos); //마우스 좌표계산 함수 = 윈도우 전체 기준 좌표라 추가 보정 필요

		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);

	}
	else//포커싱이 안되고 있다면
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrev = false;
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if(KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}

KEY_STATE CKeyMgr::GetKeyState(KEY e_KEY)
{
	return m_vecKey[(int)e_KEY].eState;
}
