#include "MnTextView.h"
LONG	MnTextView::OnMsg_EM_SETSEL(long nStart, long nEnd)
{
	if (nStart == -1)
	{
		nStart = m_nSelectionEnd;
		nEnd = nStart;
	}

	CHAR_POS cp_start;
	CHAR_POS cp_end;
	if (FilePosToCharPos(nStart, &cp_start) && FilePosToCharPos(nEnd, &cp_end))
	{
		m_visualLineView.setSelection(cp_start, cp_end);
	}
		
	InvalidateRange(m_nSelectionStart, m_nSelectionEnd);
	m_nSelectionStart = nStart;
	m_nSelectionEnd = nEnd;
	//m_nCursorOffset = nEnd;
	FilePosToCharPos(m_nSelectionEnd, &m_CurrentCharPos);
	updateCaretPos(m_CurrentCharPos);

	InvalidateRange(m_nSelectionStart, m_nSelectionEnd);
	return 0;
}
LONG	MnTextView::OnMsg_EM_GETSEL(ULONG *pStart, ULONG * pEnd)
{
	ULONG sel_start = 0, sel_end = 0;
	if (m_nSelectionStart < m_nSelectionEnd)
	{
		sel_start	= m_nSelectionStart;
		sel_end		= m_nSelectionEnd;
	}
	else
	{
		sel_start	= m_nSelectionEnd;
		sel_end		= m_nSelectionStart;
	}
	if (pStart)
		*pStart =  min(m_nSelectionStart, m_nSelectionEnd);
	if (pEnd)
		*pEnd =  max(m_nSelectionStart, m_nSelectionEnd);
	return -1;
}