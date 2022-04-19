#include "pch.h"
// #include "framework.h"
#include "Defualt.h"
#include "CMainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HWND    g_hWnd;

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름

// 전역 함수 모음 (전방 선언)
ATOM                MyRegisterClass(HINSTANCE hInstance);           // 창 생성과 관련된 디자인 요소를 제어
BOOL                InitInstance(HINSTANCE, int);                   // 실제적으로 창을 생성하고 그 창의 핸들을 만드는 기능
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);







// ============== main ====================================

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFUALT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFUALT));

    MSG msg;
    msg.message = WM_NULL;  // 앞으로 메시지를 안 받겠다.

    // MainGame 생성
    CMainGame::GetInst()->Initialize();

    // 운영체제(os)가 구동된 시점으로 부터 특정 정수 값을 반환
    // 상승하던 값이 대략 1000정도가 됐을 때를 1초로 판단하는 개념
    // GetTickCount 반환값을 대략 1 / 1000초로 판단
    DWORD	dwOldTime = GetTickCount();



    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))     // 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
            {
                TranslateMessage(&msg);     // 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 번역하는 함수
                DispatchMessage(&msg);      // 시스템 메세지 큐에서 꺼낸 메세지를 프로그램에서 처리(WndProc 호출) 하도록 전달
            }
        }           
        else
        {
            // 대략 60 fram
            if (dwOldTime + 10 < GetTickCount())
            {
                CMainGame::GetInst()->Update();
                CMainGame::GetInst()->Render();

                dwOldTime = GetTickCount();
            }
        }
    }


    return (int) msg.wParam;
}











// ============== 전역함수 정의 ==========================

//  용도: 창 클래스를 등록합니다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFUALT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}



//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   RECT rc{ 0, 0, WINCX, WINCY };


   // rc = rc + 기본 윈도우 창스타일 + 메뉴바 크기
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);


   // 윈도우 화면을 만든다!!! 중요!!
   //   ㄴ내가 만든 윈도우 화면의 ID값을 반환한다 (핸들 값)
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0,             // 출력하고자 하는 창의 left와 top 좌표
      rc.right - rc.left,   // 생성하고자 하는 창의 가로, 세로 사이즈
      rc.bottom - rc.top, 
      nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}




//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//  용도: 주 창의 메시지를 처리합니다.
//      ㄴWM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//      ㄴWM_PAINT    - 주 창을 그립니다.
//      ㄴWM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
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
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    //case WM_PAINT:
    //{
    //    PAINTSTRUCT ps;


    //}
    //    break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            DestroyWindow(hWnd);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }


    return 0;
}


// 정보 대화 상자의 메시지 처리기입니다.
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

