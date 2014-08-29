#include "StdAfx.h"
#include "MNFont.h"
#include <stdlib.h>
#include <crtdbg.h>
int MNFont::s_count = 0;
MNFont::MNFont(void):
	m_fontName	(L"arongsuyila"),
	m_size  	(20),
	m_bold  	(false),
	m_italic 	(false),
	m_underLine	(false),
	m_hFont		(0),
	m_cache		(0),
	tm			( )
{
	s_count++;
}

//MNFont::MNFont(const MNText& name,UINT size,bool bold ,bool italic ,bool underLine ):
//	m_fontName	(name),
//	m_size  	(size),
//	m_bold  	(bold),
//	m_italic 	(italic),
//	m_underLine	(underLine),
//	m_hFont		(0),
//	m_cache		(0)
//	
//{
//	s_count++;	//createFont();
//}

MNFont::MNFont(const MNFont& src):
	m_fontName	(src.m_fontName),
	m_size  	(src.m_size),
	m_bold  	(src.m_bold),
	m_italic 	(src.m_italic),
	m_underLine	(src.m_underLine),
	m_hFont		(0)	,
	m_cache		(0)
{
	s_count++;	//createFont();
}
bool MNFont::like(const MNText& name, UINT size, bool bold, bool italic, bool underLine, bool rotate)
{
	if( m_size		== size
	 && m_bold		== bold
	 && m_italic	== italic
	 && m_underLine	== underLine
	 && m_fontName	== name )
	 return true;
	else
		return false;
}

void MNFont::init(HFONT hFont)
{
	freeResourse();
	//_CrtDumpMemoryLeaks();
	LOGFONT lf;
	HDC hdc		= GetDC(NULL);
	HFONT old	= (HFONT)SelectObject(hdc, hFont);
	GetTextMetrics(hdc, &tm);
	GetObject(hFont,sizeof(lf), &lf);

	m_hFont		= hFont;
	m_fontName	= MNText(lf.lfFaceName);
	m_size		= /*lf.lfHeight > 0 ? */MulDiv(lf.lfHeight, GetDeviceCaps(hdc, LOGPIXELSY), 72) /*: -lf.lfHeight*/;
	m_bold		= lf.lfWeight;
	m_italic	= lf.lfItalic;
	m_underLine	= lf.lfUnderline;
	
	SelectObject(hdc, old);
	DeleteObject(old);
	ReleaseDC(NULL, hdc);
	
}

bool MNFont::calcMetrics(HDC hdc)
{
	HFONT old	= (HFONT)SelectObject(hdc, m_hFont);
	if(GetTextMetrics(hdc, &tm))
	{
		SelectObject(hdc, old);
		return true;
	}
	return false;
}

void MNFont::init(const MNText& name, UINT size, bool bold, bool italic, bool underLine, bool rotate )
{
	freeResourse();
	m_fontName	= name ;
	m_size  	= size ;
	m_bold  	= bold ;
	m_italic 	= italic ;
	m_underLine	= underLine ;
	m_rotate	= rotate;

	HDC hdc		= GetDC(NULL);

	if(createFont())
	{
		HFONT old	= (HFONT)SelectObject(hdc, m_hFont);
		GetTextMetrics(hdc, &tm);
		SelectObject(hdc, old);
	}
	
	ReleaseDC(NULL, hdc);
}

MNFont::~MNFont(void)
{
	if(m_hFont != 0)
		freeResourse();
	s_count--;
}

bool MNFont::operator == (const MNFont& src)
{
	if( m_size		== src.m_size 
	 && m_bold		== src.m_bold 
	 && m_italic	== src.m_italic 
	 && m_underLine	== src.m_underLine 
	 && m_fontName	== src.m_fontName )
	 return true;
	else
		return false;
}
bool MNFont::operator != (const MNFont& src)
{
	if( m_size		== src.m_size 
	 && m_bold		== src.m_bold 
	 && m_italic	== src.m_italic 
	 && m_underLine	== src.m_underLine 
	 && m_fontName	== src.m_fontName )
		return false;
	else
		return true;
}
MNFont&	MNFont::operator  = (const MNFont& src)
{
	m_size		= src.m_size ;
	m_bold		= src.m_bold ;
	m_italic	= src.m_italic ;
	m_underLine	= src.m_underLine ;
	m_fontName	= src.m_fontName ;

	if(m_hFont != 0)
		freeResourse();

	return *this;
}
void MNFont::freeResourse()
{
	DeleteObject( m_hFont);
	ScriptFreeCache(&m_cache);
	m_hFont = 0;
	m_cache = 0;
}

bool MNFont::createFont()
{	
	int weight	= m_bold?FW_BOLD:FW_DONTCARE;
	int size	= m_size;
	int angle	= 0;
	WCHAR face[50];
	if(m_rotate)
	{
		face[0] = '@'; 
		lstrcpy(face + 1, m_fontName);
		face[m_fontName.getLength() + 1] = '\0';
	}else
	{
		lstrcpy(face, m_fontName);
		face[m_fontName.getLength()] = '\0';
	}

	m_hFont = CreateFont(
		size,
		0,
		0,
		0,
		weight,
		m_italic,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS,
		0,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH,
		m_fontName
	);
	if(m_hFont == 0)
		return false;
	else
		return true;
}
//HFONT MNFont::getHFont();

