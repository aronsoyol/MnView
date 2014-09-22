#pragma once
#include "MnTextView.h"
class MnTextBoxApi :
	public MnTextView
{
public:
	MnTextBoxApi(HWND hwnd);
	virtual ~MnTextBoxApi();
public:
	
	virtual ULONG		ApiGetText(wchar_t *szBuffer, ULONG nStartOffset, ULONG nLength);
	virtual ULONG		ApiSetText(wchar_t *szBuffer, ULONG nStartOffset, ULONG nLength);
	virtual	ULONG		ApiGetTextLength();
	virtual	void		ApiSetForeColor(COLORREF col);
	virtual COLORREF	ApiGetForeColor(void);
	virtual	void		ApiSetBackColor(COLORREF col);
	virtual COLORREF	ApiGetBackColor(void);
	virtual LONG		ApiGetSelLength();
	virtual void		ApiSetSellength(long len);
	virtual ULONG		ApiGetSelStart();
	virtual ULONG		ApiGetSelection();
	virtual ULONG		ApiSetSelection(ULONG start, ULONG length);
	virtual ULONG		ApiGetParagraphLength(ULONG paragraph);
	virtual ULONG ApiSetFont(HFONT font);
	virtual ULONG ApiGetFontFace(wchar_t * szFace);
	virtual ULONG ApiSetFontFace(const wchar_t * szFace);
	virtual ULONG ApiSetFontSize(int size_in_pixel);
	virtual bool ApiCanRedo();
	virtual bool ApiRedo();
	virtual bool ApiCanUndo();
	virtual bool ApiUndo();
	/*virtual ULONG ApiHandleWndMsg(UINT msg, WPARAM wParam, LPARAM lParam, HRESULT* pResult = 0);*/

};

