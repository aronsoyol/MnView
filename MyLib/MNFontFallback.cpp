#include "StdAfx.h"
#include "MNFontFallback.h"

CHAR_FONT char_font[] =
{
	{L"ᠮᠣᠩᠭᠣᠯ",		L"MNWHITE",false},
	{L"汉语",	L"@SimSun",true},
	{L"にほん",	L"@MS Mincho",true},
	//{{0x300B,0x300B},L"Arial Unicode MS",true},
	{{0xFE14,0xFE14},L"@SimSun",true},
	{{0xFF3D,0xFF3D},L"@SimSun",true},
	{{0xE800,0xE801},L"MenkSoft Qagan",false}

};
MNFontFallback::MNFontFallback(void)
{
	int comemnt_len = strlen(COMMENT);
	comment = new char[comemnt_len + 1];
	strcpy(comment, COMMENT);
	comment[comemnt_len] = '\0';
	int			itemCount;
	SCRIPT_ITEM item[2];
	HRESULT		hr;
	length		= sizeof(char_font) / sizeof(CHAR_FONT) + 1;
	pFontList	= new SCRIPT_FALLBACK[length];

	for(int i = 0; i < length - 1; i++)
	{
		hr = ScriptItemize(char_font[i].c , 1, 2, 0, 0, item, &itemCount);
		pFontList[i].eScript	= item[0].a.eScript;
		lstrcpy(pFontList[i].fontName, char_font[i].font);
	}
	pFontList[length - 1].eScript	= SCRIPT_UNDEFINED;
	lstrcpy(pFontList[length - 1].fontName, L"Arial Unicode MS");
}
bool MNFontFallback::getFallbackFont(int eScript ,WCHAR* pFontNameBuffer, int buff_length)
{
	for(int i = 0; i < length; i++)
	{
		if(pFontList[i].eScript == eScript)
		{
			if(lstrlen(pFontList[i].fontName) >= buff_length - 1)
			{
				return false;
			}
			else
			{
				if (i == 0)
				{
					int haha = 0;
				}
				lstrcpy(pFontNameBuffer,pFontList[i].fontName);
				return true;
			}
		}
	}
	//eScript not in list

	return false;
}
MNFontFallback::~MNFontFallback(void)
{
	if (length > 1)
		delete[] pFontList;
	else if (length == 1)
		delete pFontList;

	delete[] comment;
}
