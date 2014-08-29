#pragma once
#include <windows.h>
#include <usp10.h>
#define COMMENT "this is MNFontFallback class ,this class will be define as a static member, and will be destructed when destroy the application."
typedef struct _CHAR_FONT
{
	WCHAR c[10];
	WCHAR font[50];
	bool	bCJK;
}CHAR_FONT;
typedef struct _SCRIPT_FALLBACK
{
	WORD eScript;
	WCHAR fontName[50];
}SCRIPT_FALLBACK;

class MNFontFallback
{
	char *			comment;
	SCRIPT_FALLBACK * pFontList;
	int length;
public:
	MNFontFallback(void);
	bool getFallbackFont(int eScript ,WCHAR* pFontNameBuffer, int buff_length);
public:
	virtual ~MNFontFallback(void);
};
