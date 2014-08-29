#pragma once
#include <windows.h>
#include "MNCharAttr.h"
#include "FontNameList.h"
#include "MNText.h"
#include <vector>
class MNTextAttr
{
	std::vector<MNCharAttr>		
					m_charAttr;
	UINT			m_Length;
	CFontNameList	m_fontNameList;
public:
	MNTextAttr(void);
	MNTextAttr(UINT len);
	~MNTextAttr(void);
	MNCharAttr& operator[](UINT index);
	
	
	int			setFont(MNText& fontName, UINT charPos, UINT len);
	int			setTextSize(UINT size, UINT charPos, UINT len);
	//UINT		getTextSize(UINT charPos);

	int			setSelect(UINT charPos, UINT len);
	void		setFgColor(UINT charPos, UINT len, COLORREF& col);
	void		setBgColor(UINT charPos, UINT len, COLORREF& col);
	MNText&		getFontName(UINT index);
	COLORREF&	getFgColor(UINT charPos);
	COLORREF&	getBgColor(UINT charPos);
	bool		canBreakRun(UINT i0,UINT i1);

	void		reset();
	void		allocate(UINT len);
};
