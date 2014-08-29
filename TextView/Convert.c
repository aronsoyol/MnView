#include <windows.h>
#include "textview.h"

encoding_type Encoding_Lookup[2] = 
{
	{L"UNICODE - UTF16",	NCP_UTF16},
	{L"UNICODE - UTF8",		NCP_UTF8 }
};