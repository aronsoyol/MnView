#include "StdAfx.h"
#include "conv2galig.h"
GALIG GaligMap[]=
{
	{0x0000,			L"\0",			0},
	//{0x180e,			L"-",			0},
	{0x1820,			L"a",			0},
	{0x1821,			L"e",			0},
	{0x1822,			L"\0",			0},
	{0x1823,			L"o",			0},
	{0x1824,			L"u",			0},
	{0x1825,			L"ö",			0},
	{0x1826,			L"ü",			0},
	{0x1827,			L"e",			0},
	{0x1828,			L"n",			0},
	{0x1829,			L"ng",			0},
	{0x182a,			L"\0",			0},
	{0x182b,			L"\0",			0},
	{0x182c,			L"x",			0},
	{0x182d,			L"g",			0},
	{0x182e,			L"\0",			0},
	{0x182f,			L"\0",			0},
	{0x1830,			L"s",			0},
	{0x1831,			L"\0",			0},
	{0x1832,			L"t",			0},
	{0x1833,			L"d",			0},
	{0x1834,			L"\0",			0},
	{0x1835,			L"j",			0},
	{0x1836,			L"y",			0},
	{0x1837,			L"\0",			0},
	{0x1838,			L"w",			0},
	{0x1839,			L"\0",			0},
	{0x183a,			L"\0",			0},
	{0x183c,			L"\0",			0},
	{0x183d,			L"\0",			0},
	{0x183e,			L"x",			0},
	{0x183f,			L"\0",			0},
	{0x1840,			L"\0",			0},
	//{0x202F,			L"-",			0},

};
void Convert(WCHAR* srcString, int* destString, int length)
{
	//MENUINFO i;
	//i.dwMenuData
	//GetMenuItemInfo(
	WCHAR	*ptrSrc		= srcString  ;
	int		*ptrDst		= destString ; 
	int		maplength	= sizeof(GaligMap) / sizeof(GALIG);

	for(int i = 0; i < length && ptrSrc!=NULL; i++, ptrSrc++,ptrDst++)
	{
		*ptrDst		= 0;
		//WCHAR ch[20];
		int min		= 0;
		int max		= maplength;
		int index	= (max + min) / 2;
		//for(int j = 1;j < maplength; j++)
		while(*ptrSrc != GaligMap[index].letter && max - min > 2)
		{
			/*if(*ptrSrc == GaligMap[index].letter)
			{
				*ptrDst = index;
				wsprintf(ch,L"%d,",index);

				
			}else */
			if(*ptrSrc > GaligMap[index].letter)
			{
				min = index;
			}
			else 
			{
				max = index + 1;
			}
			index	= (max + min) / 2;
		}
		if(*ptrSrc == GaligMap[index].letter)
		{
			*ptrDst = index;
		}
		else
		{
			*ptrDst = 0;
		}

		
	}
	OutputDebugString(L"Convert 2 galig\n");
//	OutputDebugString(L"\n");
}
///ptrDsturn  1.阳性 -1.阴性 0.中性 
int VowelKind( WCHAR* code)
{
	if (*code == 0x1820 || *code == 0x1823 || *code == 0x1824)//a,w.v阳
		return 1;
	else if (*code == 0x1822)//i中性
		return 0;
	else
		return -1;//阴
}