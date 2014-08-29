#pragma once
#include <Windows.h>
#include < stdio.h >
#include < stdlib.h >
#include < vcclr.h >
#include "utils.h"
#include "..\TextView\TextView.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
namespace MongolDotNet {

	/// <summary>
	/// MnTextView 摘要
	/// </summary>
	//[System.Drawing.ToolboxBitmap()]
	[System::Drawing::ToolboxBitmapAttribute("D:\\MnViewDotNet\\Untitled.bmp")]
	public ref class MnTextView : public System::Windows::Forms::UserControl
	{

		//int MyInt;
		//public:
		//[Browsable(true)]
		//property int HaHa {
		//	int get() {
		//		
		//		return MyInt;
		//	}
		//    void set(int value) {
		//		MyInt = value;
		//	}      
		//}
		//System::Windows::Forms::UserControl::

		//String^ _text;
		//virtual property String^ Text
		//{
		//	String^ get()  override = System::Windows::Forms::UserControl::
		//	{
		//		return _text;
		//	}
		//	void Set(String^ str)
		//	{
		//		_text = str;
		//	}
		//}
	
	public:
		
		MnTextView(void)
		{
			_text			= L"";
			m_hWndTextView	= 0;
			g_hFont			= 0;
			g_hModule		= 0;
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}
	

		[Browsable(true)]
		virtual property System::String^ Text
		{
			System::String^ get() override 
			{
				//String^ text;
				//WCHAR *	buffer = 0;
				//ULONG	length = TextView_GetTextLen(m_hWndTextView);
				//if(length > 0)
				//{
				//	//buffer = new WCHAR[length + 1];
				//	//return gcnew String^(buffer);
				//}
				return _text; 
			}
			void set(System::String^ value) override 
			{
				_text = value;
				if(m_hWndTextView)
				{
					pin_ptr<const wchar_t> wch = PtrToStringChars(value);
					TextView_SetText(m_hWndTextView, wch);
				}
			}
		}
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MnTextView()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container^ components;
		HWND		m_hWndTextView;
		HFONT		g_hFont;
		HMODULE		g_hModule;
		String^		_text ;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MnTextView
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(0);
			this->Name = L"MnTextView";
			this->Size = System::Drawing::Size(53, 182);
			this->Load += gcnew System::EventHandler(this, &MnTextView::MnTextView_Load);
			this->ResumeLayout(false);

		}
		protected: virtual void WndProc(Message% m) override
		{
			if(this->DesignMode) 
			{
				return UserControl::WndProc(m);
			}
			switch (m.Msg)
			{
			case (0x87): //WM_GETDLGCODE
			{
				m.Result = (IntPtr)1;   //DLGC_WANTARROWS = 1
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
			UserControl::WndProc(m);
		}
#pragma endregion
	private: System::Void MnTextView_Load(System::Object^  sender, System::EventArgs^  e) {
				 if(this->DesignMode) return ;
				 //bool	 ret			= tvinit();

				 g_hModule				= (HMODULE)Marshal::GetHINSTANCE(this->GetType()->Module).ToInt64();
				 HWND	parenthwnd		= (HWND)(this->Handle.ToInt64());
				 BOOL	ret				= InitMnTextView();
				 m_hWndTextView			= CreateMnTextView(parenthwnd );

				 
				 HDC hdc				= GetDC(0);
				int nlogsize			= MulDiv(20, GetDeviceCaps(hdc, LOGPIXELSY), 72);
				ReleaseDC(0, hdc);
				SendMessage(m_hWndTextView, WM_USER + 39, 0,0);
				LOGFONT lfont = {0};
				lfont.lfHeight		= nlogsize;
				lfont.lfWeight		= FW_NORMAL;
				lfont.lfCharSet		= DEFAULT_CHARSET;
				lfont.lfQuality		= ANTIALIASED_QUALITY;
				if(g_hModule)
					LoadUiFont(g_hModule);
				else 
					return ;
				lstrcpy( lfont.lfFaceName, L"MNWHITE");
				g_hFont	= CreateFontIndirect(&lfont);
				SendMessage(m_hWndTextView,WM_SETFONT, (WPARAM)g_hFont, 0);
				TextView_SetResModule(m_hWndTextView,g_hModule);
				{

					int mL	= this->Margin.Left;
					int mR	= this->Margin.Right;
					int mT	= this->Margin.Top;
					int mB	= this->Margin.Bottom;
					int w	= this->Width;
					int h	= this->Height;
					int width		= w - mL - mR;
					int height		= h - mT - mB;
					HDWP hdwp		= 0;
					hdwp			= BeginDeferWindowPos(4);
					hdwp			= DeferWindowPos(hdwp, m_hWndTextView, 0, Margin.Left, Margin.Top, width, height, SWP_SHOWWINDOW);
					EndDeferWindowPos(hdwp);
				}
				if(m_hWndTextView)
				{
					pin_ptr<const wchar_t> wch = PtrToStringChars(_text);
					TextView_SetText(m_hWndTextView, wch);
				}
			 }
			 
	};
}
