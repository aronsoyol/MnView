#pragma once
#include <Windows.h>


#include "..\TextView\MnTextBoxApi.h"
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
	[System::Drawing::ToolboxBitmapAttribute("D:\\MnTextDotNet\\Untitled.bmp")]
	public ref class MnTextView : public System::Windows::Forms::TextBox
	{
	public:MnTextView(void)
	{
		m_pTextVeiw = new MnTextBoxApi(0);
		TextBox::Multiline = true;
		ShowFocusCues = false;
		int i = 0;
	}
	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>

		//HWND				m_hWndTextView;
		//HWND			*	m_phWnd;
		MnTextBoxApi	*	m_pTextVeiw;
		//int					m_msgroop;
	public:
		virtual event System::EventHandler^	TextChanged;
		virtual event System::EventHandler^ BackColorChanged;
		virtual event System::EventHandler^ ForeColorChanged;
		virtual event System::Windows::Forms::KeyPressEventHandler^ KeyPress;
		//virtual event System::Windows::Forms::KeyEventHandler^ KeyDown;
		//virtual event System::Windows::Forms::KeyPressEventHandler^ KeyPress;
		//virtual event System::Windows::Forms::KeyEventHandler^ KeyUp;
	//private:
		//[Browsable(false)]
		////[System::brow]
		//virtual property bool Multiline
		//{
		//	bool get() override
		//	{
		//		return true;
		//	}
		//	void set(bool) override
		//	{
		//		TextBox::Multiline = true;
		//		return;
		//	}
		//}
	public:
		virtual void Redo()
		{
			if (m_pTextVeiw->ApiCanRedo())
				m_pTextVeiw->ApiRedo();
			//this->KeyPress
		}
		//virtual property int SelectionLength
		//{
		//	int get() override
		//	{
		//		return m_pTextVeiw->ApiGetSelLength();
		//	}
		//	void set(int len) override
		//	{
		//		m_pTextVeiw->ApiSetSellength(len);
		//	}
		//}
		virtual property bool ShowFocusCues
		{
			bool get() override
			{

				bool b = m_pTextVeiw->GetProperty_DrawFocusRect();
				return b;

			}
			void set(bool value) 
			{

				m_pTextVeiw->SetProperty_DrawFocusRect(value);

				//else
				//	return TextBox::ShowFocusCues = value;
			}
		}
		virtual property System::Drawing::Color BackColor
		{
			System::Drawing::Color get() override
			{
				COLORREF colRef = m_pTextVeiw->ApiGetBackColor();
				return System::Drawing::Color::FromArgb(GetRValue(colRef), GetGValue(colRef), GetBValue(colRef));

			}
			void set(Color col) override
			{

				int c1 = col.ToArgb();
				int c2 = RGB(col.R, col.G, col.B);
				m_pTextVeiw->ApiSetBackColor(c2);
				BackColorChanged(this, gcnew EventArgs());

			}
		}
		virtual property System::Drawing::Color ForeColor
		{
			System::Drawing::Color get() override
			{
				COLORREF colRef = m_pTextVeiw->ApiGetForeColor();
				return System::Drawing::Color::FromArgb(GetRValue(colRef), GetGValue(colRef), GetBValue(colRef));

			}
			void set(Color col) override
			{

				int c1 = col.ToArgb();
				int c2 = RGB(col.R, col.G, col.B);
				m_pTextVeiw->ApiSetForeColor(c2);
				ForeColorChanged(this, gcnew EventArgs());

			}
		}
		//virtual property System::Drawing::Font^ Font {
		//	System::Drawing::Font^ get() override;
		//	void set(System::Drawing::Font^ font) override;
		//}

		//virtual property System::String^ Text
		//{
		//	System::String^ get() override
		//	{
		//		return TextBox::Text;
		//	}
		//	void set(System::String^ value) override
		//	{
		//		TextBox::Text = value;
		//		//TextBox:
		//	}
		//}
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MnTextView()
		{
			delete m_pTextVeiw;
		}

	protected: virtual void WndProc(Message% m) override;
	 

	//private: System::Void InitializeComponent() {
	//	this->SuspendLayout();
	//	// 
	//	// MnTextBox
	//	// 
	//	this->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
	//		static_cast<System::Byte>(128)));
	//	this->ResumeLayout(false);
	//}
	//private: System::Void InitializeComponent() {
	//	this->SuspendLayout();
	//	// 
	//	// MnTextBox
	//	// 
	//	this->Text = L"zxczxcv";
	//	this->ResumeLayout(false);
	//}


	private: System::Void InitializeComponent() {
		this->SuspendLayout();
		// 
		// MnTextBox
		// 
		this->Text = L"ljgjhgjh";
		this->ResumeLayout(false);
	}
	};
}
