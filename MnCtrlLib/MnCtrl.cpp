#include "StdAfx.h"
#include "MnCtrl.h"


MnCtrl::MnCtrl(void)
{
}
void MnCtrl::doInitWndClass()
{

}
void MnCtrl::WndProc(Message% m)
{
	switch (m.Msg)
			{
			case (WM_GETDLGCODE): //WM_GETDLGCODE
			{
				m.Result = (IntPtr)DLGC_WANTARROWS;   //DLGC_WANTARROWS = 1
				return;
			}
			case WM_SIZE:
				{
					int mL	= this->Margin.Left;
					int mR	= this->Margin.Right;
					int mT	= this->Margin.Top;
					int mB	= this->Margin.Bottom;
					int w	= (short)LOWORD(m.LParam.ToInt32());
					int h	= (short)HIWORD(m.LParam.ToInt32());
					int width		= w - mL - mR;
					int height		= h - mT - mB;
					HDWP hdwp		= 0;
					hdwp			= BeginDeferWindowPos(4);
					hdwp			= DeferWindowPos(hdwp, m_hWndTextView, 0, Margin.Left, Margin.Top, width, height, SWP_SHOWWINDOW);
					EndDeferWindowPos(hdwp);
					return;
				}
			case WM_SETFOCUS:
				{
					SetFocus(m_hWndTextView);
					return ;
				}
			case WM_NCDESTROY:
				{
					DeleteObject(g_hFont);
					return;
				}

			}
}
void MnCtrl::CreateWindow(HWND hWndParent, HMODULE hResModule)
{
	BOOL	ret				= InitMnTextView();
	m_hWndTextView			= CreateMnTextView(hWndParent );

				 
	HDC hdc					= GetDC(0);
	int nlogsize			= MulDiv(20, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	ReleaseDC(0, hdc);
	TextView_SetTesterMode(m_hWndTextView, 0);

	LOGFONT lfont			= {0};
	lfont.lfHeight			= nlogsize;
	lfont.lfWeight			= FW_NORMAL;
	lfont.lfCharSet			= DEFAULT_CHARSET;
	lfont.lfQuality			= ANTIALIASED_QUALITY;
	if(hResModule)
		LoadUiFont(hResModule);
	else 
		return;
	lstrcpy( lfont.lfFaceName, L"MNWHITE");
	m_hFont	= CreateFontIndirect(&lfont);
	SendMessage(m_hWndTextView,WM_SETFONT, (WPARAM)m_hFont, 0);
	TextView_SetResModule(m_hWndTextView, hResModule);
	{
		HDWP hdwp		= 0;
		hdwp			= BeginDeferWindowPos(4);
		hdwp			= DeferWindowPos(hdwp, m_hWndTextView, 0, 0, 0, 100, 100, SWP_SHOWWINDOW);
		EndDeferWindowPos(hdwp);
	}
}
void MnCtrl::doInitialise();
