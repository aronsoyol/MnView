#include "StdAfx.h"
#include "mylib.h"
#include "MNLineGlyfCache.h"
// TODO: 在 mylib.h 中
// 引用任何所需的附加头文件，而不是在此文件中引用


bool operator >(const _CHAR_POS& cp1,const _CHAR_POS& cp2)
{
	if(cp1.logLine > cp2.logLine)return true;
	if(cp1.logLine == cp2.logLine)
	{
		if(cp1.index  > cp2.index )return true;
		if(cp1.index  == cp2.index )
			if(cp1.trailing > cp2.trailing)return true;
	}
	return false;
}
bool operator <(const _CHAR_POS& cp1,const _CHAR_POS& cp2)
{
	if(cp1.logLine < cp2.logLine)return true;
	if(cp1.logLine == cp2.logLine)
	{
		if(cp1.index  < cp2.index )return true;
		if(cp1.index  == cp2.index )
			if(cp1.trailing < cp2.trailing)return true;
	}
	return false;
}
bool operator ==(const _CHAR_POS& cp1,const _CHAR_POS& cp2)
{
	if(cp1.logLine	== cp2.logLine
	&& cp1.index	== cp2.index
	&& cp1.trailing == cp2.trailing) return TRUE;
	return false;
}
bool operator !=(const _CHAR_POS& cp1,const _CHAR_POS& cp2)
{
	if(cp1.logLine	!= cp2.logLine
	|| cp1.index	!= cp2.index
	|| cp1.trailing != cp2.trailing) return TRUE;
	return false;
}
bool MnMesureString(HDC hDc, HFONT hFont, WCHAR *pText, int length, __out SIZE *pSize)
{
	if(length <=0 || pText == NULL || pText[0] == '\0' || pSize == NULL)return false;
	MNLineGlyfCache cache;
	MNFontManager	fm ;//= MNFontManager();
	HFONT			tmpHfont ;
	LOGFONT			lf		= {0};
				//HFONT	sysFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT);
				
	GetObject(hFont,sizeof(LOGFONT),(LPVOID)&lf); 
	tmpHfont = CreateFontIndirect(&lf);
	fm.setPrimaryFont(tmpHfont);


	cache.initialize(0, 0, pText, length, &fm);
	cache.generateGlyph(hDc, pText, length);
	cache.breakLine(100000);

	pSize->cx = cache.getLineWidth(0);
	pSize->cy = fm.getLineHeight();
	return true;

	
}
void MnDrawString(HDC hdc, int x ,int y, WCHAR *pText, int length, RECT *pRect, MDS_ALIGN nAlign )
{
	//SCRIPT_ITEM		items[10];
	//SCRIPT_CONTROL	sc	= {0};
	//SCRIPT_STATE	ss	= {0};
	//
	//int		itemCount	= 0 ;
	//HRESULT hr			= S_FALSE;


	//ScriptItemize(pText, length, 10, &sc, &ss, &items, &itemCount);
	//if(hr == S_OK)
	//{
	//	for(int i = 0; i<itemCount; i++)
	//	{
	//		ScriptShape(
	//	}
	//}
}
void MnDrawString(HDC hDc, HFONT hFont, int x ,int y, WCHAR *pText, int length, RECT *pRect, MDS_ALIGN nAlign , COLORREF *pCol)
{
	if(length <=0 || pText == NULL || pText[0] == '\0')return ;
	MNLineGlyfCache cache;
	MNFontManager	fm ;//= MNFontManager();
	HFONT			tmpHfont ;
	LOGFONT			lf		= {0};
				//HFONT	sysFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT);
				
	GetObject(hFont,sizeof(LOGFONT),(LPVOID)&lf); 
	tmpHfont = CreateFontIndirect(&lf);
	fm.setPrimaryFont(tmpHfont);


	cache.initialize(0, 0, pText, length, &fm);
	cache.generateGlyph(hDc, pText, length);
	cache.breakLine(100000);
	if(pCol)
		cache.setFgColor(0, length, *pCol);
	int w = cache.getLineWidth(0);
	switch(nAlign)
	{
	case MDS_ALIGN_CENTER:
		if(pRect){
			x += (pRect->right - pRect->left -w) /2 ;
		}
		break;
	case MDS_ALIGN_RIGHT:
		if(pRect){
			x += (pRect->right - pRect->left -w) ;
		}
		break;
	default:
		break;
	}
	cache.drawSubLine(&hDc, 0, x, y);
	DeleteObject(tmpHfont);
}