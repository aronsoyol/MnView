#pragma once
#include <windows.h>
#include <usp10.h>
//#pragma comment(lib, "usp10.lib")
#include "MNCharAttr.h"
#include "MNText.h"

class MNFont
{
	friend class MNFontManager;
public:
	static int s_count;
public:
	
	SCRIPT_CACHE	m_cache;
	HFONT			m_hFont;
	TEXTMETRIC		tm;
private:
	

	LONG				m_size  ; //pixel
	LONG				m_bold  ;
	BYTE			m_italic ;
	BYTE			m_underLine;
	LONG			m_rotate;
	MNText			m_fontName;
	

public:
	MNFont(void);
	MNFont(const MNFont&);
	//MNFont(const MNText& name, UINT size = 20, bool bold = false, bool italic = false, bool underLine = false, bool rotate = false);
	MNFont(const WCHAR*  name, UINT size = 20, bool bold = false, bool italic = false, bool underLine = false, bool rotate = false);

	virtual ~MNFont(void);
	
	void	freeResourse();
	bool	createFont();
	bool	like(const MNText& name, UINT size = 20, LONG bold = FW_DONTCARE, bool italic = false, bool underLine = false, bool rotate = false);
	void	init(const MNText& name, UINT size = 20, LONG bold = FW_DONTCARE, bool italic = false, bool underLine = false, bool rotate = false);
	void	init(HFONT hFont);
	bool	calcMetrics(HDC hdc);
	bool	operator == (const MNFont&);
	bool	operator != (const MNFont&);
	MNFont&	operator  = (const MNFont&);

	HFONT getHFont();
	//SCRIPT_CACHE* getCache();
};
