#include "CTile.h"
#include "CTexture.h"


CTile::CTile():
	m_pTileTex(nullptr),
	m_iImgIdx(0)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::update()
{

}

//void CTile::render(HDC _dc)
//{
//	if (m_pTileTex == nullptr || m_iImgIdx == -1) return;
//
//	UINT iWidth = m_pTileTex->Width(); //총 너비
//	UINT iHeight = m_pTileTex->Height(); //총 길이
//
//	UINT iMaxCol = iWidth / TILE_SIZE; //너비를 비트수로 나눈값 즉 타일의 가로갯수
//	UINT iMaxRow = iHeight / TILE_SIZE;// 타일의 세로갯수
//
//	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;
//	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;
//
//	if (iMaxRow <= iCurRow || iMaxCol <= iCurCol) assert(nullptr);
//
//
//	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
//	Vec2 vScale = GetScale();
//
//	BitBlt(
//		_dc,
//		int(vRenderPos.x),
//		int(vRenderPos.y),
//		int(vScale.x),
//		int(vScale.y),
//		m_pTileTex->GetDC(),
//		iCurCol * TILE_SIZE,
//		iCurRow * TILE_SIZE,
//		SRCCOPY
//	);
//}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}

