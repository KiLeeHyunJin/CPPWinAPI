#include "framework.h"
#include "CTilePanel.h"
#include "CImage.h"
#include "CTile.h"
#include "CTileButton.h"
#include "CTileToolScene.h"
#include "CResourceManager.h"
#include "CSceneManager.h"

CTilePanel::CTilePanel():
	m_pImage(nullptr), m_uiPaletteX(0), m_uiPaletteY(0),
	m_uiTileCountX(0), m_uiTileCountY(0), m_uiTilePage(0)
{
	m_uiMenuHeight = 200;
}

CTilePanel::~CTilePanel()
{
}

void CTilePanel::Init()
{
	CreateTilePalette();
	CreatepageButton();
	SetPage(0);
}

void CTilePanel::Release()
{
}

void CTilePanel::Render()
{
}

void CTilePanel::Update()
{
}

void CTilePanel::CreateTilePalette()
{
	m_pImage = RESOURCE->LoadImg(L"Tile", L"Image\\Tile.png");
	m_uiTileCountX = m_pImage->GetBmpWidth() / CTile::TILESIZE;
	m_uiTileCountY = m_pImage->GetBmpHeight() / CTile::TILESIZE;

	m_uiPaletteX = (int)(m_vecScale.x / CTile::TILESIZE);
	m_uiPaletteY = (int)((m_vecScale.y - m_uiMenuHeight) / CTile::TILESIZE);

	int marginX = ((int)m_vecScale.x % CTile::TILESIZE) * 0.5f;
	int marginY = ((int)m_vecScale.y % CTile::TILESIZE) * 0.5f;
	for (UINT y = 0; y < m_uiPaletteY; y++)
	{
		for (UINT x = 0; x < m_uiPaletteX; x++)
		{
			CTileButton* pTileButton = new CTileButton();
			pTileButton->SetImage(m_pImage);
			pTileButton->SetPosition(Vector((float)x * CTile::TILESIZE, (float)y * CTile::TILESIZE));
			pTileButton->SetPosition(pTileButton->GetPosition() + Vector((float)marginX, (float)marginY));
			AddChildUI(pTileButton);
			m_vecTileButton.push_back(pTileButton);
		}
	}
}

void CTilePanel::CreatepageButton()
{
	auto prevClick = [](DWORD_PTR tilePanel, DWORD_PTR)
		{
			CTilePanel* pTilePanel = (CTilePanel*)tilePanel;
			pTilePanel->SetPrevPage();
		};
	CButton* pPrevButton = new CButton();
	pPrevButton->SetScale(50, 30);
	pPrevButton->SetPosition(Vector((float)10, (float)(m_vecScale.y - m_uiMenuHeight)));
	pPrevButton->SetClickedCallBack(prevClick, (DWORD_PTR)this, (DWORD_PTR)0);

	auto nextClick = [](DWORD_PTR tilePanel, DWORD_PTR)
		{
			CTilePanel* pTilePanel = (CTilePanel*)tilePanel;
			pTilePanel->SetNextPage();
		};
	CButton* pNextClick = new CButton();
	pNextClick->SetScale(50, 30);
	pNextClick->SetPosition(Vector((float)60, (float)(m_vecScale.y - m_uiMenuHeight)));
	pNextClick->SetClickedCallBack(prevClick, (DWORD_PTR)this, (DWORD_PTR)0);
}

void CTilePanel::SetPage(UINT page)
{
	for (UINT x = 0; x < m_vecTileButton.size(); x++)
	{
		auto clicked = [](DWORD_PTR tilePanel, DWORD_PTR index) 
			{
				CScene* pScene = SCENE->GetCurScene();
				CTileToolScene* pToolScene = dynamic_cast<CTileToolScene*>(pScene);
				if (pToolScene != nullptr)
				{
					UINT tileIndex = (UINT)index;
					pToolScene->ClickTileButton(tileIndex);
				}
			};
		UINT tileIndex = x + m_uiTilePage * (UINT)m_vecTileButton.size();
		m_vecTileButton[x]->SetTileIndex(tileIndex);
		m_vecTileButton[x]->SetClickedCallBack(clicked, (DWORD_PTR)this, (DWORD_PTR)tileIndex);
	}
}

void CTilePanel::SetPrevPage()
{
	if (m_uiTilePage <= 0)
	{
		return;
	}
	SetPage(--m_uiTilePage);
}

void CTilePanel::SetNextPage()
{
	UINT tileCount = m_uiTileCountX * m_uiTileCountY;
	if(m_uiTilePage >= tileCount / m_vecTileButton.size())
	if (m_uiTilePage <= 0)
	{
		return;
	}
	SetPage(++m_uiTilePage);
}
