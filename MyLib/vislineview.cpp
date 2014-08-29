#include "StdAfx.h"
#include "VisLineView.h"
#include "../textview/MnTextView.h"

bool operator==(const _LINE_INDEX& src1, const _LINE_INDEX& src2)
{
	if(src1.logLine == src2.logLine
		&&src1.subLine == src2.subLine
		&&src1.visLine == src2.visLine)
		return true;
	else
		return false;
}
bool operator!=(const _LINE_INDEX& src1, const _LINE_INDEX& src2)
{
	if(src1 == src2)
		return false;
	else
		return true;
}
bool operator >(const _LINE_INDEX& src1, const _LINE_INDEX& src2)
{
	if(src1.logLine > src2.logLine) return true;
	if(src1.logLine == src2.logLine) 
	{
		if(src1.subLine  > src2.subLine) return true;
		if(src1.subLine == src2.subLine)
		{
			if(src1.visLine > src2.visLine) return true;
		}
	}
	return false;
}
bool operator <(const _LINE_INDEX& src1, const _LINE_INDEX& src2)
{
	if(src1.logLine < src2.logLine) return true;
	if(src1.logLine == src2.logLine) 
	{
		if(src1.subLine  < src2.subLine) return true;
		if(src1.subLine == src2.subLine)
		{
			if(src1.visLine < src2.visLine) return true;
		}
	}
	return false;
}
bool operator >=(const _LINE_INDEX& src1, const _LINE_INDEX& src2)
{
	if(src1 == src2 || src1 > src2) 
		return true;
	else
		return false;
}
bool operator <=(const _LINE_INDEX& src1, const _LINE_INDEX& src2)
{
	if(src1 == src2 || src1 < src2) 
		return true;
	else
		return false;
}

//VisLineView::VisLineView(void):
//	m_hwnd			(0),
//
//	m_width			(0),
//	m_height		(0),
//
//	m_lineHeight	(0),
//	m_lineWidth		(0),
//
//	m_logLineCount	(0),
//	m_visLineCount	(0),
//	m_LogLineList	(500),
//	MAX				(500)
//{
//
//}
VisLineView::VisLineView(MnTextView* pTextView):
	m_pTextView		(pTextView),
	m_hwnd			(pTextView->m_hWnd	),
	m_pTextDoc		(pTextView->m_pTextDoc),
	m_width			(0		),
	m_height		(0		),

	m_lineHeight	(0		),
	m_lineWidth		(0		),

	m_logLineCount	(1		),
	m_visLineCount	(1		),
	m_cacheList		(CACHE_COUNT),
	m_v2s			(1	,0	),
	MAX				(500	),
	m_mruc_ID		(-1		),
	m_mruc_Line		(-1		)
{
//_CrtDumpMemoryLeaks();
}
	/*
VisLineView::VisLineView(HWND hwnd,TextDocument* pDoc):
	m_hwnd			(hwnd	),
	m_pTextDoc		(pDoc	),
	m_width			(0		),
	m_height		(0		),

	m_lineHeight	(0		),
	m_lineWidth		(0		),

	m_logLineCount	(0		),
	m_visLineCount	(0		),
	m_cacheList		(20		),
	m_v2s			(1	,1	),
	MAX				(500	)
{

}
*/
void VisLineView::initialize(UINT loglineCount)
{
	m_width			= 0;
	m_height		= 0;

	m_lineHeight	= 0;
	m_lineWidth		= 0;

	m_logLineCount	= loglineCount;
	m_visLineCount	= 0;
	//m_v2s.assign(loglineCount,1);
}
//void VisLineView::initialize(HWND hwnd, UINT loglineCount)
//{
//	m_hwnd			= hwnd;
//
//	m_width			= 0;
//	m_height		= 0;
//
//	m_lineHeight	= 0;
//	m_lineWidth		= 0;
//
//	m_logLineCount	= loglineCount;
//	m_visLineCount	= 0;
//	m_v2s.assign(loglineCount,0);
//}
//void VisLineView::initialize(HWND hwnd)
//{
//	m_hwnd			= hwnd;
//
//	m_width			= 0;
//	m_height		= 0;
//
//	m_lineHeight	= 0;
//	m_lineWidth		= 0;
//
//	m_logLineCount	= 0;
//	m_visLineCount	= 0;
//
//}
VisLineView::~VisLineView(void)
{

}
//void VisLineView::initLogLine(UINT logLineIndex, WCHAR* text,UINT length, MNTextAttr& textAttr)
//{
//	if(m_hwnd == 0 ) throw UspException();
//	m_LogLineList[logLineIndex].initialize(
//		m_hwnd,
//		text,
//		length,
//		textAttr
//	);
//	m_lineHeight	= max(m_lineHeight, m_LogLineList[logLineIndex].getLineHeight());
//	m_logLineCount	= max(m_logLineCount, logLineIndex);
//}
//void VisLineView::initLogLine(UINT logLineIndex, WCHAR* text,UINT length )
//{
//	m_LogLineList[logLineIndex].initialize(
//		m_hwnd,
//		text,
//		length
//	);
//	m_LogLineList[logLineIndex].generateGlyph();
//
//	m_logLineCount	= max(m_logLineCount, logLineIndex);
//	m_lineHeight	= max(m_lineHeight, m_LogLineList[logLineIndex].getLineHeight());
//}
//void VisLineView::initLogLine(UINT logLineIndex, UspFontManager* fontManager,WCHAR *text,int length,TextAttribute *textAttr)
//{
//	m_LogLineList[logLineIndex].initialize(
//		m_hwnd,
//		fontManager,
//		text,
//		length,
//		textAttr
//	);
//
//}
void VisLineView::setSelection(CHAR_POS& cp1, CHAR_POS& cp2)
{
	if(cp1 < cp2)
	{
		m_selStartPos	= cp1;
		m_selEndPos		= cp2;
	}
	else
	{
		m_selStartPos	= cp2;
		m_selEndPos		= cp1;
	}
	//resetCache();
}
void VisLineView::clearSelection()
{/*
	for(UINT i = 0 ; i < m_logLineCount; i++)
	{
		m_LogLineList[i].setSelect(0,0);
	}*/
}

UINT VisLineView::getWidth()
{
	return m_width;
}

int VisLineView::setWidth(UINT width)
{
	int count		= 0;
	m_width			= width ;
	//m_visLineCount	= 0;

	for(int l = 0; l < m_logLineCount; l++)
	{
		int id		= getLineCache(l);
		m_v2s[l]	= m_cacheList[id].breakLine(width);
	}
	m_visLineCount = -1;
	return 0;
}
//BOOL VisLineView::setWidth(UINT width)
//{
//	if(m_width != width)
//	{
//		m_width			= width ;
//		m_visLineCount	= 0 ;
//		int cacheCount	= m_cacheList.size();
//		int useCount	= 0 ;
//
//		for(UINT i=0; i < cacheCount; i++)
//		{
//			if(m_cacheList[i].getUsage() > 0)
//			{
//				useCount ++;
//				int line		= m_cacheList[i].getLineIndex();
//				m_v2s[line]		= m_cacheList[i].breakLine(width);
//				m_visLineCount += m_v2s[line];
//			}
//		}
//
//		m_visLineCount = 0;
//		for(UINT i=0; i < cacheCount; i++)
//		{
//			m_visLineCount	+= m_v2s[i];
//		}	
//	}
//	if(m_v2s[0]>1)
//	{
//		int stop =1;
//	}
//	return TRUE;
//}
UINT VisLineView::getHeight()
{
	return m_height;
}

UINT VisLineView::getLineHeight()
{
	return m_lineHeight;
}
void VisLineView::setLineHeight(UINT height)
{
	m_lineHeight = height;
}
UINT VisLineView::getLogLineCount()
{
	return m_logLineCount;
}
void VisLineView::setLineCount(UINT logLineCount)
{
	resetCache();
	m_logLineCount = logLineCount?logLineCount : 1;
	m_v2s.resize(m_logLineCount);
	for(int i=0;i< m_logLineCount; i++)
	{
		m_v2s[i] = 0;
	}
	m_visLineCount = -1;
}
UINT VisLineView::getSubLineCount(UINT logLineIndex)
{
	int vCount = m_v2s[logLineIndex];
	if(vCount <=0 )
	{
		int id = getLineCache(logLineIndex);
		return m_v2s[logLineIndex] = m_cacheList[id].getLineCount();
	}
	else
		return vCount;

}
UINT VisLineView::getVisLineCount()
{
	if(m_visLineCount < 0)
	{
		m_visLineCount = 0;
		for(int i = 0; i < m_logLineCount; i++)
		{
			m_visLineCount += getSubLineCount(i);/*m_v2s[i]*/;
			if(m_logLineCount > 1 && m_visLineCount == 0)
			{
				int stop =1;
			}
		}
	}
	return m_visLineCount;
}
BOOL VisLineView::getCharLoc(CHAR_POS *charPos, __out CHAR_LOC* charLoc)
{
	int cacheId = getLineCache(charPos->logLine);
	return m_cacheList[cacheId].getCharLocation(charPos,charLoc);
	//return m_LogLineList[charPos->logLine].getCharLocation(charPos,charLoc);
}
BOOL VisLineView::getCharPos(int x, int y, CHAR_POS* charPos, POINT* pPoint)
{
	if(m_pTextDoc->charCount() == 0 )
	{
		*charPos = CHAR_POS();
		if(pPoint)
		{
			pPoint->x = 0;
			pPoint->y = 0;
		}
		return TRUE;
	}
	int maxY = getVisLineCount() * m_lineHeight;
	if( y < 0) y = 0;
	if( y > maxY) y = maxY;
	int visline	= min(y / m_lineHeight, m_visLineCount - 1 ) ;
	///
	//WCHAR b[50];
	//wsprintf(b,L"v %d, ",visline);
	//OutputDebugString(b);
	///
	LINE_INDEX 
		idx		= getLineIndex(visline);

	if(idx.logLine >= m_logLineCount)
	{
		throw  MnException();
	}
	int offset	= (idx.visLine - idx.subLine) * m_lineHeight;
	
	charPos->logLine = idx.logLine;
	int id = getLineCache(idx.logLine);

	CHAR_LOC	cl;
	cl.subLine	= idx.subLine;
	cl.x		= x;

	if(m_cacheList[id].getCharPos(&cl, charPos))
	{
		if(pPoint)
		{
			pPoint->x = cl.x;
			pPoint->y = idx.visLine * m_lineHeight;
		}
		return TRUE;
	}
	return FALSE;

}
BOOL VisLineView::getLocation(__in const CHAR_POS* pCharPos, __out POINT* point)
{
	if(m_logLineCount == 0)
	{
		point->x = 0;
		point->y = 0;
		return TRUE;
	}
	int logline	= pCharPos->logLine;
	int id		= getLineCache(logline);
	CHAR_LOC	cl;
	//m_cacheList[id].getLocation(pCharPos,point);
	m_cacheList[id].getCharLocation(pCharPos,&cl);
	LINE_INDEX 
		idx		= getLineIndex(logline,0);
	point->x	= cl.x;
	point->y	= (cl.subLine + idx.visLine) * m_lineHeight;
	//int y		= cl.subLine * m_lineHeight;
	//y			+= idx.visLine * m_lineHeight;
	if(point->x == 10)
	{
		int stop =1;
	}
	WCHAR string[50];
	wsprintf(string,L"x:%d,y:%d  ",point->x,point->y);
	OutputDebugString(string);
	wsprintf(string,L"charPos  i:%d,t%d  ",pCharPos->index, pCharPos->trailing);
	OutputDebugString(string);

	return TRUE;
}
LINE_INDEX& VisLineView::next(LINE_INDEX& index)
{
	return getLineIndex(index.visLine + 1);
}
LINE_INDEX& VisLineView::last(LINE_INDEX& index)
{
	return getLineIndex(max(index.visLine - 1,0));
}
//UINT VisLineView::getVisLine(UINT logLine,UINT subLine)
//{
//	UINT visline = 0;
//	for(UINT i = 0; i < logLine; i++)
//	{
//		visline += m_LogLineList[i].getLineCount();
//	}
//	return visline + subLine;
//}

//UINT VisLineView::getLogLine(UINT visLine)
//{
//	UINT vislineCount = 0;
//	for(UINT i = 0;i< m_logLineCount; i++)
//	{
//		if(visLine < vislineCount) return i;;
//		vislineCount += m_LogLineList[i].getLineCount(); 
//	}
//	return m_logLineCount;
//}
//void VisLineView::drawVisLine(HDC hdc,UINT visLine,int x, int y)
//{
//	//get
//}
LINE_INDEX&  VisLineView::drawVisLine(HDC hdc,LINE_INDEX& idx,int x, int y)
{
	//m_LogLineList[idx.logLine].drawSubLine(&hdc, idx.subLine, x, y);
	int CID = getLineCache(idx.logLine);

	if(CID >= CACHE_COUNT || CID < 0)
	{
		throw MnException();
	}
	//cahceid = getLineCache(0);
	//if(m_selStartPos.logLine <= idx.logLine && idx.logLine <= m_selEndPos.logLine)
	//{
	//	int start,len;
	//	if(m_selStartPos.logLine < idx.logLine)
	//	{
	//		start = 0;
	//	}
	//	else
	//	{
	//		start = m_selStartPos.get();
	//	}

	//	if(m_selEndPos.logLine > idx.logLine)
	//	{
	//		len = m_cacheList[cahceid].getCharCount();
	//	}
	//	else
	//	{
	//		len = m_selEndPos.get() - start;
	//	}
	//	m_cacheList[cahceid].setSelect(start,len);
	//}
	//else
	//{
	//	m_cacheList[cahceid].setSelect(0,0);
	//}
	int start ,end,len;
	if(m_pTextView->m_nSelectionStart > m_pTextView->m_nSelectionEnd)
	{
		start	= m_pTextView->m_nSelectionEnd;
		end		= m_pTextView->m_nSelectionStart;
	}
	else
	{
		end		= m_pTextView->m_nSelectionEnd;
		start	= m_pTextView->m_nSelectionStart;
	}

	ULONG offset;
	if(m_pTextDoc->lineinfo_from_lineno(idx.logLine,&offset,NULL,NULL,NULL))
	{
		m_cacheList[CID].setSelect( start - offset, end - start );	
		m_cacheList[CID].drawSubLine(&hdc, idx.subLine, x, y);
	}

	LINE_INDEX next(idx);
	next.visLine ++;
	next.subLine ++;
	
	if(next.subLine == m_cacheList[CID].getLineCount())
	{
		next.subLine = 0;
		next.logLine ++;
	}
	return next;
}
LINE_INDEX& VisLineView::getLineIndex(const CHAR_POS& charPos)
{
	CHAR_LOC loc;
	int dLine = min(m_logLineCount - 1, max(0, charPos.logLine));
	int id = getLineCache(dLine);
	if(m_cacheList[id].getCharLocation(&charPos,&loc))
	{
		return getLineIndex(dLine, loc.subLine);
	}
}
LINE_INDEX& VisLineView::getLineIndex(UINT visLine)
{
	//IDX.visLine	= visLine;
	if(/*visLine > m_visLineCount || */visLine < 0) throw MnException();
	UINT	v	= 0,
			l	= 0,
			s	= 0,
			ns	= getSubLineCount(0);
	
	int tmp=0;
	for(int i=0 ;i< m_v2s.size();i++)
	{
		tmp += m_v2s[i];
	}
	if(tmp != m_visLineCount)
	{
		int STOP =1;
		m_visLineCount = -1;
		m_visLineCount = getVisLineCount();
	}
	while(v < visLine)//(v = 0;v <= visLine; v++,s++)
	{
		v++;
		s++;
		if(s == ns)
		{
			l ++ ;
			s	= 0 ;
			if(l == m_logLineCount)
			{
				v = 0;
				break;
			}
			ns	= getSubLineCount(l);
		}
		//vislineCount += m_LogLineList[l].getLineCount(); 
	}
	//IDX.logLine  = m_logLineCount;


	return LINE_INDEX(v,l,s);
}
LINE_INDEX& VisLineView::getLineIndex(UINT logLine,UINT subLine )
{
	LINE_INDEX IDX;
	IDX.logLine		= logLine;	
	IDX.subLine		= subLine;
	UINT visline	= 0;
	for(UINT i = 0; i < logLine; i++)
	{
		visline += getSubLineCount(i);
	}
	IDX.visLine		= visline + subLine;
	return IDX;
}
void VisLineView::resetCache()
{
	m_mruc_Line = -1;
	for(UINT i = 0; i< m_cacheList.size(); i++)
	{
		m_cacheList[i].invalidate();
	}
	for(UINT i = 0; i< m_v2s.size(); i++)
	{
		m_v2s[i] = 0;
	}
	m_visLineCount = -1;
}
void VisLineView::resetCache(int line)
{
	if(m_mruc_Line == line)m_mruc_Line = -1;
	for(UINT i = 0; i< m_cacheList.size(); i++)
	{
		if(m_cacheList[i].getLineIndex() == line)
			m_cacheList[i].invalidate();
	}
	m_v2s[line] = 0;
	m_visLineCount = -1;
}
int	VisLineView::getLineCache(UINT line)
{
	if(m_mruc_Line == line)
	{
		return m_mruc_ID;
	}
	
	int	m_rci = 0;//least-recently used replaceCandidateIndex
	for(UINT i = 0; i< m_cacheList.size(); i++)
	{
		int usage = m_cacheList[i].getUsage();
		if(	usage > 0 
		&&	m_cacheList[i].getLineIndex() == line )
		{
			m_cacheList[i].use();
			m_mruc_Line = line;
			m_mruc_ID	= i;
			return i;
		}

		if(usage < m_cacheList[m_rci].getUsage() && m_mruc_ID != i)
		{
			m_rci = i;
			
		}
	}
	ULONG	off_chars;
	ULONG	len		= m_pTextDoc->getline(line, m_buff, MAX_LINE_LENGTH, &off_chars);
	HDC		tmpDc	= GetDC(m_pTextView->m_hWnd);

	m_cacheList[m_rci].initialize(line, off_chars, m_buff, len, m_pTextView->m_pFontManager);
	m_cacheList[m_rci].generateGlyph(tmpDc, m_buff, len);

	ReleaseDC(0, tmpDc);
	int l = m_cacheList[m_rci].breakLine(m_width);
	m_cacheList[m_rci].use();

	


	if(line >= m_v2s.size())
	{
		int stop = 1;
	}
	else if(m_v2s[line] != l)
	{
		//m_visLineCount	= -1;	
		m_v2s[line]		= l ;
	}
	
	m_lineHeight	= max(m_lineHeight, getLineHeight());
	m_lineHeight	= m_lineHeight ? m_lineHeight : 20;

	m_mruc_Line		= line;
	m_mruc_ID		= m_rci;
	return m_rci;
}
LINE_INDEX& VisLineView::getEnd()
{
	return LINE_INDEX(0,m_logLineCount,0);
}
LINE_INDEX&	VisLineView::getBegin()
{
	return LINE_INDEX(0,0,0);
}

int VisLineView::getCharCount_Without_CRLF(int logline)
{
	int id = getLineCache(logline);
	return m_cacheList[id].getCharCount_WithoutCRLF();
}
BOOL VisLineView::moveToCharPrev(const CHAR_POS &cp, __out CHAR_POS *outCP, bool bStopTail)
{
	int id = getLineCache(cp.logLine);
	return m_cacheList[id].moveToCharPrev(cp,outCP,bStopTail);
}
BOOL VisLineView::moveToCharNext(const CHAR_POS &cp, __out CHAR_POS *outCP, bool bStopHead)
{
	int id = getLineCache(cp.logLine);
	return m_cacheList[id].moveToCharNext(cp,outCP, bStopHead);
}
BOOL VisLineView::moveToWordStart(const CHAR_POS &charPos, __out CHAR_POS *outCP)
{
	int cp	= charPos.get();
	int id	= getLineCache(charPos.logLine);
	int st	= m_cacheList[id].getPrevWordStop(cp);
	if(outCP)
	{
		outCP->set(charPos.logLine,st,0);
		return TRUE;
	}
	return FALSE;
}
BOOL VisLineView::moveToWordEnd  (const CHAR_POS &charPos, __out CHAR_POS *outCP)
{
	int cp	= charPos.get();
	int id	= getLineCache(charPos.logLine);
	int en	= m_cacheList[id].getNextWordStop(cp);
	if(outCP)
	{
		outCP->set(charPos.logLine,en - 1, 1);
		return TRUE;
	}
	return FALSE;
}
BOOL VisLineView::getWord(const CHAR_POS &charPos, __out CHAR_POS *pWordStart, __out CHAR_POS *pWordEnd)
{

	CHAR_POS WordStartCP ;
	CHAR_POS WordEndCP  ;

	int cp	= charPos.get();
	int id	= getLineCache(charPos.logLine);
	int st	= m_cacheList[id].getPrevWordStop(cp);
	int en	= m_cacheList[id].getNextWordStop(cp);
	if(pWordStart)
	{
		pWordStart->set(charPos.logLine, st, 0);
	}
	if(pWordEnd)
	{
		pWordEnd->set(charPos.logLine,en - 1, 1);
	}
	return TRUE;
}
BOOL VisLineView::moveToVLineNext(const CHAR_POS &cp, int nVline, __out CHAR_POS *outCP)
{
	CHAR_LOC cl;
	int maxSLine;
	int id = getLineCache(cp.logLine);
	m_cacheList[id].getCharLocation(&cp, &cl);

	LINE_INDEX lastIdx,idx = getLineIndex(cp);
	LINE_INDEX endIdx = getEnd();
	for(int i = 0; i < nVline; i++)
	{
		lastIdx = idx;
		idx		= next(idx);
		if(idx == endIdx)
		{
			idx = lastIdx;
			break;
		}
	}
	id			= getLineCache(idx.logLine);
	cl.subLine	= idx.subLine;
	outCP->logLine = idx.logLine;
	m_cacheList[id].getCharPos(&cl,outCP);
	
	return TRUE;
}
BOOL VisLineView::moveToVLinePrev(const CHAR_POS &cp, int nVline, __out CHAR_POS *outCP)
{
	CHAR_LOC cl;
	int maxSLine;
	int id = getLineCache(cp.logLine);
	m_cacheList[id].getCharLocation(&cp, &cl);

	LINE_INDEX lastIdx,idx = getLineIndex(cp);
	for(int i = 0; i < nVline; i++)
	{
		lastIdx = idx;
		idx		= last(idx);
		if(idx == getBegin())
		{
			idx = lastIdx;
			break;
		}
	}
	id			= getLineCache(idx.logLine);
	cl.subLine	= idx.subLine;
	outCP->logLine = idx.logLine;
	m_cacheList[id].getCharPos(&cl,outCP);
	
	return TRUE;
}
BOOL VisLineView::moveToLineStart(const CHAR_POS &cp, __out CHAR_POS *outCP)
{
	if(outCP == 0) return FALSE;
	int id = getLineCache(cp.logLine);
	return m_cacheList[id].getSlineStartPos(cp, outCP);
}
BOOL VisLineView::moveToLineEnd(const CHAR_POS &cp, __out CHAR_POS *outCP)
{
	if(outCP == 0) return FALSE;
	int id = getLineCache(cp.logLine);
	return m_cacheList[id].getSlineEndPos(cp, outCP);
}
//
//BOOL VisLineView::moveToWordPrev(const CHAR_POS &cp, __out CHAR_POS *outCP);
//BOOL VisLineView::moveToWordNext(const CHAR_POS &cp, __out CHAR_POS *outCP);
//
//BOOL VisLineView::moveToLineNext(const CHAR_POS &cp, __out CHAR_POS *outCP);
//BOOL VisLineView::moveToLinePrev(const CHAR_POS &cp, __out CHAR_POS *outCP);