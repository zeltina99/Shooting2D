﻿// Shooting2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Shooting2D.h"
#include "Player.h"

//#include <crtdbg.h>
//#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__,__LINE__)

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

Player PlayerAirplane;

Gdiplus::Point g_AppPosition(100, 100);
Gdiplus::Point g_ScreenSize(800, 600);

Gdiplus::Point g_HousePosition(100, 100);
constexpr int g_HouseVerticesCount = 7;
const Gdiplus::Point g_HouseVertices[g_HouseVerticesCount] =
{
    {0,-100},{50,-50},{30,-50},{30,0},{-30,0},{-30,-50},{-50,-50}
};
//bool g_bKeyWasPressed
std::unordered_map<InputDirection, bool> g_KeyWasPressedMap;

Gdiplus::Bitmap* g_BackBuffer = nullptr;    // 백버퍼용 종이
Gdiplus::Graphics* g_BackBufferGraphics = nullptr;  // 백버퍼용 종이에 그리기 위한 도구

//Gdiplus::Bitmap* g_PlayerImage = nullptr;   // 플레이어가 그려질 종이
constexpr int PlayerImageSize = 64;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);  // 사용 안하는 파라메터 명시적으로 표시
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // GDI+ 초기화
    ULONG_PTR Token;
    Gdiplus::GdiplusStartupInput StartupInput;
    Gdiplus::GdiplusStartup(&Token, &StartupInput, nullptr);
    g_KeyWasPressedMap[InputDirection::Up] = false;
    g_KeyWasPressedMap[InputDirection::Down] = false;
    g_KeyWasPressedMap[InputDirection::Left] = false;
    g_KeyWasPressedMap[InputDirection::Right] = false;

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SHOOTING2D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);                 // 1. 윈도우 클래스 등록

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))    // 2. 윈도우 실제 생성 및 초기화
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SHOOTING2D));

    MSG msg;

    // 3. 메시지 루프
    // 기본 메시지 루프입니다:(메세지 큐에 들어온 메세지들을 하나씩 처리하는 부분)
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 단축키 처리
        {
            TranslateMessage(&msg); // 메시지를 메시지 프로시저로 보내 메시지를 처리한다.
            DispatchMessage(&msg);
        }
    }

    // GDI+ 정리하기
    Gdiplus::GdiplusShutdown(Token);
    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // 윈도우의 모양과 기본동작 등을 결정
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;  // 윈도우 프로시저 함수 등록
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHOOTING2D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;// 메뉴 제거
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    // 클라이언트 영역의 크기를 원하는 크기로 조절하기
    RECT rc = { 0,0, g_ScreenSize.X, g_ScreenSize.Y };

    AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, FALSE, 0);

    // 실제 윈도우 생성
    HWND hWnd = CreateWindowW(szWindowClass,
        L"2D Shooting for GDI+",
        // WS_OVERLAPPEDWINDOW에서 
        // WS_MAXIMIZEBOX(최대화 버튼 비활성화)와 WS_THICKFRAME(테두리잡고 크기 변경 금지)만 제외
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        g_AppPosition.X, g_AppPosition.Y,   // 시작 좌표(스크린 좌표계)
        rc.right - rc.left, rc.bottom - rc.top,    // 크기(윈도우 스타일에 맞춰 재조정된 크기)
        nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);  // 윈도우 보여주기
    UpdateWindow(hWnd);          // 윈도우 업데이트하기(윈도우 화면 갱신)

    return TRUE;
}
//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // 윈도우가 생성되었을때 날아오는 메시지
        g_BackBuffer = new Gdiplus::Bitmap(g_ScreenSize.X, g_ScreenSize.Y, PixelFormat32bppARGB);
        g_BackBufferGraphics = Gdiplus::Graphics::FromImage(g_BackBuffer);
        if (!g_BackBufferGraphics)
        {
            // 혹시 안만들어졌을 때를 대비한 에러 출력
            MessageBox(hWnd, L"백 버퍼 그래픽스 생성 실패", L"오류", MB_OK | MB_ICONERROR);
        }
        PlayerAirplane.LoadImageW(hWnd);
        break;
    case WM_DESTROY:
        // 윈도우가 삭제되었을 때 날아오는 메세지
        PlayerAirplane.ReleaseImage();
        delete g_BackBufferGraphics;
        g_BackBufferGraphics = nullptr;
        delete g_BackBuffer;
        g_BackBuffer = nullptr;
        PostQuitMessage(0);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        if (g_BackBufferGraphics)   // g_BackBufferGraphics 필수
        {
            g_BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));
            Gdiplus::SolidBrush GreenBrush(Gdiplus::Color(255, 0, 255, 0));
            Gdiplus::SolidBrush BlueBrush(Gdiplus::Color(255, 0, 0, 255));
            Gdiplus::SolidBrush YelloBrush(Gdiplus::Color(255, 255, 255, 0));


            for (int y = 0; y < 2; y++)
            {
                for (int x = 0; x < 10; x++)
                {
                    g_BackBufferGraphics->FillRectangle(&YelloBrush, 30 + 70 * x, 50 + 70 * y, 60, 60);
                }
            }

            Gdiplus::Pen GreenPen(Gdiplus::Color(255, 0, 255, 0), 2.0f);
            Gdiplus::Point Positions[g_HouseVerticesCount];
            for (int i = 0; i < g_HouseVerticesCount; i++)
            {
                Positions[i] = g_HousePosition + g_HouseVertices[i];
            }
            g_BackBufferGraphics->DrawPolygon(&GreenPen, Positions, g_HouseVerticesCount);
            //g_BackBufferGraphics->FillPolygon(&GreenBrush, Positions, g_HouseVerticesCount);

            //if(g_PlayerImage)
            //{
            //    
            //}
            //else
            //{
            //    // 플레이어 이미지가 없으면 원을 대신 그림
            //    Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
            //    g_BackBufferGraphics->FillEllipse(
            //        &RedBrush,
            //        100, 100,
            //        PlayerImageSize, PlayerImageSize);
            //}

            PlayerAirplane.Draw(g_BackBufferGraphics);
            Gdiplus::Graphics GraphicsInstance(hdc);    // Graphics객체 만들기
            GraphicsInstance.DrawImage(g_BackBuffer, 0, 0);
           
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_ERASEBKGND:
        // 화면을 지워야 할 때 날라온 메시지
        return 1;   // 배경지우기 방지(백버퍼 사용하고 있기 때문에)
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            //if (!g_KeyWasPressedMap[static_cast<InputDirection>(wParam)])
        {
            g_KeyWasPressedMap[static_cast<InputDirection>(wParam)] = true;
            OutputDebugStringW(L"왼쪽키를 눌렀다.\n");
            PlayerAirplane.Move(-10, 0);
            InvalidateRect(hWnd, nullptr, FALSE);    // 창을 다시 그리도록 요청(WM_PAINT 메시지가 들어간다)
        }
        break;
        case VK_RIGHT:
            //if (!g_KeyWasPressedMap[static_cast<InputDirection>(wParam)])
        {
            g_KeyWasPressedMap[static_cast<InputDirection>(wParam)] = true;
            OutputDebugStringW(L"오른쪽키를 눌렀다.\n");
            PlayerAirplane.Move(+10, 0);
            InvalidateRect(hWnd, nullptr, FALSE);   // 3번째 FALSE로 WM_ERASEBKGND 발동 안되게 하기
        }
        break;
        case VK_UP:
            //if (!g_KeyWasPressedMap[static_cast<InputDirection>(wParam)])
        {
            g_KeyWasPressedMap[static_cast<InputDirection>(wParam)] = true;
            OutputDebugStringW(L"위쪽키를 눌렀다.\n");
            //g_HousePosition.Y -= 10;
            InvalidateRect(hWnd, nullptr, FALSE);
        }
        break;
        case VK_DOWN:
            //if (!g_KeyWasPressedMap[static_cast<InputDirection>(wParam)])
        {
            g_KeyWasPressedMap[static_cast<InputDirection>(wParam)] = true;
            OutputDebugStringW(L"아래쪽키를 눌렀다.\n");
            //g_HousePosition.Y += 10;
            InvalidateRect(hWnd, nullptr, FALSE);
        }
        break;
        case VK_ESCAPE:
            DestroyWindow(hWnd);    // hWnd 창을 닫아라 -> 프로그램을 꺼라(WM_DESTROY메시지가 들어간다.)
        }
        break;
    case WM_KEYUP:
        g_KeyWasPressedMap[static_cast<InputDirection>(wParam)] = false;    // 키가 떨어졌다고 표시
        switch (wParam)
        {
        case VK_LEFT:
            OutputDebugStringW(L"왼쪽키를 땠다.\n");
            break;
        case VK_RIGHT:
            OutputDebugStringW(L"오른쪽키를 땠다.\n");
            break;
        case VK_UP:
            OutputDebugStringW(L"위쪽키를 땠다.\n");
            break;
        case VK_DOWN:
            OutputDebugStringW(L"아래쪽키를 땠다.\n");
            break;
        }
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
