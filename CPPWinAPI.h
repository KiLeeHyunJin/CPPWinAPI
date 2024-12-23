#pragma once
#include "resource.h"

extern HINSTANCE hInst;
extern HWND hWnd;

#define STARTPOSX 400
#define STARTPOSY 250

#define WINSIZEX 800
#define WINSIZEY 600

enum class GroupScene
{
	Title, Stage01, EditScene,Size
};

enum class Layer
{
	Default,
	Monster,
	Character,
	Tile,

	Ui,
	Size
};

enum class TileType 
{
	None,
	Ground,
	Platform,
	Wall,

	Size
};
