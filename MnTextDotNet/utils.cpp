#include "stdafx.h"
#include "resource.h"
#include <Windows.h>

bool LoadUiFont (HMODULE hModule)
{
	HRSRC	hRSrc	= 0;

	if(hModule)
	{
		//hRSrc	= FindResource(hModule, MAKEINTRESOURCE(IDR_RT_FONT1), L"RT_FONT");
	}
	else return false;
	HGLOBAL	hGlobal;
	DWORD	dwSize, dwInst;
	LPVOID	lpLock = NULL;
	HANDLE	hResFont;
	if(hRSrc)
	{
		hGlobal = LoadResource( hModule, hRSrc );
		if( hGlobal != NULL )
		{
			dwSize = SizeofResource( hModule, hRSrc );

			lpLock = LockResource( hGlobal );
			if( lpLock != NULL ){
				hResFont = AddFontMemResourceEx( lpLock, dwSize, NULL, &dwInst );
				return true;
			}

			
		}
	}
	return false;
}