#include "StdAfx.h"
#include "MNFontManager.h"
#define  PHONE_FONT_SCALE	0.4f
#define  PHONE_SPACE		0.1f
MNFontManager::MNFontManager(void):
	m_maxDescent	(INT_MIN),
	m_maxAscent		(INT_MIN),
	m_fontList		(MAX_FONTLIST_LENGTH),
	m_count			(   1   ),
	m_PhoneticFont	(   0   ),
	m_PhoneticFontInternalLeading(0),
	m_PhoneticSpace	(	PHONE_SPACE	),
	m_fTesterViewMode(false)
{
//m_PhoneticSpace  = 0;
}

MNFontManager::~MNFontManager(void)
{
	int count = m_fontList.size();
	for(int i = 0; i < count; i++)
	{
		//delete m_fontList[i];
	}
	DeleteObject(m_PhoneticFont);
}
int MNFontManager::queryFont(const MNText& fontName, UINT size, BOOL bBold, BOOL bItalic, BOOL bUline, BOOL rotate)
{
	for(int i = 0; i < m_count; i++)
	{
		if(m_fontList[i].like(fontName, size, bBold, bItalic, bUline, rotate))
		{
			return i;
		}
	}
	return -1;
}
int MNFontManager::addFont(const MNText& fontName, UINT size, BOOL bBold, BOOL bItalic, BOOL bUline, BOOL rotate)
{
	//MNFont*	newFont	= new MNFont();
	
	m_fontList[m_count ++].init(fontName, size, bBold, bItalic, bUline,rotate);
	updateMetrics();
	if(m_fTesterViewMode)
	{
		UpdatePhoneticFont();
		UpdatePhoneticOffset();
	}
	return m_count - 1;
}
void MNFontManager::setPrimaryFont(HFONT hFont)
{
	m_fontList[0].init(hFont);
	m_count	= 1;
	updateMetrics();
	if(m_fTesterViewMode)
	{
		UpdatePhoneticFont();
		UpdatePhoneticOffset();
	}
	
	//_CrtDumpMemoryLeaks();
}
//void MNFontManager::setPrimaryFont(const MNText& fontName, UINT size, BOOL bBold, BOOL bItalic, BOOL bUline)
//{
//	if(m_fontList.size() == 0)
//	{
//		m_fontList.resize(1);
//	}
//	m_fontList[0]->init(fontName, size, bBold, bItalic, bUline);
//	updateMetrics();
//	_CrtDumpMemoryLeaks();
//}
int MNFontManager::getFontIndex(const MNText& fontName, UINT size, BOOL bBold, BOOL bItalic, BOOL bUline, BOOL rotate)
{
	int index = queryFont(fontName, size, bBold, bItalic, bUline, rotate);
	if(index >= 0 )
		return index;
	else
		return addFont(fontName, size, bBold, bItalic, bUline, rotate);
}
UINT MNFontManager::getLineHeight()
{
	if(m_fTesterViewMode)
		return (UINT)(m_maxDescent + m_maxAscent + m_maxExternalLeading + m_PhoneticOffset);
	else 
		return (UINT)(m_maxDescent + m_maxAscent + m_maxExternalLeading);
}
UINT MNFontManager::calcLineHeight(HDC hdc)
{
	for(int i = 0; i < m_count; i++ )
	{
		if(!m_fontList[i].calcMetrics(hdc))
		{
			throw MnException();
		}
	}
	updateMetrics();
	return getLineHeight();
}
void MNFontManager::updateMetrics()
{
	m_maxDescent			= INT_MIN;
	m_maxAscent				= INT_MIN;
	m_maxInternalLeading	= INT_MIN;
	m_maxExternalLeading	= INT_MIN;

	for(int i = 0; i < m_count; i++ )
	{
		m_maxDescent		= max(m_fontList[i].tm.tmDescent			, m_maxDescent	);
		m_maxAscent			= max(m_fontList[i].tm.tmAscent				, m_maxAscent	);
		m_maxInternalLeading= max(m_fontList[i].tm.tmInternalLeading	, m_maxInternalLeading	);
		m_maxExternalLeading= max(m_fontList[i].tm.tmExternalLeading	, m_maxExternalLeading	);
	}

}
HFONT MNFontManager::getFont(int index)
{
	return m_fontList[index].m_hFont;
}
void MNFontManager::UpdatePhoneticFont()
{
	if(!m_fTesterViewMode) 
		return;
	bool fCreateFont = false;
	if(m_PhoneticFont == 0)
		fCreateFont = true;
	else
	{
		LOGFONT lFont;
		GetObject(m_PhoneticFont, sizeof(lFont), &lFont);
		if(lFont.lfHeight != -(m_maxDescent + m_maxAscent) * PHONE_FONT_SCALE)
		{
			DeleteObject(m_PhoneticFont);
			m_PhoneticFont	= 0;
			fCreateFont		= true;
			
		}
	}
	if(fCreateFont)
	{
		m_PhoneticFontTm;
		LOGFONT		lFont,syslfont;
		GetObject(getFont(0), sizeof(lFont), &lFont);
		HFONT syshfont = (HFONT) GetStockObject(SYSTEM_FONT);
		GetObject(syshfont, sizeof(syslfont), &syslfont);
		m_PhoneticFont = CreateFont(-(m_maxDescent + m_maxAscent) * PHONE_FONT_SCALE, 
									0, 0, 0, FW_THIN, 0, 0, 0, 0, 0, 0, lFont.lfQuality, 0, 
									syslfont.lfFaceName);
		HDC hdc		= GetDC(NULL);
		HFONT old	= (HFONT)SelectObject(hdc, m_PhoneticFont);
		GetTextMetrics(hdc, &m_PhoneticFontTm);
		m_PhoneticFontInternalLeading = m_PhoneticFontTm.tmInternalLeading;
		m_PhoneticFontHeight = m_PhoneticFontTm.tmHeight;
		SelectObject(hdc, old);
		OutputDebugString(L"Phonetic Font is updated\n");
		ReleaseDC(NULL, hdc);
	}

}
HFONT MNFontManager::getPhoneticFont()
{
	if(m_PhoneticFont == 0)
		UpdatePhoneticFont();
	return m_PhoneticFont;
}
int MNFontManager::getPhoneticFontHeight()
{
	return m_PhoneticFontHeight;
}

int	MNFontManager::getPhoneticFontInternalLeading()
{
	return m_PhoneticFontInternalLeading;
}
float MNFontManager::getPhoneticOffset()
{
	return m_PhoneticOffset;
}
void MNFontManager::UpdatePhoneticOffset()
{
	int lineheight = m_maxDescent + m_maxAscent + m_maxExternalLeading;
	if(0 < m_PhoneticSpace && m_PhoneticSpace < 1)
		m_PhoneticOffset = lineheight * m_PhoneticSpace ;
	else if(m_PhoneticSpace >=1)
		m_PhoneticOffset = lineheight + m_PhoneticSpace ;
	else 
		m_PhoneticOffset = 0;
	if( !m_fTesterViewMode)
		m_PhoneticOffset = 0;
}