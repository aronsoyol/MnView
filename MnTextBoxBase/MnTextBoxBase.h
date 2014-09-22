#pragma once
#include "../TextView/MnTextView.h"
class MnTextBoxBase :
	public MnTextView
{
public:
	MnTextBoxBase(HWND hwnd);
	virtual ~MnTextBoxBase();
public:
	virtual	ULONG ApiGetTextLength();
	virtual ULONG ApiGetText(wchar_t *szBuffer, ULONG nStartOffset, ULONG nLength);
	virtual ULONG ApiSetText(wchar_t *szBuffer, ULONG nStartOffset, ULONG nLength);
	virtual	ULONG ApiSetForeColor(COLORREF col);
	virtual ULONG ApiGetForeColor(COLORREF *pCol = 0);
	virtual	ULONG ApiSetBackColor(COLORREF col);
	virtual ULONG ApiGetBackColor(COLORREF *pCol = 0);
	virtual ULONG ApiGetSelLength();
	virtual ULONG ApiGetSelStart();
	virtual ULONG ApiGetSelection();
	virtual ULONG ApiSetSelection(ULONG start, ULONG length);
	virtual ULONG ApiGetParagraphLength(ULONG paragraph);
	virtual ULONG ApiSetFont(HFONT font);
	virtual ULONG ApiGetFontFace(wchar_t * szFace);
	virtual ULONG ApiSetFontFace(const wchar_t * szFace);
	virtual ULONG ApiSetFontSize(int size_in_pixel);

};

