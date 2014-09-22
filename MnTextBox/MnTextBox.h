#pragma once
#include <Windows.h>
namespace MongolDotNet
{
	ref class MnTextBox :public System::Windows::Forms::TextBox
	{
	private:
		HWND m_hWndTextView;
	public:
		MnTextBox();
		override WndProc()
		{

		}
	};

}