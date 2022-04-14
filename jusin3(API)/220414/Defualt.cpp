#include "framework.h"
#include "Defualt.h"
#include <vector>

using namespace std;

#define MAX_LOADSTRING 100


#pragma region 숙제 함수

void DrowMe(HDC _hdc, RECT _rec)
{
    // left, top, right, bottom

    // 머리
    Ellipse(_hdc, 0 + _rec.left, 0 + _rec.top, 100 +_rec.right, 100 + _rec.bottom);
    // 눈
    Ellipse(_hdc, 20 + _rec.left, 20 + _rec.top, 40 + _rec.right, 40 + _rec.bottom);
    Ellipse(_hdc, 20 + 40 + _rec.left, 20 + _rec.top, 40 + 40 + _rec.right, 40 + _rec.bottom);
    // 입
    MoveToEx(_hdc, 40 + _rec.left, 50 + _rec.top, nullptr);
    LineTo(_hdc, 70 + _rec.left, 50 + _rec.top);

    // 몸통
    MoveToEx(_hdc, 50 + _rec.left, 100 + _rec.top, nullptr);
    LineTo(_hdc, 50 + _rec.left, 150 + _rec.top);

    // 발
    LineTo(_hdc, 0 + _rec.left, 200 + _rec.top);
    MoveToEx(_hdc, 50 + _rec.left, 150 + _rec.top, nullptr);
    LineTo(_hdc, 100 + _rec.left, 200 + _rec.top);

    // 손
    MoveToEx(_hdc, 50 + _rec.left, 110 + _rec.top, nullptr);
    LineTo(_hdc, 10 + _rec.left, 160 + _rec.top);
    MoveToEx(_hdc, 50 + _rec.left, 110 + _rec.top, nullptr);
    LineTo(_hdc, 120 + _rec.left, 100 + _rec.top);

    // 망치
    MoveToEx(_hdc, 110 + _rec.left, 110 + _rec.top, nullptr);
    LineTo(_hdc, 140 + _rec.left, 50 + _rec.top);
    Rectangle(_hdc, 140 - 50 + _rec.left, 50 - 25 + 25 + _rec.top, 140 + 50 + _rec.right, 50 - 25 - 25 + _rec.bottom);


}

#pragma endregion



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

    // TODO: 여기에 코드를 입력합니다.

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

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))     // 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
        {
            TranslateMessage(&msg);     // 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 번역하는 함수
            DispatchMessage(&msg);      // 시스템 메세지 큐에서 꺼낸 메세지를 프로그램에서 처리(WndProc 호출) 하도록 전달
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
#pragma region Handle(키 값)이 필요한 이유

// 윈도우는 멀티 프로세스가 가능하다
// 그 이유는 코어가 계속 여러 프로세스를 왓다갓다해서 (컨텍스트 스위칭!!)
// 프로세스마다 고유의 키 값을 줘서 구분한다.
//      ㄴ지금은 너, 다음은 너
//      ㄴ많은 프로세스 메세지들을 전부 큐에 담는데, 어느 프로세스의 메시지인지 구분하기 위해서도 키 값 필요!!

#pragma endregion

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   RECT rc{ 0, 0, 800, 600 };


   // 윈도우 화면을 만든다!!! 중요!!
   //   ㄴ내가 만든 윈도우 화면의 ID값을 반환한다 (핸들 값)
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      100, 100,             // 출력하고자 하는 창의 left와 top 좌표
      rc.right - rc.left,   // 생성하고자 하는 창의 가로, 세로 사이즈
      rc.bottom - rc.top, 
      nullptr, nullptr, hInstance, nullptr);



   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}




enum DIR { UP, DOWN, LEFT, RIGHT };
struct ProjectileInfo
{
    RECT m_rec{ 0, 0, 0, 0 };
    DIR m_dir = DIR::UP;
};
RECT rec{ 0, 0, 0, 0 };
vector<ProjectileInfo> vecRect;


//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//  용도: 주 창의 메시지를 처리합니다.
//      ㄴWM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//      ㄴWM_PAINT    - 주 창을 그립니다.
//      ㄴWM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:

        SetTimer(hWnd, 0, 0, 0);
        
        break;
    case WM_TIMER:
        
        // 화면 지우기
        InvalidateRect(hWnd, 0, true);

        break;




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




    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);    // 그리기 시작할게!
            
            // 그리기 함수
            // MoveToEx(hdc, 100, 100, nullptr);     // 선 그리기 시작점
            // LineTo(hdc, 200, 100);


            // 사각형 그리기 함수
            //      ㄴRectangle(hdc, 100, 100, 200, 200);

            // 원 그리기 함수
            //      ㄴEllipse(hdc, 300, 300, 400, 400);

            
            DrowMe(hdc, rec);


            for (int i = 0; i < vecRect.size(); ++i)
            {
                Ellipse(hdc, 10 + 120 + vecRect[i].m_rec.left, 10 + vecRect[i].m_rec.top, 30 + 120 + vecRect[i].m_rec.right, 30 + vecRect[i].m_rec.bottom);
                
                switch (vecRect[i].m_dir)
                {
                case UP:
                    vecRect[i].m_rec.bottom -= 10;
                    vecRect[i].m_rec.top -= 10;
                    break;
                case DOWN:
                    vecRect[i].m_rec.bottom += 10;
                    vecRect[i].m_rec.top += 10;
                    break;
                case LEFT:
                    vecRect[i].m_rec.left -= 10;
                    vecRect[i].m_rec.right -= 10;
                    break;
                case RIGHT:
                    vecRect[i].m_rec.left += 10;
                    vecRect[i].m_rec.right += 10;
                    break;
                }
            }


            EndPaint(hWnd, &ps);            // 그리기 끝낼게...
        }
        break;




    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_RIGHT:

            rec.left += 10;
            rec.right += 10;

            break;
        case VK_LEFT:

            rec.left -= 10;
            rec.right -= 10;

            break;
        case VK_UP:

            rec.top -= 10;
            rec.bottom -= 10;

            break;
        case VK_DOWN:

            rec.top += 10;
            rec.bottom += 10;

            break;

        case 'W':
            vecRect.push_back(ProjectileInfo() = { RECT{ rec.left, rec.top, rec.right, rec.bottom }, DIR::UP });
            break;
        case 'S':
            vecRect.push_back(ProjectileInfo() = { RECT{ rec.left, rec.top, rec.right, rec.bottom }, DIR::DOWN });
            break;
        case 'A':
            vecRect.push_back(ProjectileInfo() = { RECT{ rec.left, rec.top, rec.right, rec.bottom }, DIR::LEFT });
            break;
        case 'D':
            vecRect.push_back(ProjectileInfo() = { RECT{ rec.left, rec.top, rec.right, rec.bottom }, DIR::RIGHT });
            break;

        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;
    }



    case WM_DESTROY:
        KillTimer(hWnd, 0);
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



#pragma region 숙제

// 숙제 : 
// 1.함수 호출 규약에 대해 공부하기
//     ㄴc놀로지 뇌자극 시스템 프로래밍   >>  파트가 있음 p.343 ~ 347
//          ㄴ함수 호출 규약은 면접에서 나올 수도 있다.
//                 ㄴ콜백함수에 대해서 설명해 봐라
// 2.Draw any Paint by using LintoFunc
//     ㄴ사각형 그리기 함수, 원 그리기 함수도 사용해서
// 3.wasd 키를 누르면 총알 쏘기

#pragma endregion

