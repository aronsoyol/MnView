// MnTextViewCtrl.cpp : 定义 DLL 应用程序的导出函数。
//
#include "..\TextView\TextView.h"
BOOL	 MnTextViewInit()
{
	return InitMnTextView();
}
HWND	 MnTextViewCreate(HWND hwndParent)
{
	return CreateMnTextView( hwndParent);
}
