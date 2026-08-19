#include "Global.h"
#include "CTexture.h"
#include "CCore.h"


CTexture::CTexture() :
    m_pImg(nullptr),
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

void CTexture::PNG_Load(const std::wstring& _strFilePath)
{
    // GDI+ Image 생성
    m_pImg = new Gdiplus::Image(_strFilePath.c_str());

    // 로드 상태 확인
    Gdiplus::Status st = m_pImg->GetLastStatus();

    if (st == Gdiplus::Ok)
    {
        m_bUseGDIPlus = true;
        m_bitInfo.bmWidth = m_pImg->GetWidth();
        m_bitInfo.bmHeight = m_pImg->GetHeight();
        return;
    }

    // 실패 시 메시지 출력
    wchar_t buf[256];
    swprintf_s(buf, L"GDI+ Load Failed (Status: %d)\nPath: %s", st, _strFilePath.c_str());
    MessageBox(nullptr, buf, L"PNG Load Error", MB_OK);

    delete m_pImg;
    m_pImg = nullptr;
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

void CTexture::render(HDC hdc, int x, int y)
{
    if (m_pImg)
    {
        Gdiplus::Graphics g(hdc);
        g.DrawImage(m_pImg, x, y);
    }
}

