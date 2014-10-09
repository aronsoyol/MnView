//
//	MODULE:		TextView.cpp
//
//	PURPOSE:	Implementation of the TextView control
//
//
#define _WIN32_WINNT 0x501
#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

// for the EM_xxx message constants
#include <richedit.h>
#include <shellapi.h>
#include "TextView.h"
//#include "TextViewInternal.h"
#include "MnTextView.h"
#include "racursor.h"

#if !defined(UNICODE)
#error "Please build as Unicode only!"
#endif

#if !defined(GetWindowLongPtr)
#error "Latest Platform SDK is required to build Neatpad - try PSDK-Feb-2003
#endif

#pragma comment(lib, "comctl32.lib")
//static MnCursor mnCursor;
//
//	Constructor for TextView class
//

LRESULT WINAPI MnTextViewWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	MnTextView *ptv = (MnTextView *)GetWindowLongPtr(hwnd, 0);

	switch(msg)
	{
	// First message received by any window - make a new TextView object
	// and store pointer to it in our extra-window-bytes

	case WM_NCCREATE:
	{
		//_CrtDumpMemoryLeaks();
		if((ptv = new MnTextView(hwnd)) == 0)
			return FALSE;

		SetWindowLongPtr(hwnd, 0, (LONG)ptv);

		

		return TRUE;
	}
	// Last message received by any window - delete the TextView object
	case WM_NCDESTROY:
		delete ptv;
		SetWindowLongPtr(hwnd, 0, 0);
		return 0;


	// Pass everything to the TextView window procedure
	default:
		if(ptv)
			return ptv->WndProc(msg, wParam, lParam);
		else
			return 0;
	}
}

//
//	Register the TextView window class
//
BOOL InitMnTextView()
{
	WNDCLASSEX	wcx;
	//HCURSOR  cursor = LoadCursor (GetModuleHandle(0), MAKEINTRESOURCE(132));
	//Window class for the main application parent window
	wcx.cbSize			= sizeof(wcx);
	wcx.style			= /*CS_HREDRAW | CS_VREDRAW |*/ CS_DBLCLKS /*| CS_DROPSHADOW*/;
	wcx.lpfnWndProc		= MnTextViewWndProc;
	wcx.cbClsExtra		= 0;
	wcx.cbWndExtra		= sizeof(MnTextView *);
	wcx.hInstance		= (HINSTANCE)GetModuleHandle(0);
	wcx.hIcon			= 0;
	wcx.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground	= (HBRUSH)0;		//NO FLICKERING FOR US!!
	wcx.lpszMenuName	= 0;
	wcx.lpszClassName	= MNTEXTVIEW_CLASS;	
	wcx.hIconSm			= 0;

	return RegisterClassEx(&wcx) ? TRUE : FALSE;
}

//
//	Create a TextView control!
//
HWND CreateMnTextView(HWND hwndParent)
{
 
	HWND hWnd = CreateWindowEx(
		/*WS_EX_STATICEDGE*/0, 
//		L"EDIT", L"",
		MNTEXTVIEW_CLASS, _T("MnTextView"), 
		WS_HSCROLL | WS_CHILD | WS_VISIBLE /*|WS_BORDER*/ ,
		0, 0, 0, 0, 
		hwndParent, 
		0, 
		GetModuleHandle(0), 
		0);
	if(hWnd == 0)
	{
		DWORD error = GetLastError();
		BOOL b = IsWindow (hwndParent);
		int i=0;
	}
	return hWnd;
}

HWND CreateMnConvertTextView(HWND hwndParent)
{
	
	HWND me = CreateWindowEx(WS_EX_CLIENTEDGE, 
//		L"EDIT", L"",
		MNTEXTVIEW_CLASS, _T("MnConvertView"), 
		WS_HSCROLL | WS_POPUPWINDOW | WS_VISIBLE | WS_CAPTION,
		0, 0, 400, 400, 
		hwndParent, 
		0, 
		GetModuleHandle(0), 
		0
	);
		UpdateWindow(me);
	TextView_Clear(me);
	ShowWindow(me, SW_SHOW);

	return me;
}