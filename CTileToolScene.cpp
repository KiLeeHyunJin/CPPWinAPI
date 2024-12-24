#include "framework.h"
#include "CTileToolScene.h"
#include "CTile.h"

#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"

LRESULT CALLBACK   WinTileToolProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


CTileToolScene::CTileToolScene():
	m_iTileSizeX(0), m_iTileSizeY(0), m_fScrollSpeed(0)
{
	m_hWndTileTool = 0;
}

CTileToolScene::~CTileToolScene()
{
}

void CTileToolScene::ClickTileButton(UINT tileIndex)
{

}

void CTileToolScene::Init()
{
}

void CTileToolScene::Release()
{
}

void CTileToolScene::Render()
{
}

void CTileToolScene::Update()
{
	if (BUTTONDOWN(VK_F1))
	{
		CHANGESCENE(GroupScene::Title);
	}
	if (BUTTONDOWN(VK_SPACE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);
	}
	if (LMOUSEDOWN(true))
	{
		SetTileIndex(1);
	}
	CameraMove();
}

void CTileToolScene::Enter()
{
	m_hWndTileTool = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TOOLSCENE), hWnd, WinTileToolProc);
	ShowWindow(m_hWndTileTool, SW_SHOW);

	RECT rect;
	GetWindowRect(m_hWndTileTool, &rect);
	MoveWindow(m_hWndTileTool, WINSIZEX + STARTPOSX, WINSIZEY + STARTPOSY, rect.right - rect.left, rect.bottom - rect.top, true);

	CreateTiles(10, 10);

	CAMERA->FadeIn(0.25f);
}

void CTileToolScene::Exit()
{
	EndDialog(m_hWndTileTool, IDOK);
	DeleteAll();
}

void CTileToolScene::SetTileIndex(UINT index)
{
	Vector vecMousePos = MOUSEWORLDPOSITION;
	float tilePosX = vecMousePos.x / CTile::TILESIZE;
	float tilePosY = vecMousePos.y / CTile::TILESIZE;

	if (tilePosX < 0.0f || (int)m_iTileSizeX <= tilePosX ||
		tilePosY < 0.0f || (int)m_iTileSizeY <= tilePosY)
	{
		return;
	}

	const list<CGameObject*>& listTile = GetLayerObject(Layer::Tile);
	for (CGameObject* pObj : listTile)
	{
		CTile* pTile = dynamic_cast<CTile*>(pObj);
		if (pTile->GetTilePosX() != (int)tilePosX ||
			pTile->GetTilePosY() != (int)tilePosY)
		{
			continue;
		}

		pTile->SetTileIndex(pTile->GetTileIndex() + index);
		return;
	}
}

void CTileToolScene::CameraMove()
{
	Vector dir;
	if (BUTTONSTAY('A'))
	{
		dir.x = -1;
	}
	else if (BUTTONSTAY('W'))
	{
		dir.y = -1;
	}
	else if (BUTTONSTAY('D'))
	{
		dir.x = 1;
	}
	else if (BUTTONSTAY('S'))
	{
		dir.y = 1;
	}
	CAMERA->Scroll(dir, m_fScrollSpeed);
}

void CTileToolScene::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	wchar_t szName[256] = {};

	ofn.lpstrTitle = szName;
	ofn.nMaxFile = sizeof(szName);

	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;

	ofn.nMaxFileTitle = 0;
	wstring strTileFolder = GETPATH;
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetSaveFileName(&ofn))
	{
		LoadTile(szName);
	}
}

void CTileToolScene::SaveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	wchar_t szName[256] = {};

	ofn.lpstrTitle = szName;
	ofn.nMaxFile = sizeof(szName);

	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;

	ofn.nMaxFileTitle = 0;
	wstring strTileFolder = GETPATH;
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CTileToolScene::SaveTile(const wstring& strPath )
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strPath.c_str(), L"wb");
	assert(pFile);
	UINT xCount = m_iTileSizeX;
	UINT yCount = m_iTileSizeY;
	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	for (CGameObject* pObj : m_listObj[(int)Layer::Tile])
	{
		CTile* pTile = dynamic_cast<CTile*>(pObj);
		if (pTile != nullptr)
		{
			pTile->Save(pFile);
		}
	}
	fclose(pFile);
}


LRESULT CALLBACK		WinTileToolProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_TILEBUTTON)
		{
			int x = GetDlgItemInt(hDlg, IDC_EDITTILEXSIZE, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDITTILEYSIZE, nullptr, false);

			//CScene* pCurScene = SCENE->GetCurScene();
			//pCurScene->CreateTiles(x, y);
		}
		break;

	default:
		break;
	}
	return (INT_PTR)false;
}
