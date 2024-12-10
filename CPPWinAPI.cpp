// CPPWinAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "CPPWinAPI.h"
#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

bool processState;  // 게임 진행 중이면 true 종료면 false

// 윈도우 메인함수
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //메모리 누수 체크


#pragma region Init

    setlocale(LC_ALL, "Korean");    //지역 설정

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CPPWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    processState = true;

    // 단축키 정보를 가져옵니다.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CPPWINAPI));

#pragma endregion

    // 다음 틱 카운트 입니다.
    ULONGLONG nextTickCount = 0;
    ULONGLONG tickCount;
    CORE->Init();

    // 기본 메시지 루프입니다:
    MSG msg;
    while (processState)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))// 단축키 처리 하지만, 단축키가 아닐 경우
            {
                TranslateMessage(&msg); // 입력 메시지 번역
                DispatchMessage(&msg); // 입력 메시지 처리, WinProc에서 전달된 메시지 처리
            }
        }
        else
        {
            tickCount = GetTickCount64();
            if (nextTickCount <= tickCount)
            {
                nextTickCount = tickCount + 10;

                CORE->Update();
                CORE->Render();
            }
        }
    }

    CORE->Release();

    return (int) msg.wParam;
}

/// <summary>
///  창 클래스를 등록합니다.
/// </summary>
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc; // 메시지 처리 함수 등록 //DispatchMessage를 통해 처리
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;

    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CPPWINAPI));
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // Small Icon

    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);

    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);

    wcex.lpszMenuName   = nullptr; //MAKEINTRESOURCEW(IDC_CPPWINAPI);
    wcex.lpszClassName  = szWindowClass;

    return RegisterClassExW(&wcex);
}


/// 인스턴스 핸들을 저장하고 주 창을 만듭니다.(HINSTANCE, int)
/// 이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
/// 주 프로그램 창을 만든 다음 표시합니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   DWORD myStyle =    WS_OVERLAPPED 
                    | WS_CAPTION 
                    | WS_SYSMENU 
                    | WS_THICKFRAME 
                    | WS_MINIMIZEBOX 
                    //|WS_MAXIMIZEBOX
                    ;

   hWnd = CreateWindowW(
       szWindowClass, 
       szTitle,
       myStyle,

       STARTPOSX, //Start Pos X //CW_DEFAULT
       STARTPOSY,  //Start Pos Y //CW_DEFAULT

       WINSIZEX,  //Size X
       WINSIZEY,  //Size Y

       nullptr,
       nullptr, 
       hInstance, 
       nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

/// 주 창의 메시지를 처리합니다.(HWND, UINT, WPARAM, LPARAM)
/// WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
/// WM_PAINT    - 주 창을 그립니다.
/// WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND: //단축키
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                processState = false;
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_LBUTTONDOWN: // 마우스 왼쪽 클릭
        {
            /*point.x = LOWORD(lParam);
            point.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, false);*/
        }
        break;

        // 무효화 영역이 발생했을때 실행
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;

#pragma region WM_KEYDOWN
        /*
    case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_LEFT :
                case 'A':
                    point.x -= 10;
                    break;

                case VK_RIGHT:
                case 'D':
                    point.x += 10;
                    break;

                case VK_DOWN:
                case 'S':
                    point.y += 10;
                    break;

                case VK_UP:
                case 'W':
                    point.y -= 10;
                    break;
            default:
                break;
            }
            InvalidateRect(hWnd, NULL, false);
            
        }
        break;
        */
#pragma endregion

        // 윈도우 종료될때
    case WM_DESTROY:
        PostQuitMessage(0); // 종료 메시지 전달
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

/// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
