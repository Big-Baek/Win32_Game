#include "Global.h"
#include "CTexture.h"
#include "CCore.h"


CTexture::CTexture() :
	m_dc(0),
	m_hbit(0),
	m_bitInfo()
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hbit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	m_hbit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	//assert(m_hbit);
	SetWindowText(CCore::GetInst()->GetMainHwnd(), _strFilePath.c_str());

	//비트맵과 연결할 dc
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hbit);
	DeleteObject(hPrevBit);

	//가로세로길이 필요
	GetObject(m_hbit, sizeof(BITMAP), &m_bitInfo);
}

void CTexture::PNG_Load(const wstring& _strFilePath)
{
    // 1) 먼저 GDI+로 시도
    m_pImg = new Gdiplus::Image(_strFilePath.c_str());
    if (m_pImg && m_pImg->GetLastStatus() == Gdiplus::Ok)
    {
        m_bUseGDIPlus = true;
        m_bitInfo.bmWidth = m_pImg->GetWidth();
        m_bitInfo.bmHeight = m_pImg->GetHeight();
        return;
    }
    delete m_pImg;
    m_pImg = nullptr;

    // 2) 실패하면 BMP로 시도
    m_hbit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP,
        0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

    if (m_hbit)
    {
        m_bUseGDIPlus = false;
        m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());
        HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hbit);
        DeleteObject(hPrevBit);

        //비트맵 정보
        GetObject(m_hbit, sizeof(BITMAP), &m_bitInfo);
    }
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
    HDC maindc = CCore::GetInst()->GetMainDC();

    m_hbit = CreateCompatibleBitmap(maindc, _iWidth, _iHeight);
    m_dc = CreateCompatibleDC(maindc);

    HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hbit);
    DeleteObject(hOldBit);

    GetObject(m_hbit, sizeof(BITMAP), &m_bitInfo);

}

