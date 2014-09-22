#include "MnTextView.h"	
#include <time.h>
void MnTextView::OnDrawV(HDC* pDC, RECT& updateRect)
{

	int		x,y,v ;
	int		h	= getLineHeight();
	if(updateRect.left > 0)
	{
		int stop = 1;
	}

	wchar_t debug [50];
	

	//OutputDebugString(L"start");
	RECT cliRect;//, zeroRect = {0,0,0,0};
	GetClientRect(this->m_hWnd, &cliRect);

	int left		= max(m_MarginLeft,	updateRect.left	)	- m_MarginLeft;
	int right		= min(cliRect.right- m_MarginRight,	updateRect.right)	- m_MarginLeft;
	if(right < 0) return;

	LINE_INDEX idx		= m_visualLineView.getLineIndex(m_nScrollPos + left / h);
	LINE_INDEX endIdx	= m_visualLineView.getEnd();
	LINE_INDEX nextIdx;

	int		height	= cliRect.right	- cliRect.left	- getMarginLR();
	int		width	= cliRect.bottom- cliRect.top	- getMarginTB();
	HDC		hDc		= *pDC;//pDC->GetSafeHdc();
	HDC		memHdc	= CreateCompatibleDC(hDc);
	HBITMAP	memBmp	= CreateCompatibleBitmap(hDc, cliRect.bottom - cliRect.top, h);
	HBRUSH	bgBrush = CreateSolidBrush(m_colBack);

	SelectObject(memHdc , memBmp );
	SelectObject(memHdc , bgBrush);
	//RGB
	SetBkMode(memHdc,OPAQUE);
	SetBkColor(memHdc, this->m_colBack);
	//CRgn rgn;
	//GetUpdateRgn(&rgn);


	//SetBkMode(memHdc,TRANSPARENT);
	if(m_visualLineView.getLogLineCount() > 0)
	{
		
		//int count = min((int)(height / h) + 1, m_visualLineView.getVisLineCount());
		int 
		count	= (int )ceil((float)right / h) - left / h;
		x		= m_MarginLeft + (idx.visLine - m_nScrollPos) * h; 
		wsprintf(debug, L"update rect l:%d r:%d t:%d b:%d count:%d\n",updateRect.left, updateRect.right ,updateRect.top, updateRect.bottom, count);
		OutputDebugString(debug);
		
		for(UINT i = 0; i < count; i++)
		{
			//if(getMarginTB() + i * h  >= cliRect.bottom) break;
			RECT memRect = {0,0,cliRect.bottom - cliRect.top, h};
			FillRect(memHdc,&memRect,bgBrush);
			if(idx < endIdx)
			{
				if(idx.logLine == 0 && idx.subLine == 1)
				{
					int stop =1;
				}
				nextIdx = m_visualLineView.drawVisLine(memHdc, idx, m_MarginTop, 0);
				try
				{
					if(idx == nextIdx)
					{
						int stop = 1;
					}
					idx		= nextIdx;
				}
				catch(...)
				{
					int haha =0;
				}
			}
			else
			{
				//FillRect(memHdc,&memRect,bgBrush);
			}
			//printf("v:%d,l:%d,s:%d\n",idx.visLine,idx.logLine,idx.subLine);
			

			POINT point[3];
			point[0].x = x + h;
			point[0].y = cliRect.top;

			point[1].x = point[0].x;
			point[1].y = cliRect.bottom - cliRect.top;

			point[2].x = x;
			point[2].y = point[0].y;
			
			PlgBlt(hDc,point,memHdc,0,0, cliRect.bottom - cliRect.top,h,NULL,0,0);
			x		+= h;
		}
		//printf("%d\n",m_visualLineView.getSubLineCount(0));
	}



	DeleteObject(bgBrush);
	DeleteObject(memBmp);
	DeleteDC(memHdc);
	//OutputDebugString(L"-end*\n");
}
void MnTextView::drawBorder(HDC* pDC, RECT& updateRect)
{
	RECT cliRect;
	GetClientRect(m_hWnd,&cliRect);
	HBRUSH brush = CreateSolidBrush(m_colBack);	
}
void MnTextView::drawMarginLeft(HDC* pDC)
{
	//getclient
}
void MnTextView::drawMarginTop(HDC* pDC){}
void MnTextView::drawMarginRight(HDC* pDC){}
void MnTextView::drawMarginBottom(HDC* pDC){}
/*
void MnTextView::OnDrawH(HDC* pDC)
{
	//if(m_lineManager.getLogLineCount()<= 0 )return;

	CtextViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	
	
	


	
	int		x,y,v ;
	int		h	= getLineHeight();
	

	
	//
	////Rectangle(memHdc,0,0,r.bottom-r.top, r.right-r.left);
	
	//SetBkMode(memHdc,TRANSPARENT);
	HDC		hDc	= pDC->GetSafeHdc();

	CRect updataRect, cliRect;//, zeroRect = {0,0,0,0};


	LINE_INDEX idx = m_offset;

	GetClientRect(&cliRect);

	CRgn rgn;
	GetUpdateRgn(&rgn);



	
	SetBkMode(hDc,TRANSPARENT);
	if(m_visualLineView.getLogLineCount() > 0)
	{
		
		int count = min((int)((cliRect.bottom - getMarginTB())/h) + 1, m_visualLineView.getVisLineCount());

		if(GetUpdateRect(&updataRect))
		{
			v		= (updataRect.top - getMarginTop()) / h + m_offset.visLine; 
			idx		= m_visualLineView.getLineIndex(v);
			count	= (int)ceil((float)updataRect.Height() / h );
			x		= (idx.visLine - m_offset.visLine) * h;

			printf("draw %d,%d\n",idx.visLine,count);
		}
		else
		{
			idx		= m_offset;
			count	= (int)ceil((float)(cliRect.Height() - getMarginTB()) / h );
			x		= m_MarginTop; 
		}
		count		= min(count, m_visualLineView.getVisLineCount() - idx.visLine);
		for(UINT i = 0; i < count; i++)
		{
			//if(getMarginTB() + i * h  >= cliRect.bottom) break;
			m_visualLineView.drawVisLine(hDc, idx, m_MarginLeft, x);
			
			//printf("v:%d,l:%d,s:%d\n",idx.visLine,idx.logLine,idx.subLine);
			x		+= h;
			idx		= m_visualLineView.next(idx);

			if(m_visualLineView.getSubLineCount(idx.logLine)==idx.subLine)
			{
				int error =1;
				break;
			}
			
			
		}
		printf("%d\n",m_visualLineView.getSubLineCount(0));
	}

}
*/
inline int MnTextView::getMarginLR()
{
	return m_MarginLeft + m_MarginRight;
}
inline int MnTextView::getMarginTB()
{
	return m_MarginTop + m_MarginBottom;
}
int MnTextView::getLineHeight()
{
	return m_visualLineView.getLineHeight();
}
int MnTextView::getMarginLeft()
{
	return m_MarginLeft;
}
int MnTextView::getMarginRight()
{
	return m_MarginRight;
}
int MnTextView::getMarginBottom()
{
	return m_MarginBottom;
}
int MnTextView::getMarginTop()
{
	return m_MarginTop;
}
void MnTextView::setMargin(int MarginALLSides)
{
	m_MarginBottom = MarginALLSides;
	m_MarginTop	= MarginALLSides;
	m_MarginRight	= MarginALLSides;
	m_MarginLeft	= MarginALLSides;
}
void MnTextView::setMarginLeft(int MarginLeft)
{
	m_MarginLeft	= MarginLeft;
}
void MnTextView::setMarginRight(int MarginRight)
{
	m_MarginRight	= MarginRight;
}
void MnTextView::setMarginBottom(int MarginBottom)
{
	m_MarginBottom = MarginBottom;
}
void MnTextView::setMarginTop(int MarginTop)
{
	m_MarginTop	= MarginTop;
}

VOID MnTextView::UpdateMetrics()
{
	RECT rect;
	GetClientRect(m_hWnd, &rect);

	OnSize(0, rect.right, rect.bottom);
	RefreshWindow();

}

int MnTextView::breakLines(int width,int height)
{
	if(m_visualLineView.getLogLineCount() == 0) 
		return 0;
	//m_visLineCount	= 0;
	if(width == 0 && height == 0)
	{
		
		RECT rect;
		GetClientRect(this->m_hWnd, &rect);
		width	= (rect.right	- rect.left)- getMarginLR();
		height	= (rect.bottom	- rect.top)	- getMarginTB();
	}
	int lineWidth		= 0 ; 
	int windowHeight	= 0;
	if(m_direction == WD_HORIZONTAL)
	{
		lineWidth = width;
		windowHeight = height;
	}
	else
	{
		lineWidth	= height;
		windowHeight = width;
	}
	return m_visualLineView.setWidth(lineWidth);
}
BOOL MnTextView::CreateMyCaret(void)
{
	int h				= 20;
	/*
	HDC windowDC		= GetDC(0);
	HDC dc				= GetDC(m_hWnd);
	HDC memDc			= CreateCompatibleDC(dc);
	HBITMAP bmpCaret	= CreateCompatibleBitmap(dc, 10 ,20);

	HBRUSH redBrush		= CreateSolidBrush(RGB(255,0,0));

	SelectObject(memDc, bmpCaret);
	SelectObject(memDc, redBrush);

	Rectangle(memDc, 0, 0, 20, 20);
	//FillRect(hdc ,&rect, redBrush);
*/
	if(m_visualLineView.getLogLineCount() > 0)
	{
		h = getLineHeight();
	}
	if(m_direction == WD_HORIZONTAL)
	{
		CreateCaret(m_hWnd, (HBITMAP)NULL, DFAULT_CARET_WIDTH, h);
	}
	else if(m_direction == WD_VERTICAL)
	{
		CreateCaret(m_hWnd, (HBITMAP)NULL, h, DFAULT_CARET_WIDTH);
	}
	return TRUE;
}

void MnTextView::updateCaretPos(const CHAR_POS& charPos, bool autoScrollToViewPort)
{
	POINT point;
	//m_lineManager.getLocation(charPos,&point);
	//charPos->print();
	m_visualLineView.getLocation(&charPos,&point);
	convertOut(&point);
	SetCaretPos(point.x,point.y);
	NotifyParent(TVN_CURSOR_CHANGE);
	OutputDebugString(L"updateCaretPos\n");
	ImeSetCandWindowPos();
	ImeSetCompWindowPos();
    
}
void MnTextView::updateCaretPos(const POINT &point)
{
	SetCaretPos(point.x,point.y);
	OutputDebugString(L"updateCaretPos\n");
	ImeSetCandWindowPos();
	ImeSetCompWindowPos();
}
BOOL MnTextView::getVisLineRect(int vline,RECT* pRect)
{
	if(vline < 0 || vline >= m_visualLineView.getVisLineCount()) 
		return FALSE;
	int lh = getLineHeight();
	GetClientRect(m_hWnd,pRect);
	if(m_direction == WD_HORIZONTAL)
	{
		pRect->left		= m_MarginLeft;
		pRect->right   -= m_MarginRight;
		pRect->top		= m_MarginTop + vline * lh;
		pRect->bottom	= pRect->top + lh;
	}
	else if(m_direction == WD_VERTICAL)
	{
		pRect->left		 = m_MarginLeft + vline * lh;
		pRect->right	 = pRect->left + lh;
		pRect->top		 = m_MarginTop ;
		pRect->bottom	-= m_MarginBottom;
	}
	return TRUE;
}
BOOL MnTextView::convertIn(POINT* point)
{
	//text view coordinate to vitual visal line cordinate
	//if(m_direction == WD_HORIZONTAL)
	//{
	RECT clientRect;
	GetClientRect(m_hWnd,&clientRect);
	//CPoint newOoint = *oldPoint;
	//CPoint *point = &newOoint;

	if(m_direction == WD_HORIZONTAL)
	{
		int maxX = clientRect.right - m_MarginRight;
		int minX = m_MarginLeft;

		if(point->x < minX)
		{
			point->x = minX;
		}else if(point->x > maxX)
		{
			point->y = maxX;
		}
		point->x -= m_MarginLeft;//(m_offset.visLine * m_visualLineView.getLineHeight() - m_MarginLeft);
		point->y += (m_nScrollPos * m_visualLineView.getLineHeight() - m_MarginTop);
	}

	//}
	if(m_direction == WD_VERTICAL)
	{
		int maxY = clientRect.bottom - clientRect.top - m_MarginBottom;
		int minY = m_MarginTop;
		if(point->y < minY)
		{
			point->y = minY;
		}else if(point->y > maxY)
		{
			point->y = maxY;
		}
		point->x += (m_nScrollPos * m_visualLineView.getLineHeight() - m_MarginLeft);
		point->y -= m_MarginTop;

		int  tmp = point->x;
		point->x = point->y;
		point->y = tmp;
	}
	if(point->x<0||point->y<0)
	{
		int stop =1;
	}
	return TRUE;
}

BOOL MnTextView::convertOut(POINT* point)
{
	//text view coordinate to vitual visal line cordinate
	int h = getLineHeight();
	if(m_direction == WD_VERTICAL)
	{
		int  tmp = point->x;
		point->x = point->y - h * m_nScrollPos;
		point->y = tmp;
	}
	else
	{
		point->y = point->y - h * m_nScrollPos;
	}
	point->x += m_MarginLeft;
	point->y += m_MarginTop ;
	return TRUE;
}
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
LONG MnTextView::Find_Text(const WCHAR *pFindText, ULONG length, BOOL bBack , BOOL bMatchCase, BOOL bWrap , BOOL bSelFound)
{
	LONG start			= max(m_nSelectionStart, m_nSelectionEnd);
	//start				= max(start,m_nCursorOffset);
	ULONG found_offset	= -1;

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
	if(m_pTextDoc->find(start, pFindText, length, &found_offset))
	{
		LONG old_selstart	= min(m_nSelectionStart, m_nSelectionEnd);
		LONG old_selend		= max(m_nSelectionStart, m_nSelectionEnd);
		if(bSelFound)
		{
			m_nSelectionStart	= found_offset;
			m_nSelectionEnd		= found_offset + m_pFndIterator->find_text_length();
			//m_nCursorOffset		= m_nSelectionEnd;
			FilePosToCharPos(m_nSelectionEnd, &m_CurrentCharPos);

			updateCaretPos(m_CurrentCharPos);
			InvalidateRange(m_nSelectionStart, m_nSelectionEnd);

			ScrollToCaret();
		
			if(old_selstart != old_selend)
				InvalidateRange(old_selstart, old_selend);
		}
		return found_offset;
		//m_pTextDoc->replace_text(found_offset, pInsertText, insert_length, erase_length);
	}
	return -1;
}
LONG MnTextView::FindForward2(BOOL bMatchcase, const WCHAR *pFind_text, BOOL bReplaceAll)
{
	LONG start			= min(m_nSelectionStart, m_nSelectionEnd);
	//start				= min(start,m_nCursorOffset);
	ULONG found_offset	= -1;
	//WCHAR *pFind_text	= m_pFndIterator->find_text();
	//ULONG erase_length	= m_pFndIterator->find_text_length();
	ULONG find_length	= lstrlen(pFind_text);
	if (m_pTextDoc->find(m_nSelectionEnd, pFind_text, find_length, &found_offset))
	{
		return found_offset;
		//m_pTextDoc->replace_text(found_offset, pInsertText, insert_length, erase_length);
	}
	return -1;
	
}
LONG MnTextView::ReplaceALLForward (BOOL bMatchCase, const WCHAR *pReplaceText)
{
	LONG offset_find	= -1;
	LONG count			= 0;
	LONG start			= min(m_nSelectionStart, m_nSelectionEnd);
	//start				= min(start,m_nCursorOffset);
	LONG erase_length	= m_pFndIterator->find_text_length();
	LONG insert_length	= lstrlen(pReplaceText);

	while((offset_find = m_pFndIterator->find_forward2(start, bMatchCase)) >= 0)
	{
		if(m_pTextDoc->replace_text(offset_find, pReplaceText, insert_length, erase_length))
		{
			count ++;
			start += insert_length;
		}
		else
			break;
	}
	if(count > 0)
	{
		Smeg(0);
	}
	return count;
}
LONG MnTextView::ReplaceALLBackward(BOOL bMatchCase, const WCHAR *pReplaceText)
{
	LONG offset_find	= -1;
	LONG count			= 0;
	LONG start			= max(m_nSelectionStart, m_nSelectionEnd);
	//start				= max(start,m_nCursorOffset);
	LONG erase_length	= m_pFndIterator->find_text_length();
	LONG insert_length	= lstrlen(pReplaceText);

	while((offset_find = m_pFndIterator->find_backward2(start, bMatchCase)) >= 0)
	{
		if(m_pTextDoc->replace_text(offset_find, pReplaceText, insert_length, erase_length))
		{
			count ++;
			start = offset_find;
		}
		else
			break;
	}
	if(count > 0)
	{
		Smeg(0);
	}
	return count;
}
LONG MnTextView::FindForward(BOOL bMatchCase, const WCHAR *pReplaceText, BOOL bReplaceAll)
{
	//ReplaceALLForward(bMatchCase, pReplaceText);
	if(bReplaceAll)
		return ReplaceALLForward(bMatchCase, pReplaceText);
	
	LONG old_selstart	= min(m_nSelectionStart, m_nSelectionEnd);
	LONG old_selend		= max(m_nSelectionStart, m_nSelectionEnd);
	LONG found_offset;

	if(pReplaceText && old_selend - old_selstart == m_pFndIterator->find_text_length())
	{
		found_offset	= m_pFndIterator->find_forward2(old_selstart, bMatchCase);
		if(found_offset == old_selstart)
		{
			EnterText(pReplaceText, lstrlen(pReplaceText));
		}
	}
	ULONG found = -1;
	if (m_pTextDoc->find(m_nSelectionEnd, L"abc", 3, &found))
	{
		int stop =1;
	}
	found_offset = m_pFndIterator->find_forward2(m_nSelectionEnd, bMatchCase);

	if(found_offset >= 0)
	{
		m_nSelectionStart	= found_offset;
		m_nSelectionEnd		= found_offset + m_pFndIterator->find_text_length();
		//m_nCursorOffset		= m_nSelectionEnd;
		FilePosToCharPos(m_nSelectionEnd, &m_CurrentCharPos);

		updateCaretPos(m_CurrentCharPos);
		InvalidateRange(m_nSelectionStart, m_nSelectionEnd);

		ScrollToCaret();
	}
	if(old_selstart != old_selend)
		InvalidateRange(old_selstart, old_selend);
	return found_offset;
}

LONG MnTextView::FindBackward(BOOL bMatchCase, const WCHAR *pReplaceText, BOOL bReplaceAll)
{
	if(bReplaceAll)
		return ReplaceALLBackward(bMatchCase, pReplaceText);

	LONG old_selstart	= min(m_nSelectionStart, m_nSelectionEnd);
	LONG old_selend		= max(m_nSelectionStart, m_nSelectionEnd);
	LONG start_offset	= old_selstart;

	LONG found_offset;

	if(pReplaceText && old_selend - old_selstart == m_pFndIterator->find_text_length())
	{
		found_offset	= m_pFndIterator->find_backward2(old_selend, bMatchCase);
		if(found_offset == old_selstart)
			EnterText(pReplaceText, lstrlen(pReplaceText));
	}

	found_offset	= m_pFndIterator->find_backward2(start_offset, bMatchCase);

	if(found_offset >= 0)
	{
		m_nSelectionStart	= found_offset;
		m_nSelectionEnd		= found_offset + m_pFndIterator->find_text_length();
		//m_nCursorOffset		= m_nSelectionEnd;
		FilePosToCharPos(m_nSelectionEnd, &m_CurrentCharPos);

		updateCaretPos(m_CurrentCharPos);
		InvalidateRange(m_nSelectionStart, m_nSelectionEnd);

		ScrollToCaret();
	}
	if(old_selstart != old_selend)
		InvalidateRange(old_selstart, old_selend);
	return found_offset;
}