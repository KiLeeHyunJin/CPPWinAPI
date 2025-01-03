﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cassert>

// C++ 표준 라이브러리
#include <clocale>
#include <chrono>
#include <string>
#include <cmath>

//STL
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <unordered_map>


using namespace std;

//Util
#include "SingleTon.h"
#include "Struct.h"
#include "Logger.h"
#include <commdlg.h>


//D2D
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib,"D2D1.lib")
#pragma comment(lib,"Dwrite.lib")

using namespace D2D1;

#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "fmod_vc.lib")


