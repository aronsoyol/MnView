#pragma once
#include "..\TextView\TextView.h"
#include <Windows.h>
ref class MnCtrl
{
	HWND	m_hWndTextView;
	HFONT	m_hFont;
	HMODULE	m_hModule;

public:
	MnCtrl(void);
	void CreateWindow(HWND parentHwnd, HMODULE hResModule);
	void OnSize(int width, iint height);
	void OnSetFocus();
	void OnDestroy();
	void OnGetDlgCode();
	void LoadUiFont();

};

