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
	Title, Stage01, Size
};

enum class Layer
{
	Default,
	Monster,
	Character,

	Ui,
	Size
};

