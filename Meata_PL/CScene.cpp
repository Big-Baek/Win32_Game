#include "Global.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CCore.h"


CScene::CScene() :
	m_iTileX(0),
	m_iTileY(0),
	m_pPlayer(nullptr)
{}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			delete m_arrObj[i][j];
		}
	}
}

void CScene::Start()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->Start();
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}
//충돌체는 플레이어 따라감
void CScene::Physics_update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->Physics_update();
		}
	}
}


//타일을 런타임도중에 없애야한다면 별도의 작업 추가
void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		if (i == (UINT)GROUP_TYPE::TILE)
		{
			render_tile(_dc);
			continue;
		}
		vector<CObject*>::iterator iter = m_arrObj[i].begin();
		for (; iter != m_arrObj[i].end();)
		{

			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::render_background(HDC _dc)
{



}

void CScene::render_tile(HDC _dc)
{
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	Vec2 vCamLook = CCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	Vec2 vLeftTop = vCamLook - vResolution / 2.f;

	int iTileSize = TILE_SIZE;

	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;

	int iClientWidt = (int)vResolution.x / iTileSize;
	int iClientHeight = (int)vResolution.y / iTileSize;

	for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight) + 1; iCurRow++)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidt) + 1; iCurCol++)
		{
			if (iCurCol < 0 || m_iTileX <= iCurCol
				|| iCurRow < 0 || m_iTileY <= iCurRow)
			{
				continue;
			}


			int iIdx = (m_iTileX * iCurRow) + iCurCol;

			vecTile[iIdx]->render(_dc);
		}

	}
}



void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	//Safe_Delete_Vec(m_arrObj[(UINT)_eTarget]); //간단한 버전
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]); //템플릿 정석사용법
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}

}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\bTile.bmp");

	for (UINT i = 0; i < _iYCount; i++)
	{
		for (UINT j = 0; j < _iXCount; j++)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)j * TILE_SIZE, (float)i * TILE_SIZE));
			pTile->SetTexture(pTileTex);
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}

}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	//파일은 커널오브젝트
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;


	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	//타일 가로세로 갯수 불러오기
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	//불러온 개수에 맞게 EmptyTile 만들기
	CreateTile(xCount, yCount);

	//만들어진 타일 개별로 정보 불러오기
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}


	fclose(pFile);
}
