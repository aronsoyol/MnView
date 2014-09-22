#include "MnTextBoxApi.h"


MnTextBoxApi::MnTextBoxApi(HWND hWnd) :
MnTextView(hWnd)
{

}


MnTextBoxApi::~MnTextBoxApi()
{
}
//
//	Retrieve the specified range of text and copy it to supplied buffer
//	szDest must be big enough to hold nLength characters
//	nLength includes the terminating NULL
//
ULONG MnTextBoxApi::ApiGetText(wchar_t *szDest, ULONG nStartOffset, ULONG nLength)
{
	ULONG copied = 0;

	if (nLength > 1)
	{
		TextIterator itor = m_pTextDoc->iterate(nStartOffset);
		copied = itor.gettext(szDest, nLength - 1);

		// null-terminate
		szDest[copied] = 0;
	}

	return copied;
}
ULONG MnTextBoxApi::ApiSetText(wchar_t *szBuffer, ULONG nStartOffset, ULONG nLength){ return 0; }
ULONG MnTextBoxApi::ApiGetTextLength(){ return 0; }
void  MnTextBoxApi::ApiSetForeColor(COLORREF col)
{
	int r = GetRValue(col);
	int g = GetGValue(col);
	int b = GetBValue(col);

	this->m_colFore = col;
	InvalidateRect(m_hWnd, NULL, TRUE);
	/*return 0; */
}
COLORREF MnTextBoxApi::ApiGetForeColor(void){ return m_colFore; }
void  MnTextBoxApi::ApiSetBackColor(COLORREF col)
{ 
	int r = GetRValue(col);
	int g = GetGValue(col);
	int b = GetBValue(col);

	this->m_colBack = col; 
	InvalidateRect(m_hWnd, NULL, TRUE);
}
COLORREF	MnTextBoxApi::ApiGetBackColor(void){ return m_colBack; }
LONG	MnTextBoxApi::ApiGetSelLength(){ return m_nSelectionEnd - m_nSelectionStart; }
void	MnTextBoxApi::ApiSetSellength(long len)
{
	m_nSelectionEnd = m_nSelectionStart + len;
	//SendMessage(m_hWnd, EM_SETSEL, (WPARAM) 
	OnMsg_EM_SETSEL(m_nSelectionStart, m_nSelectionEnd);
}
ULONG MnTextBoxApi::ApiGetSelStart(){ return 0; }
ULONG MnTextBoxApi::ApiGetSelection(){ return 0; }
ULONG MnTextBoxApi::ApiSetSelection(ULONG start, ULONG length){ return 0; }
ULONG MnTextBoxApi::ApiGetParagraphLength(ULONG paragraph){ return 0; }
ULONG MnTextBoxApi::ApiSetFont(HFONT font){ return 0; }
ULONG MnTextBoxApi::ApiGetFontFace(wchar_t * szFace){ return 0; }
ULONG MnTextBoxApi::ApiSetFontFace(const wchar_t * szFace){ return 0; }
ULONG MnTextBoxApi::ApiSetFontSize(int size_in_pixel){ return 0; }
bool MnTextBoxApi::ApiCanRedo(){ return (bool)this->CanRedo(); }
bool MnTextBoxApi::ApiRedo(){ return (bool)this->Redo(); }
bool MnTextBoxApi::ApiCanUndo(){ return 0; }
bool MnTextBoxApi::ApiUndo(){ return 0; }