﻿// GameDevExper02.cpp : 定义应用程序的入口点。
//

#include "pch.h"
#include "framework.h"
#include "GameDevExper02.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

HDC hdc;										//内存句柄
HDC HMemDC;										//兼容内存句柄
HBITMAP hmap;									//位图
RECT rect;										//获取窗口大小
DWORD startX;
DWORD startY;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GAMEDEVEXPER02, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEDEVEXPER02));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GAMEDEVEXPER02);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	//我加的代码**********
	hdc = GetDC(hWnd);
	HMemDC = CreateCompatibleDC(hdc);
	GetClientRect(hWnd, &rect);
	SelectObject(HMemDC, hmap);
	hmap = CreateCompatibleBitmap(hdc, rect.left, rect.top);
	//结束**********

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		startX = LOWORD(lParam);
		startY = HIWORD(lParam);
		DrawIcon(HMemDC, startX - 12, startY - 8, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON4)));
		break;
	case WM_MOUSEMOVE:
		if (wParam == MK_LBUTTON)
		{
			startX = LOWORD(lParam);
			startY = HIWORD(lParam);
			DrawIcon(HMemDC, startX - 12, startY - 8, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON4)));
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			startY -= 6;
			DrawIcon(HMemDC, startX - 12, startY - 8, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON4)));
			break;
		case VK_DOWN:
			startY += 6;
			DrawIcon(HMemDC, startX - 12, startY - 8, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON4)));
			break;
		case VK_LEFT:
			startX -= 6;
			DrawIcon(HMemDC, startX - 12, startY - 8, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON4)));
			break;
		case VK_RIGHT:
			startX += 6;
			DrawIcon(HMemDC, startX - 12, startY - 8, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON4)));
		default:
			break;
		}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择:
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
		//PAINTSTRUCT ps;
		//HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, HMemDC, rect.left, rect.top, SRCCOPY);
		//EndPaint(hWnd, &ps);
	}
	break;
	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		if (rect.right>900)
		{
			BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, HMemDC, rect.left, rect.top, SRCCOPY);
			hmap = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
			SelectObject(HMemDC, hmap);
			BitBlt(HMemDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdc, rect.left, rect.top, SRCCOPY);
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

// “关于”框的消息处理程序。
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