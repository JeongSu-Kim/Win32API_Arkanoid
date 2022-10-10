// Win32Project2.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Win32Project4.h"

#include <crtdbg.h>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING] = _T("TITLE");                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING] = _T("WINCLASS");            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//GameScene myGame;
HWND hWnd;
FPScount fps;

TCHAR titleFPSbuffer[100] = { 0, };

COLORREF rainbow();
COLORREF dark(COLORREF color);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	//LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadStringW(hInstance, IDC_WIN32PROJECT2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT4));

	MSG msg;

	ZeroMemory(&msg, 0); //�̰��� �����ΰ�


	fps.init();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}
		else
		{
			//_stprintf_s(titleFPSbuffer, TEXT("x : %f, y : %f"), pball->getPosition().x, pball->getPosition().y);
			//_stprintf_s(titleFPSbuffer, TEXT("x : %d, y : %d"), clirect.right, clirect.bottom);
			//_stprintf_s(titleFPSbuffer, TEXT("colBlockKey : %d"), collisionCheckKey);
			//_stprintf_s(titleFPSbuffer, TEXT("RGB : %d, %d, %d"), GetRValue(rainbow()), GetGValue(rainbow()), GetBValue(rainbow()));
			_stprintf_s(titleFPSbuffer, TEXT("FPS : %d"), fps.getFPS());
			SetWindowText(hWnd, titleFPSbuffer);

			fps.update();

			SCENEMNG->run(fps.getOneFrameTime());
			//myGame.update(fps.getOneFrameTime());
			//myGame.input(fps.getOneFrameTime());
			//myGame.render();

		}
	}
	return (int)msg.wParam;
}


//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT4));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT2);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 512, 568, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
		{
			SCENEMNG->add(SceneManager::LOGO, new LogoScene(hWnd));
			SCENEMNG->add(SceneManager::TITLE, new TitleScene(hWnd));
			SCENEMNG->add(SceneManager::GAME, new GameScene(hWnd));
			SCENEMNG->init(hWnd);
			//myGame.init(hWnd);
		}
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_DESTROY:
		SCENEMNG->~SceneManager();

		delete SCENEMNG;

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

COLORREF rainbow()
{
	//static int rflag, gflag, bflag;
	// static bool rmax, gmax, bmax, rmin, gmin, bmin;

	static int r(255), g(0), b(0);
	static int rflag = -1;
	static int gflag = 1;
	static int bflag = 0;
	static bool	rmax = true;
	static bool gmax = false;
	static bool	bmax = false;
	static bool	rmin = false;
	static bool	gmin = true;
	static bool	bmin = true;

	if (rmax && gmin && bmin)
	{
		rflag = 0;
		gflag = 1;
		bflag = 0;
	}
	else if (rmax && gmax && bmin)
	{
		rflag = -1;
		gflag = 0;
		bflag = 0;
	}
	else if (rmin && gmax && bmin)
	{
		rflag = 0;
		gflag = 0;
		bflag = 1;
	}
	else if (rmin && gmax && bmax)
	{
		rflag = 0;
		gflag = -1;
		bflag = 0;
	}
	else if (rmin && gmin && bmax)
	{
		rflag = 1;
		gflag = 0;
		bflag = 0;
	}
	else if (rmax && gmin && bmax)
	{
		rflag = 0;
		gflag = 0;
		bflag = -1;
	}

	r += 5 * rflag;
	g += 5 * gflag;
	b += 5 * bflag;

	if (r == 255)
		rmax = true;
	else
		rmax = false;
	if (r == 0)
		rmin = true;
	else
		rmin = false;
	if (g == 255)
		gmax = true;
	else
		gmax = false;
	if (g == 0)
		gmin = true;
	else
		gmin = false;
	if (b == 255)
		bmax = true;
	else
		bmax = false;
	if (b == 0)
		bmin = true;
	else
		bmin = false;

	return RGB(r, g, b);
}

COLORREF dark(COLORREF color)
{
	BYTE r, g, b;
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);
	if (r == 255)
		r = 150;
	if (g == 255)
		g = 150;
	if (b == 255)
		b = 150;

	return RGB(r, g, b);
}

