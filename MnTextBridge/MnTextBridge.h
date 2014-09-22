// MnTextBridge.h

#pragma once
#include <Windows.h>
#include < stdio.h >
#include < stdlib.h >
#include "..\TextView\TextView.h"
using namespace System;

namespace MnTextBridgeDotNet {

	public ref class MnTextBridge
	{
		// TODO: Add your methods for this class here.
	public :
		bool		doInitMnTextView()
		{	
			BOOL b = InitMnTextView();
			return (b == TRUE ? true : false);
		}
		IntPtr		doCreateMnTextView(IntPtr hwndParent)
		{
			return (IntPtr)CreateMnTextView((HWND)hwndParent.ToInt32());
		}

	};
}
