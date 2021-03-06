// MongolDotNet.cpp: 主项目文件。

#include "stdafx.h"
#include "MongolDotNet.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
namespace MongolDotNet {
	void MnTextView::WndProc(Message% m)
	{

		if (this->DesignMode || (m_pTextVeiw->GetHwnd() == 0 && m.Msg != WM_NCCREATE))
		{
			TextBox::WndProc(m);
			return;
		}
		UINT_PTR wParam = safe_cast<WPARAM>(m.WParam.ToInt64());
		LONG_PTR lParam = safe_cast<LPARAM>(m.LParam.ToInt64());
		switch (m.Msg)
		{

		case WM_NCCREATE:
		{
			HWND hWnd	= (HWND)m.HWnd.ToInt32();
			LONG style	= GetWindowLongPtr(hWnd, GWL_STYLE);
			style &= ~WS_VSCROLL;
			SetWindowLongPtr(hWnd, GWL_STYLE, WS_HSCROLL /*| WS_BORDER*/ | style);
			
			//m_pTextVeiw = new MnTextBoxApi(hWnd);
			m_pTextVeiw->SetHwnd(hWnd);
			TextBox::WndProc(m);
			return;
		}
		//case WM_NCDESTROY:
		//{
		//	//delete m_pTextVeiw;
		//	TextBox::WndProc(m);
		//	return;
		//}

		case EM_SETSEL:
		case EM_GETSEL:
		{
			long ret = 0;
			if (m_pTextVeiw->HandleWndProc(m.Msg, wParam, lParam, &ret))
			{
				m.Result = (IntPtr)ret;
			}
			return;
		}
		//case WM_SETFOCUS:
		//case WM_KILLFOCUS:
		//case WM_SETFONT:
		//case WM_MOUSEACTIVATE:
		//case WM_MOUSEWHEEL:
		//case WM_MOUSEMOVE:
		//case WM_LBUTTONDOWN:
		//case WM_LBUTTONUP:
		//case WM_LBUTTONDBLCLK:
		//case WM_SIZE:
		//case WM_PAINT:
		//case WM_VSCROLL:
		//case WM_HSCROLL:
		//case WM_KEYDOWN:
		//	{
		//		KeyDown(this, gcnew KeyEventArgs());
		//	}
		//case WM_CHAR:
		//case WM_SETCURSOR:
		//case WM_TIMER:
		//	{
		//		//HWND hwnd		= (HWND)m.HWnd.ToInt32();
		//		//HWND thisHwnd	= (HWND)this->Handle.ToInt32();
		//		//if (hwnd != thisHwnd)
		//		//{
		//		//	assert(hwnd == m_hWndTextView);
		//		//}
		//		//TextBox::WndProc(m);
		//		//if (m.)
		//		m.Result = (IntPtr)m_pTextVeiw->WndProc(m.Msg, m.WParam.ToInt32(), m.LParam.ToInt32());
		//		return;
		//	}
		case WM_CHAR:
		{
			KeyPressEventArgs^ arg = gcnew KeyPressEventArgs((wchar_t)m.WParam.ToInt32());
			//arg->
			KeyPress(this, arg);
			if (arg->Handled)
				return;
			break;
		}
		case WM_NOTIFY:
			{
			
				NMHDR *nmhdr = (NMHDR*)(lParam);// lParam;

				if (nmhdr->hwndFrom == (HWND)this->Handle.ToInt64())
				{
					switch (nmhdr->code)
					{
					case TVN_CHANGED:
						{
						
							//if (TextChanged != nullptr)
							//{
								this->TextChanged(this, gcnew System::EventArgs());
							//}
						}
					}
				}
				break;
			}
		case WM_ERASEBKGND:
		case WM_NCPAINT:
			TextBox::WndProc(m);
			return;
		
		//case WM_GETDLGCODE:

		
		//case WM_IME_STARTCOMPOSITION:
		//case WM_IME_COMPOSITION:
		//case WM_IME_ENDCOMPOSITION:
		//case WM_IME_CHAR:
		//case WM_IME_CONTROL:
		//case WM_IME_NOTIFY:
		//case WM_IME_REQUEST:
		//case WM_INPUTLANGCHANGE:
			//{
			//	m.Result = (IntPtr)m_pTextVeiw->WndProc(m.Msg, m.WParam.ToInt32(), m.LParam.ToInt32());
			//	return;
			//}
		default:
			{
			break;
			
			}
		}
		long ret = 0;
		
		if (m.Msg >= WM_MOUSEFIRST && m.Msg <= WM_MOUSELAST
			|| m.Msg >= WM_KEYFIRST && m.Msg <= WM_KEYLAST/* && m.Msg != WM_CHAR*/)
		{
			if (m.Msg != WM_CHAR)
				TextBox::WndProc(m);
			
			

			if (m_pTextVeiw->HandleWndProc(m.Msg, wParam, lParam, &ret))
			{
				m.Result = (IntPtr)ret;
			}
			return;
		}
		if (m_pTextVeiw == nullptr)
		{
			int haha = 0;
		}
		if (m_pTextVeiw->GetHwnd() != 0 && m_pTextVeiw->HandleWndProc(m.Msg, wParam, lParam, &ret))
		{
			m.Result = (IntPtr)ret;
		}
		else
		{
			TextBox::WndProc(m);
		}
		return;
		
	}
}