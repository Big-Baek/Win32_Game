#include "Global.h"
#include "CTexture.h"
#include "CCore.h"


CTexture::CTexture() :
    m_pImg(nullptr),
    m_dc(0),
    m_hbit(0)
{
}

CTexture::~CTexture()
{
    if (m_dc) DeleteDC(m_dc);
    if (m_hbit) DeleteObject(m_hbit);
    if (m_pImg)
    {
        delete m_pImg;
        m_pImg = nullptr;
    }
}

bool CTexture::CreateTexture(const wstring& _Name, const wstring& _strFilePath)
{
    m_pImg = new Image(_strFilePath.c_str());

    m_strKey = _Name;
    m_strRelativePath = _strFilePath;

    // 로드 상태 확인
    Status st = m_pImg->GetLastStatus();

    if (st == Gdiplus::Ok)
    {
        return true;
    }
    
    // 실패 시 메시지 출력
    wchar_t buf[256];
    swprintf_s(buf, L"GDI+ Load Failed (Status: %d)\nPath: %s", st, _strFilePath.c_str());
    MessageBox(nullptr, buf, L"PNG Load Error", MB_OK);

    delete m_pImg;
    m_pImg = nullptr;
    return false;
}

void CTexture::CreateBuffer(const wstring& _Name, UINT _iWidth, UINT _iHeight)
{
	m_strKey = _Name;
    HDC maindc = CCore::GetInst()->GetMainDC();

    m_dc = CreateCompatibleDC(maindc);
    m_hbit = CreateCompatibleBitmap(maindc, _iWidth, _iHeight);

    SelectObject(m_dc, m_hbit);
}

void CTexture::render(HDC hdc, int x, int y)
{
    if (m_pImg)
    {
        Gdiplus::Graphics g(hdc);
        g.DrawImage(m_pImg, x, y);
    }
}

