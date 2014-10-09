#include "MnTextView.h"
void MnTextView::FindInitial(const WCHAR *find_text)
{
	m_pFndIterator->find_init(find_text);
}
//LONG MnTextView::FindForward(const WCHAR *find_text, BOOL bMatchCase, BOOL bReplace)
//{
//	m_pFndIterator->find_init(find_text);
//	LONG found_offset	= m_pFndIterator->find_forward2(m_nCursorOffset, bMatchCase);
//	
//	LONG old_selstart	= m_nSelectionStart;
//	LONG old_selend		= m_nSelectionEnd;
//	if(found_offset >= 0)
//	{
//		m_nSelectionStart	= found_offset;
//		m_nSelectionEnd		= found_offset + m_pFndIterator->find_text_length();
//		m_nCursorOffset		= m_nSelectionEnd;
//		FilePosToCharPos(m_nCursorOffset, &m_CurrentCharPos);
//		updateCaretPos(m_CurrentCharPos);
//		InvalidateRange(m_nSelectionStart, m_nSelectionEnd);
//		
//	}
//	if(old_selstart != old_selend)
//		InvalidateRange(old_selstart, old_selend);
//	return found_offset;
//}
//LONG MnTextView::FindBackward(const WCHAR *find_text, BOOL bMatchCase, BOOL bReplace)
//{
//	m_pFndIterator->find_init(find_text);
//	LONG old_selstart	= m_nSelectionStart;
//	LONG old_selend		= m_nSelectionEnd;
//	LONG start_offset	= min(old_selstart, old_selend) - 1;
//	LONG found_offset	= m_pFndIterator->find_backward2(start_offset, bMatchCase);
//	
//
//	if(found_offset >= 0)
//	{
//		m_nSelectionStart	= found_offset;
//		m_nSelectionEnd		= found_offset + m_pFndIterator->find_text_length();
//		m_nCursorOffset		= m_nSelectionEnd;
//		FilePosToCharPos(m_nCursorOffset, &m_CurrentCharPos);
//		updateCaretPos(m_CurrentCharPos);
//		InvalidateRange(m_nSelectionStart, m_nSelectionEnd);
//		
//	}
//	if(old_selstart != old_selend)
//		InvalidateRange(old_selstart, old_selend);
//	return found_offset;
//}
LONG MnTextView::Replace_Text(const REPLACE_OPTION *pOption)
{
	m_pTextDoc->replace_text(pOption->fop.text, lstrlen(pOption->fop.text), pOption->text, lstrlen(pOption->text));
	Smeg(0);
	return 0;
}
LONG MnTextView::Find_Text(const WCHAR *pFindText, ULONG length, BOOL bBack, BOOL bMatchCase, BOOL bWrap, BOOL bSelFound)
{
	LONG start = max(m_nSelectionStart, m_nSelectionEnd);
	//start				= max(start,m_nCursorOffset);
	ULONG found_offset = -1;

	//{
	//	clock_t st = clock();
	//	long f= 0;
	//	while(m_pTextDoc->find(f, pFindText, length, &found_offset))
	//	{
	//		f = found_offset + 1;
	//	}
	//	clock_t en = clock();

	//	double time = (double)(en-st)/CLOCKS_PER_SEC;
	//}
	if (m_pTextDoc->find(start, pFindText, length, &found_offset))
	{
		LONG old_selstart = min(m_nSelectionStart, m_nSelectionEnd);
		LONG old_selend = max(m_nSelectionStart, m_nSelectionEnd);
		if (bSelFound)
		{
			m_nSelectionStart = found_offset;
			m_nSelectionEnd = found_offset + m_pFndIterator->find_text_length();
			//m_nCursorOffset		= m_nSelectionEnd;
			FilePosToCharPos(m_nSelectionEnd, &m_CurrentCharPos);

			updateCaretPos(m_CurrentCharPos);
			InvalidateRange(m_nSelectionStart, m_nSelectionEnd);

			ScrollToCaret();

			if (old_selstart != old_selend)
				InvalidateRange(old_selstart, old_selend);
		}
		return found_offset;
		//m_pTextDoc->replace_text(found_offset, pInsertText, insert_length, erase_length);
	}
	return -1;
}
LONG MnTextView::FindForward2(BOOL bMatchcase, const WCHAR *pFind_text, BOOL bReplaceAll)
{
	LONG start = min(m_nSelectionStart, m_nSelectionEnd);
	//start				= min(start,m_nCursorOffset);
	ULONG found_offset = -1;
	//WCHAR *pFind_text	= m_pFndIterator->find_text();
	//ULONG erase_length	= m_pFndIterator->find_text_length();
	ULONG find_length = lstrlen(pFind_text);
	if (m_pTextDoc->find(m_nSelectionEnd, pFind_text, find_length, &found_offset))
	{
		return found_offset;
		//m_pTextDoc->replace_text(found_offset, pInsertText, insert_length, erase_length);
	}
	return -1;

}
LONG MnTextView::ReplaceALLForward(BOOL bMatchCase, const WCHAR *pReplaceText)
{
	LONG offset_find = -1;
	LONG count = 0;
	LONG start = min(m_nSelectionStart, m_nSelectionEnd);
	//start				= min(start,m_nCursorOffset);
	LONG erase_length = m_pFndIterator->find_text_length();
	LONG insert_length = lstrlen(pReplaceText);

	while ((offset_find = m_pFndIterator->find_forward2(start, bMatchCase)) >= 0)
	{
		if (m_pTextDoc->replace_text(offset_find, pReplaceText, insert_length, erase_length))
		{
			count++;
			start += insert_length;
		}
		else
			break;
	}
	if (count > 0)
	{
		Smeg(0);
	}
	return count;
}
LONG MnTextView::ReplaceALLBackward(BOOL bMatchCase, const WCHAR *pReplaceText)
{
	LONG offset_find = -1;
	LONG count = 0;
	LONG start = max(m_nSelectionStart, m_nSelectionEnd);
	//start				= max(start,m_nCursorOffset);
	LONG erase_length = m_pFndIterator->find_text_length();
	LONG insert_length = lstrlen(pReplaceText);

	while ((offset_find = m_pFndIterator->find_backward2(start, bMatchCase)) >= 0)
	{
		if (m_pTextDoc->replace_text(offset_find, pReplaceText, insert_length, erase_length))
		{
			count++;
			start = offset_find;
		}
		else
			break;
	}
	if (count > 0)
	{
		Smeg(0);
	}
	return count;
}
LONG MnTextView::FindForward(BOOL bMatchCase, const WCHAR *pReplaceText, BOOL bReplaceAll)
{
	//ReplaceALLForward(bMatchCase, pReplaceText);
	if (bReplaceAll)
		return ReplaceALLForward(bMatchCase, pReplaceText);

	LONG old_selstart = min(m_nSelectionStart, m_nSelectionEnd);
	LONG old_selend = max(m_nSelectionStart, m_nSelectionEnd);
	LONG found_offset;

	if (pReplaceText && old_selend - old_selstart == m_pFndIterator->find_text_length())
	{
		found_offset = m_pFndIterator->find_forward2(old_selstart, bMatchCase);
		if (found_offset == old_selstart)
		{
			EnterText(pReplaceText, lstrlen(pReplaceText));
		}
	}
	ULONG found = -1;
	if (m_pTextDoc->find(m_nSelectionEnd, L"abc", 3, &found))
	{
		int stop = 1;
	}
	found_offset = m_pFndIterator->find_forward2(m_nSelectionEnd, bMatchCase);

	if (found_offset >= 0)
	{
		m_nSelectionStart = found_offset;
		m_nSelectionEnd = found_offset + m_pFndIterator->find_text_length();
		//m_nCursorOffset		= m_nSelectionEnd;
		FilePosToCharPos(m_nSelectionEnd, &m_CurrentCharPos);

		updateCaretPos(m_CurrentCharPos);
		InvalidateRange(m_nSelectionStart, m_nSelectionEnd);

		ScrollToCaret();
	}
	if (old_selstart != old_selend)
		InvalidateRange(old_selstart, old_selend);
	return found_offset;
}

LONG MnTextView::FindBackward(BOOL bMatchCase, const WCHAR *pReplaceText, BOOL bReplaceAll)
{
	if (bReplaceAll)
		return ReplaceALLBackward(bMatchCase, pReplaceText);

	LONG old_selstart = min(m_nSelectionStart, m_nSelectionEnd);
	LONG old_selend = max(m_nSelectionStart, m_nSelectionEnd);
	LONG start_offset = old_selstart;

	LONG found_offset;

	if (pReplaceText && old_selend - old_selstart == m_pFndIterator->find_text_length())
	{
		found_offset = m_pFndIterator->find_backward2(old_selend, bMatchCase);
		if (found_offset == old_selstart)
			EnterText(pReplaceText, lstrlen(pReplaceText));
	}

	found_offset = m_pFndIterator->find_backward2(start_offset, bMatchCase);

	if (found_offset >= 0)
	{
		m_nSelectionStart = found_offset;
		m_nSelectionEnd = found_offset + m_pFndIterator->find_text_length();
		//m_nCursorOffset		= m_nSelectionEnd;
		FilePosToCharPos(m_nSelectionEnd, &m_CurrentCharPos);

		updateCaretPos(m_CurrentCharPos);
		InvalidateRange(m_nSelectionStart, m_nSelectionEnd);

		ScrollToCaret();
	}
	if (old_selstart != old_selend)
		InvalidateRange(old_selstart, old_selend);
	return found_offset;
}