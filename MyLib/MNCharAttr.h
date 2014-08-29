#pragma once
#include "stdafx.h"
class MNCharAttr
{

public:
	COLORREF	bgColor		;
	COLORREF	fgColor		;
	UINT		fontIndex	;
	UINT 		size		;
	bool		selcted		;
	bool		bold		;
	bool		italic		;
	bool		underLine   ;
	bool		isMonCtrlChar;

	MNCharAttr(void);
	MNCharAttr(const MNCharAttr&);
	~MNCharAttr(void);
	bool operator == (const MNCharAttr&);
	bool operator != (const MNCharAttr&);
};
