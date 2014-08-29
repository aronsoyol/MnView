#pragma once
#include	<vector>
#include	"FontNameList.h"
#include	"glyfdata.h"
#include	"MNFont.h"
#include	"MNText.h"
#define		MAX_FONTLIST_LENGTH	32
class MNFontManager
{
	friend class GlyfData;
private:
	vector<MNFont>	m_fontList;
	HFONT			m_PhoneticFont;
	int				m_count;
	int				m_maxDescent;
	int				m_maxAscent;
	int				m_maxInternalLeading;
	int				m_maxExternalLeading;
	int				m_PhoneticFontInternalLeading;
	float			m_PhoneticSpace;
	float			m_PhoneticOffset;
	bool			m_fTesterViewMode;
	int				m_PhoneticFontHeight;
	int				m_PhoneticFontAvgCharWidth;
	TEXTMETRIC		m_PhoneticFontTm;
protected:
	int				queryFont(const MNText& fontName, UINT size, BOOL bBold, BOOL bItalic, BOOL bUline, BOOL rotate);
	int				addFont(const MNText& fontName, UINT size, BOOL bBold, BOOL bItalic, BOOL bUline, BOOL rotate);
	void			updateMetrics();
	void			UpdatePhoneticFont();
	void			UpdatePhoneticOffset();
public:
	MNFontManager(void);
	virtual			~MNFontManager(void);
	//void			setPrimaryFont(const MNText& fontName, UINT size, BOOL bBold, BOOL bItalic, BOOL bUline);
	void			setPrimaryFont(HFONT hFont);
	int				getFontIndex(const MNText& fontName, UINT size, BOOL bBold, BOOL bItalic, BOOL bUline, BOOL rotate = FALSE);
	UINT			getLineHeight();
	UINT			calcLineHeight(HDC hdc);
	HFONT			getFont(int index);
	HFONT			getPhoneticFont();
	int				getPhoneticFontHeight();
	int				getPhoneticFontInternalLeading();
	//void 			getPhoneticFontTm()
	//{
	//	return m_PhoneticFontTm;
	//}
	float			getPhoneticOffset();
	bool			isTesterMode(){
		return m_fTesterViewMode;
	}
	void			setTesterMode(bool mode)
	{
		m_fTesterViewMode = mode;
		UpdatePhoneticFont();
		UpdatePhoneticOffset();
	}
};
