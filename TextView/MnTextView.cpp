#include "MnTextView.h"	
//#include "../verui/verui.h"
#include "../MnTextDotNet/resource.h"
MnTextView::MnTextView(HWND hwnd):
	TextViewBase	(hwnd),
	//m_visualLineView(hwnd,m_pTextDoc)
	m_visualLineView(this),
	m_fMenuVisible(0),
	m_hResModule(0)
{
	m_hWnd			= hwnd		;
	m_isLButtonDown	= 0			;
	m_bufLen		= 0			;
	m_buffer		= NULL		;
	m_direction		= WD_VERTICAL;
	m_nScrollPos	= 0;
	m_nScrollMax	= 0;
	setMargin(Margin);
	m_pFontManager	= new MNFontManager();
//	m_pMenu			= 0;//new MNUiPopupMenu(hwnd);

}
MnTextView::~MnTextView(void)
{
	//for(int i = 0; i < USP_CACHE_SIZE; i++)
	//	UspFree(m_uspCache[i].uspData);
	if(m_pFontManager)
		delete m_pFontManager;
	//if(m_pMenu)
	//	delete m_pMenu;
}

LONG MnTextView::ClearFile()
{
	if(m_pTextDoc)
	{
		m_pTextDoc->clear();
		m_pTextDoc->EmptyDoc();
	}


	m_nLineCount		=	m_pTextDoc->linecount();
	
	m_visualLineView.setLineCount(m_nLineCount);
	
	//m_logline
	//m_nLongestLine		= m_pTextDoc->longestline(m_nTabWidthChars);

	m_nScrollPos		= 0;
	//m_nVScrollPos		= 0;
	//m_nHScrollPos		= 0;

	m_nSelectionStart	= 0;
	m_nSelectionEnd		= 0;
	m_nCursorOffset		= 0;
	m_CurrentCharPos	= CHAR_POS();
	//m_caretCharPos		= CHAR_POS();

	m_nCurrentLine		= 0;
	m_nCurrentLine_D    = 0;

	UpdateMetrics();

	

	return TRUE;
}
void MnTextView::ResetLineCache(ULONG line)
{
	int nSub_old		= m_visualLineView.getSubLineCount( line );
	int nViewLineOld	= m_visualLineView.getVisLineCount(      );
	m_visualLineView.resetCache(line);
	int nSub_new		= m_visualLineView.getSubLineCount( line );
	int nViewLineNew	= m_visualLineView.getVisLineCount(      );
	//WCHAR debug[100];
	//wsprintf(debug,L"subline count old:%d new %d ,| view line count old%d, new %d\n", nSub_old, nSub_new, nViewLineOld, nViewLineNew);
	//OutputDebugString(debug);
	if(nSub_old != nSub_new)
	{
		UpdateMetrics();
	}
}
void MnTextView::ResetLineCache()
{
	m_visualLineView.resetCache();
}
LONG MnTextView::OnSetText(WCHAR* buffer, ULONG length)
{
	ClearFile();

	if(m_pTextDoc->init_from_utf16(buffer, length))
	{
		//m_loglinecou   
		Smeg(TRUE);
		/*m_nLineCount = m_pTextDoc->linecount();

		m_visualLineView.setLineCount(m_nLineCount);*/

		m_nScrollPos		= 0;
		m_nSelectionStart	= 0;
		m_nSelectionEnd		= 0;
		m_nCursorOffset		= 0;

		//ResetLineCache();
		//UpdateMetrics();
		//m_visualLineView.resetCache();
		//m_visualLineView.setLineHeight(m_pFontManager->getLineHeight());
		//Smeg(TRUE);
		OnKillFocus(0);
		OnSetFocus(0);
		return TRUE;
	}
	return FALSE;
}
LONG MnTextView::OpenFile(TCHAR *szFileName)
{
	ClearFile();

	if(m_pTextDoc->init(szFileName))
	{
		//m_loglinecou   
		
		m_nLineCount = m_pTextDoc->linecount();

		m_visualLineView.setLineCount(m_nLineCount);

		m_nScrollPos		= 0;
		//m_nVScrollPos  = 0;
		//m_nHScrollPos  = 0;

		m_nSelectionStart	= 0;
		m_nSelectionEnd		= 0;
		m_nCursorOffset		= 0;

		ResetLineCache();
		UpdateMetrics();
		return TRUE;
	}

	return FALSE;
}
LONG MnTextView::ImportFile(WCHAR *szFileName, int conver_type)
{
	ClearFile();

	if(m_pTextDoc->init(szFileName, conver_type))
	{
		//m_loglinecou   
		
		m_nLineCount = m_pTextDoc->linecount();

		m_visualLineView.setLineCount(m_nLineCount);

		m_nScrollPos		= 0;
		//m_nVScrollPos  = 0;
		//m_nHScrollPos  = 0;

		m_nSelectionStart	= 0;
		m_nSelectionEnd		= 0;
		m_nCursorOffset		= 0;

		ResetLineCache();
		UpdateMetrics();
		return TRUE;
	}

	return FALSE;
}
LONG MnTextView::OnPaint()
{
	RECT updateRect;
	RECT cliRect,left,right,top,bottom;
	GetClientRect(m_hWnd, &cliRect);


	
	GetUpdateRect(m_hWnd, &updateRect, FALSE);
	PAINTSTRUCT ps;
	BeginPaint(m_hWnd, &ps);
	//HBRUSH b	= CreateSolidBrush(RGB(255,255,255));
	//FillRect(ps.hdc,&ps.rcPaint,b);
	//SetRect(
	//HRGN hrgnClient  = CreateRectRgnIndirect(&client);
	//SelectClipRgn(
	if(m_direction == WD_VERTICAL)
	{
		OnDrawV(&ps.hdc, updateRect);
	}
	else
	{
		//OnDrawH(&ps.hdc);
	}
	
	HBRUSH brush = CreateSolidBrush( RGB(255, 255, 255));
	SetRect(&left , 0, 0, m_MarginLeft, cliRect.bottom);
	SetRect(&right, cliRect.right - m_MarginRight, 0, cliRect.right , cliRect.bottom);
	SetRect(&top	,0,0,cliRect.right,m_MarginTop);
	SetRect(&bottom	,0,cliRect.bottom - m_MarginBottom,cliRect.right, cliRect.bottom);

	FillRect(ps.hdc, &left	,brush);
	FillRect(ps.hdc, &right	,brush);
	FillRect(ps.hdc, &top	,brush);
	FillRect(ps.hdc, &bottom,brush);

	DeleteObject(brush);
	EndPaint(m_hWnd, &ps);
	//wchar_t debug [50];
	//wsprintf(debug, L"update rect l:%d r:%d t:%d b:%d \n",updateRect.left, updateRect.right ,updateRect.top, updateRect.bottom);
	//OutputDebugString(debug);
	return 0;
}
LONG MnTextView::OnNcPaint(HRGN hrgnUpdate)
{
	RECT r;
	GetClientRect(m_hWnd,&r);
	HBRUSH b	= CreateSolidBrush(RGB(255,255,255));
	HDC hdc		= GetDC(m_hWnd);
	FillRect(hdc,&r,b);
	DeleteObject(b);
	ReleaseDC(m_hWnd,hdc);
	return 0;
}

//LONG OnPrint(HDC printDC, TVPRINTINFO* pPrintInfo)
//{
//	if(printDC == 0)
//	{
//		int stop =1 ;
//		return 0;
//	}
//	DOCINFO &di		= pPrintInfo->di;
//	di.cbSize		= sizeof(DOCINFO);
//	//di.lpszDocName	= L"MongolNote";
//	di.lpszOutput	= NULL;
//	di.fwType		= 0; // Windows 95 only; ignored on Windows NT
//	///////
//	//TextOut(printDC, 0,0,L"this is a test",14);
//
//	long  line_no		= 0;
//	ULONG line_length	= 0;
//	ULONG line_offset	= 0;
//	int	  h				= 0;
//	int	  x				= 0;
//	int heightPixel		= GetDeviceCaps(printDC, HORZRES);
//	int widthPixel		= GetDeviceCaps(printDC, VERTRES);
//	int  widthMM		= GetDeviceCaps(printDC, HORZSIZE);
//	float dot_per_mm	= widthPixel / widthMM;
//	int MarginMM		= 10;
//	int MarginPixel	= dot_per_mm * MarginMM;
//	int innerHeight		= heightPixel	- 2 * MarginPixel;
//	int innerWidth		= widthPixel	- 2 * MarginPixel;
//	int fontSizePixel	= -MulDiv(pPrintInfo->textSizePoint, GetDeviceCaps(printDC, LOGPIXELSY), 72);
//	
//	MNFontManager	fontManager;
//	LOGFONT			lf;
//
//	HFONT hFontScreen	= m_pFontManager->getFont(0);
//
//	GetObject(hFontScreen, sizeof(lf), &lf); 
//
//	lf.lfHeight			= fontSizePixel;
//	//lf.lfEscapement		= 900;
//	//lf.lfOrientation	= 900;
//	HFONT hFontPrinter	= CreateFontIndirect(&lf);
//
//
//	
//	
//	//int font_size_point = 
//	
//	fontManager.setPrimaryFont(hFontPrinter);
//	//fontManager.setPrimaryFont();
//	MNLineGlyfCache *pGlfCache;
//	WCHAR buffer[MAX_LINE_LENGTH];
//	
//
//	//HDC		memHdc	= CreateCompatibleDC(printDC);
//	//HBITMAP	memBmp	= CreateCompatibleBitmap(printDC, height, h);
//	//HBRUSH	bgBrush	= (HBRUSH) GetStockObject(WHITE_BRUSH);
//
//	//SelectObject(memHdc , memBmp );
//	//SelectObject(memHdc , bgBrush);
//	//SetMapMode(printDC);
//
//	//int mode = GetMapMode(printDC);
//	SetBkMode(printDC,OPAQUE);
//	SetBkColor(printDC, GetSysColor(COLOR_WINDOW));
//	pGlfCache = new  MNLineGlyfCache[m_pTextDoc->linecount()];
//	for(;line_no < m_pTextDoc->linecount(); line_no++)
//	{
//		line_length = m_pTextDoc->getline(line_no, buffer, MAX_LINE_LENGTH, &line_offset);
//		pGlfCache[line_no].initialize(line_no, line_offset, buffer, line_length, &fontManager);
//		pGlfCache[line_no].generateGlyph(printDC);
//		pGlfCache[line_no].breakLine(innerHeight);
//	}
//
//	int startX = widthPixel - MarginPixel;
//	x = startX;
//	h = fontManager.calcLineHeight(printDC);
//	StartDoc(printDC, &di);
//	StartPage(printDC);
//	for(line_no = 0; line_no < m_pTextDoc->linecount(); line_no ++)
//	{
//
//
//		for(int i = 0; i < pGlfCache[line_no].getLineCount(); i++ )
//		{
//			//RECT memRect = {0,0,height, h};
//			//FillRect(memHdc,&memRect,(HBRUSH)GetStockObject(BLACK_BRUSH));
//
//			if(x - h <= MarginPixel)
//			{
//				EndPage(printDC);
//				StartPage(printDC);
//				x = startX;
//			}
//			pGlfCache[line_no].drawSubLine(&printDC, i, MarginPixel, x - h);
//
//			//POINT point[3];
//			//point[0].x = 0;//height;//x + h;
//			//point[0].y = x;// + h + h/2;
//
//			//point[1].x = height;//0;
//			//point[1].y = x;//point[0].y;
//
//			//point[2].x = 0;//point[0].x;
//			//point[2].y = x + h;///2;
//			
//			//PlgBlt(printDC, point, memHdc, 0, 0, height, h, NULL, 0, 0);
//
//			x	-= h;
//		}
//	}
//
//	//DeleteObject(bgBrush);
//	//DeleteObject(memBmp);
//	//DeleteDC(memHdc);
//	
//	///////
//	
//	//EndPage(printDC);
//	EndDoc(printDC);
//	DeleteDC(printDC);
//	delete[] pGlfCache;
//	return 0;
//}
LONG MnTextView::OnPrint(HDC printDC, int fontSizePoint)
{
	if(printDC == 0)
	{
		int stop =1 ;
		return 0;
	}
	WCHAR title[MAX_PATH];
	m_pTextDoc->getfilename(0,title);
	DOCINFO di;
	di.cbSize		= sizeof(DOCINFO);
	di.lpszDocName	= title;
	di.lpszOutput	= NULL;
	di.fwType		= 0; // Windows 95 only; ignored on Windows NT
	
	///////
	//TextOut(printDC, 0,0,L"this is a test",14);

	long	line_no		= 0;
	ULONG	line_length	= 0;
	ULONG	line_offset	= 0;
	int		h			= 0;
	int		x			= 0;
	int		heightPixel	= GetDeviceCaps(printDC, HORZRES);
	int		widthPixel	= GetDeviceCaps(printDC, VERTRES);
	int		widthMM		= GetDeviceCaps(printDC, HORZSIZE);
	float	dot_per_mm	= widthPixel / widthMM;
	int		MarginMM	= 10;
	int		MarginPixel= dot_per_mm * MarginMM;
	int		innerHeight	= heightPixel	- 2 * MarginPixel;
	int		innerWidth	= widthPixel	- 2 * MarginPixel;
	int		fontSizePixel= MulDiv(fontSizePoint, GetDeviceCaps(printDC, LOGPIXELSY), 72);
	
	MNFontManager	fontManager;
	LOGFONT			lf;

	HFONT hFontScreen	= m_pFontManager->getFont(0);

	GetObject(hFontScreen, sizeof(lf), &lf); 

	lf.lfHeight			= fontSizePixel;
	//lf.lfEscapement		= 900;
	//lf.lfOrientation	= 900;
	HFONT hFontPrinter	= CreateFontIndirect(&lf);


	
	
	//int font_size_point = 
	
	fontManager.setPrimaryFont(hFontPrinter);

	fontManager.setTesterMode(m_pFontManager->isTesterMode());
	//fontManager.setPrimaryFont();
	MNLineGlyfCache *pGlfCache;
	WCHAR buffer[MAX_LINE_LENGTH];
	

	//HDC		memHdc	= CreateCompatibleDC(printDC);
	//HBITMAP	memBmp	= CreateCompatibleBitmap(printDC, height, h);
	//HBRUSH	bgBrush	= (HBRUSH) GetStockObject(WHITE_BRUSH);

	//SelectObject(memHdc , memBmp );
	//SelectObject(memHdc , bgBrush);
	//SetMapMode(printDC);

	//int mode = GetMapMode(printDC);
	SetBkMode(printDC,OPAQUE);
	SetBkColor(printDC, GetSysColor(COLOR_WINDOW));
	pGlfCache = new  MNLineGlyfCache[m_pTextDoc->linecount()];
	for(;line_no < m_pTextDoc->linecount(); line_no++)
	{
		line_length = m_pTextDoc->getline(line_no, buffer, MAX_LINE_LENGTH, &line_offset);
		pGlfCache[line_no].initialize(line_no, line_offset, buffer, line_length, &fontManager);
		pGlfCache[line_no].generateGlyph(printDC, buffer, line_length);
		pGlfCache[line_no].breakLine(innerHeight);
	}

	int startX = widthPixel - MarginPixel;
	x = startX;
	h = fontManager.calcLineHeight(printDC);
	StartDoc(printDC, &di);
	StartPage(printDC);
	for(line_no = 0; line_no < m_pTextDoc->linecount(); line_no ++)
	{
		for(int i = 0; i < pGlfCache[line_no].getLineCount(); i++ )
		{
			//RECT memRect = {0,0,height, h};
			//FillRect(memHdc,&memRect,(HBRUSH)GetStockObject(BLACK_BRUSH));

			if(x - h <= MarginPixel)
			{
				EndPage(printDC);
				StartPage(printDC);
				x = startX;
			}
			pGlfCache[line_no].drawSubLine(&printDC, i, MarginPixel, x - h);

			//POINT point[3];
			//point[0].x = 0;//height;//x + h;
			//point[0].y = x;// + h + h/2;

			//point[1].x = height;//0;
			//point[1].y = x;//point[0].y;

			//point[2].x = 0;//point[0].x;
			//point[2].y = x + h;///2;
			
			//PlgBlt(printDC, point, memHdc, 0, 0, height, h, NULL, 0, 0);

			x	-= h;
		}
	}

	//DeleteObject(bgBrush);
	//DeleteObject(memBmp);
	//DeleteDC(memHdc);
	
	///////
	
	//EndPage(printDC);
	EndDoc(printDC);
	DeleteDC(printDC);
	delete[] pGlfCache;
	return 0;
}
LONG MnTextView::OnSetFont(HFONT hFont)
{
	m_pFontManager->setPrimaryFont(hFont);
	m_visualLineView.resetCache();
	m_visualLineView.setLineHeight(m_pFontManager->getLineHeight());
	Smeg(TRUE);
	OnKillFocus(0);
	OnSetFocus(0);
	ImeSetCompWindowFont();
	return 0;
}
//LONG MnTextView::OnSetFont(WCHAR* fontName)
//{
//	m_pFontManager->setPrimaryFont(MNText(fontName),20,0,0,0);
//	m_visualLineView.resetCache();
//	m_visualLineView.setLineHeight(m_pFontManager->getLineHeight());
//	Smeg(true);
//	return 0;
//}
LONG MnTextView::OnSize(UINT nFlags, int width, int height)
{
	RECT cliRect;
	GetClientRect(m_hWnd, &cliRect);
	bool need_refresh = false;
	if(m_direction == WD_VERTICAL && height - getMarginTB() != m_visualLineView.getWidth())
	{
		breakLines(width- getMarginLR(), height - getMarginTB());
		need_refresh = true;
	}
	if(m_visualLineView.getLineHeight() > 0)
	{
		m_nWindowLines	= min((unsigned)(width- getMarginLR()) / m_visualLineView.getLineHeight(), m_visualLineView.getVisLineCount());
	}
	else
	{
		m_nWindowLines	= 0 ;
	}
	/*
	int remain = m_visualLineView.getVisLineCount() - m_nScrollPos;
	if(remain < 0)
	{
		m_nScrollPos = 0;
	}
	else if(remain < m_nWindowLines)
	{
		m_nScrollPos -= (m_nWindowLines - remain);
		if(m_nScrollPos < 0) m_nScrollPos = 0;
	}*/

	m_nScrollPos = min(m_nScrollPos, m_visualLineView.getVisLineCount() - m_nWindowLines);
	
	SetupScrollbars();
	if(1/*need_refresh*/)
	{
		RefreshWindow();
	}
	//RepositionCaret();
	
	ScrollToCaret();
	updateCaretPos(m_CurrentCharPos);
	NotifyParent(TVN_CURSOR_CHANGE);
	return 0;
}
VOID MnTextView::RepositionCaret()
{
	CHAR_POS cp;
	FilePosToCharPos(m_nCursorOffset,&cp);
	if(cp != m_CurrentCharPos)
	{
		m_CurrentCharPos = cp;
	}
	updateCaretPos(m_CurrentCharPos);
	wchar_t debug[50];
	wsprintf(debug,L"l%d,i%d,t%d\n",m_CurrentCharPos.logLine,m_CurrentCharPos.index,m_CurrentCharPos.trailing);
	OutputDebugString(debug);
}
BOOL MnTextView::MouseCoordToCharPos(int mx, int my, __out CHAR_POS* charPos, int *px )
{
	POINT		point = {mx,my};
	convertIn(&point);
	m_visualLineView.getCharPos(
		point.x,
		point.y,
		charPos,
		&point);

	convertOut(&point);
	*px = point.x;
	return TRUE;
}
LONG MnTextView::OnSetFocus(HWND hwndOld)
{
	//CreateCaret(m_hWnd, (HBITMAP)NULL, m_nCaretWidth, m_nLineHeight);
	CreateMyCaret();
	updateCaretPos(m_CurrentCharPos);

	ShowCaret(m_hWnd);
	RefreshWindow();
	return 0;
}
LONG MnTextView::OnKeyDown(UINT nKeyCode, UINT nFlags)
{
	bool fCtrlDown	= IsKeyPressed(VK_CONTROL);
	bool fShiftDown	= IsKeyPressed(VK_SHIFT);
	switch(nKeyCode)
	{
	case VK_UP:

		if(fCtrlDown)	MoveWordPrev();
		else			
		{
			MoveCharPrev(true,true);
			ScrollToCaret();
		}

		//fAdvancing = FALSE;
		break;

	case VK_DOWN:
		
		if(fCtrlDown)	MoveWordNext();
		else			
		{

			MoveCharNext(true,true);
			ScrollToCaret();
		}
			
		//fAdvancing = TRUE;
		break;

	case VK_LEFT:
		if(fCtrlDown)	Scroll(-1, 0);
		else			MoveLineUp(1);
		break;

	case VK_RIGHT:
		if(fCtrlDown)	Scroll(1, 0);
		else			MoveLineDown(1);
		break;
	//case VK_SPACE:
		//if(fCtrlDown)
		//{
		//	OnCtrlSpaceDown();
		//	return 0;
		//}
	default:
		return TextViewBase::OnKeyDown(nKeyCode, nFlags);
	}
	// Extend selection if <shift> is down
	if(fShiftDown)
	{		
		InvalidateRange(m_nSelectionEnd, m_nCursorOffset);
		m_nSelectionEnd	= m_nCursorOffset;
		NotifyParent( TVN_SELECTION_CHANGED);
	}
	// Otherwise clear the selection
	else if(!fCtrlDown)
	{
		if(m_nSelectionStart != m_nSelectionEnd)
			InvalidateRange(m_nSelectionStart, m_nSelectionEnd);

		m_nSelectionEnd		= m_nCursorOffset;
		m_nSelectionStart	= m_nCursorOffset;
		NotifyParent( TVN_SELECTION_CHANGED);
	}

	// update caret-location (xpos, line#) from the offset
	//UpdateCaretOffset(m_nCursorOffset, fAdvancing, &m_nCaretPosX, &m_nCurrentLine);
	//CHAR_POS cp;
	//FilePosToCharPos(m_nCursorOffset, &m_CurrentCharPos);
	//m_nCurrentLine_D = cp.logLine;
	
	// maintain the caret 'anchor' position *except* for up/down actions
	if(nKeyCode != VK_UP && nKeyCode != VK_DOWN)
	{
		//m_nAnchorPosX = m_nCaretPosX;

		// scroll as necessary to keep caret within viewport
		//ScrollToPosition(m_nCaretPosX, m_nCurrentLine);
	}
	else
	{
		// scroll as necessary to keep caret within viewport
		if(!fCtrlDown);
			//ScrollToPosition(m_nCaretPosX, m_nCurrentLine);
	}

	NotifyParent(TVN_CURSOR_CHANGE);

	return 0;
}
LONG MnTextView::OnRButtonDown(UINT nFlags, int mx, int my)
{
	RECT r;
	POINT pt = {mx,my};
	
	GetClientRect(m_hWnd,&r);
	if(/*m_fMenuVisible &&*/ IsInside(r,pt))
	{
		//HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
		//SetCapture(this->m_hWnd);
		m_fMenuVisible = true;
		ClientToScreen(m_hWnd, &pt);
//
		//SetCursor(cursor);
	}else
	{
		m_fMenuVisible = false;
//		m_pMenu->Hide();
		//HidePopUpWindow();
		//ReleaseCapture();
	}
	//HMENU hMenu = GetMenu(m_hWnd);
	////TrackPopupMenu( m_hUserMenu, TPM_LEFTALIGN, mx, my, 0, m_hWnd, NULL );
	HWND deskTopHwnd =  GetDesktopWindow();
	//SetActiveWindow(deskTopHwnd);
	
	return 0;
}

//
//	WM_LBUTTONDOWN
//
//  Position caret to nearest text character under mouse
//
LONG MnTextView::OnLButtonDown(UINT nFlags, int mx, int my)
{
	//if(m_fMenuVisible)
	//{
	//	m_fMenuVisible = false;
	//	if(m_pMenu)
	//		m_pMenu->Hide();
	//	ReleaseCapture();
	//	SendMessage(m_hWnd, WM_LBUTTONDOWN,0, MAKELONG(mx,my));
	//	return 0;
	//}
	ULONG nLineNo;
	ULONG nFileOff;
	
	// regular mouse input - mouse is within 
	/*if(ValidatePoint(mx,my))
	{*/
		// map the mouse-coordinates to a real file-offset-coordinate
		//MouseCoordToFilePos(mx, my, &nLineNo, &nFileOff, &m_nCaretPosX);
		
		//m_nAnchorPosX = m_nCaretPosX;
		POINT point = {mx,my};
		POINT outPoint;
		POINT outPoint2;
		//CHAR_POS charPos;
		
		convertIn(&point);

		m_visualLineView.getCharPos(point.x,point.y,&m_CurrentCharPos,&outPoint);
		//m_visualLineView.getLocation(&m_CurrentCharPos,&outPoint2);
		convertOut(&outPoint);
		//convertOut(&outPoint2);
		CharPosToFilePos(m_CurrentCharPos,&nFileOff);

		//UpdateCaretXY(m_nCaretPosX, nLineNo);
		updateCaretPos(outPoint);

		//WCHAR debug[50];

		//wsprintf(debug,L"x:%d,y:%d",outPoint.x,outPoint.y);

		//OutputDebugString(debug);
		// Any key but <shift>
		if(IsKeyPressed(VK_SHIFT) == false)
		{
			// remove any existing selection
			InvalidateRange(m_nSelectionStart, m_nSelectionEnd);

			// reset cursor and selection offsets to the same location
			m_nSelectionStart	= nFileOff;
			m_nSelectionEnd		= nFileOff;
			m_nCursorOffset		= nFileOff;
			m_visualLineView.setSelection(CHAR_POS(),CHAR_POS());
		}
		else
		{
			// redraw to cursor
			InvalidateRange(m_nSelectionEnd, nFileOff);
			
			// extend selection to cursor
			m_nSelectionEnd		= nFileOff;
			m_nCursorOffset		= nFileOff;
		}

		if(IsKeyPressed(VK_MENU))
		{
			//m_cpBlockStart.line = nLineNo;
			//m_cpBlockStart.xpos = m_nCaretPosX;
			m_nSelectionType	= SEL_BLOCK;
		}
		else
		{
			m_nSelectionType	= SEL_NORMAL;
		}

		// set capture for mouse-move selections
		m_nSelectionMode = IsKeyPressed(VK_MENU) ? SEL_BLOCK : SEL_NORMAL;
	//}
	// mouse clicked within margin 
	//else
	//{
	//	// remove any existing selection
	//	InvalidateRange(m_nSelectionStart, m_nSelectionEnd);

	//	nLineNo = (my / m_nLineHeight) + m_nVScrollPos;

	//	//
	//	// if we click in the margin then jump back to start of line
	//	//
	//	if(m_nHScrollPos != 0)
	//	{
	//		m_nHScrollPos = 0;
	//		SetupScrollbars();
	//		RefreshWindow();
	//	}

	//	m_pTextDoc->lineinfo_from_lineno(nLineNo, &m_nSelectionStart, &m_nSelectionEnd, 0, 0);
	//	m_nSelectionEnd    += m_nSelectionStart;
	//	m_nCursorOffset	    = m_nSelectionStart;
	//	
	//	m_nSelMarginOffset1 = m_nSelectionStart;
	//	m_nSelMarginOffset2 = m_nSelectionEnd;

	//	InvalidateRange(m_nSelectionStart, m_nSelectionEnd);
	//	
	//	UpdateCaretOffset(m_nCursorOffset, FALSE, &m_nCaretPosX, &m_nCurrentLine);
	//	m_nCurrentLine = m_visualLineView.
	//	//m_nAnchorPosX = m_nCaretPosX;

	//	// set capture for mouse-move selections
	//	m_nSelectionMode = SEL_MARGIN;
	//}


	m_nCurrentLine_D = m_CurrentCharPos.logLine;
	SetCapture(m_hWnd);

	//TVNCURSORINFO ci = { { 0 }, nLineNo, 0, m_nCursorOffset };
	NotifyParent(TVN_CURSOR_CHANGE);
	NotifyParent( TVN_SELECTION_CHANGED);
	return 0;
}
//
//	WM_MOUSEMOVE
//
//	Set the selection end-point if we are dragging the mouse
//
LONG MnTextView::OnMouseMove(UINT nFlags, int mx, int my)
{
	//if(m_pMenu)
	//{
	//	POINT pt ={mx,my};
	//	RECT rectMenu;
	//	
	//	GetWindowRect(m_pMenu->GetWindowHandle(),&rectMenu);
	//	ClientToScreen(m_hWnd, &pt);
	//	//if(IsInside(rectMenu,pt))
	//	//{
	//	//	SendMessage(m_pMenu->GetWindowHandle(), WM_MOUSEMOVE,0,0);
	//	//	return 0;
	//	//}
	//	
	//}

	if(m_nSelectionMode)
	{
		ULONG	nLineNo, nFileOff;
		BOOL	fCurChanged = FALSE;

		RECT	rect;
		POINT	pt = { mx, my };

		//
		//	First thing we must do is switch from margin-mode to normal-mode 
		//	if the mouse strays into the main document area
		//
		//if(m_nSelectionMode == SEL_MARGIN && mx > LeftMarginWidth())
		//{
		//	m_nSelectionMode = SEL_NORMAL;
		//	SetCursor(LoadCursor(0, IDC_IBEAM));
		//}

		//
		//	Mouse-scrolling: detect if the mouse
		//	is inside/outside of the TextView scrolling area
		//  and stop/start a scrolling timer appropriately
		//
		GetClientRect(m_hWnd, &rect);
		
		// build the scrolling area
		int h = m_visualLineView.getLineHeight();
		rect.bottom -= rect.bottom % (h?h:20);
		rect.left   += m_MarginLeft;
/*
		// If mouse is within this area, we don't need to scroll
		if(PtInRect(&rect, pt))
		{
			if(m_nScrollTimer != 0)
			{
				KillTimer(m_hWnd, m_nScrollTimer);
				m_nScrollTimer = 0;
			}
		}
		// If mouse is outside window, start a timer in
		// order to generate regular scrolling intervals
		else 
		{
			if(m_nScrollTimer == 0)
			{
				m_nScrollCounter = 0;
				m_nScrollTimer   = SetTimer(m_hWnd, 1, 30, 0);
			}
		}
		*/

		// get new cursor offset+coordinates
		CHAR_POS oldCP = m_CurrentCharPos;
		POINT pointOut,pointIn = {mx,my};
		convertIn(&pointIn);
		m_visualLineView.getCharPos(pointIn.x,pointIn.y,&m_CurrentCharPos,&pointOut);

		/*WCHAR b[50];
		wsprintf(b,L"logline:%d,index:%d,trailing:%d\n",charPos.logLine,charPos.index,charPos.trailing);
		OutputDebugString(b);*/

		convertOut(&pointOut);
		if(pointIn.x == pointOut.x && pointIn.y == pointOut.y)
		{
			int stop=1;
		}

		CharPosToFilePos(m_CurrentCharPos,&nFileOff);
		nLineNo = m_CurrentCharPos.logLine;

		//MouseCoordToFilePos(mx, my, &nLineNo, &nFileOff, &m_nCaretPosX);
		//m_nAnchorPosX = m_nCaretPosX;

		//m_cpBlockEnd.line = nLineNo;
		//m_cpBlockEnd.xpos = mx + m_nHScrollPos * m_nFontWidth - LeftMarginWidth();//m_nCaretPosX;


		// redraw the old and new lines if they are different
		//UpdateLine(nLineNo);
		m_nCurrentLine_D = m_CurrentCharPos.logLine;
		// update the region of text that has changed selection state
		fCurChanged = m_nSelectionEnd == nFileOff ? FALSE : TRUE;
		//if(m_nSelectionEnd != nFileOff)
		{
			ULONG linelen;
			m_pTextDoc->lineinfo_from_lineno(nLineNo, 0, &linelen, 0, 0);

			m_nCursorOffset	= nFileOff;

			//if(m_nSelectionMode == SEL_MARGIN)
			//{
			//	if(nFileOff >= m_nSelectionStart)
			//	{
			//		nFileOff += linelen;
			//		m_nSelectionStart = m_nSelMarginOffset1;
			//	}
			//	else
			//	{
			//		m_nSelectionStart = m_nSelMarginOffset2;
			//	}
			//}

			// redraw from old selection-pos to new position
			//CHAR_POS cp1,cp2;
			//FilePosToCharPos(m_nSelectionStart,&cp1);
			//FilePosToCharPos(nFileOff,&cp2);
			//m_visualLineView.setSelection(cp1,cp2);
			
			InvalidateRange(oldCP , m_CurrentCharPos);
			//InvalidateRange(m_nSelectionEnd, nFileOff);
			m_nSelectionEnd = nFileOff;
			// adjust the cursor + selection to the new offset
			
		}

		if(m_nSelectionMode == SEL_BLOCK)
			RefreshWindow();

		//m_nCaretPosX = mx+m_nHScrollPos*m_nFontWidth-LeftMarginWidth();
		// always set the caret position because we might be scrolling
		//UpdateCaretXY(m_nCaretPosX, m_nCurrentLine);
		updateCaretPos(pointOut);

		if(fCurChanged)
		{
			NotifyParent(TVN_CURSOR_CHANGE);
		}
		ScrollToCaret();
	}
	// mouse isn't being used for a selection, so set the cursor instead
	else
	{
		//HCURSOR hCursor = LoadCursor(GetModuleHandle(L"MnCtrlDotNet"), MAKEINTRESOURCE( IDC_IBEAMV));
		HCURSOR hCursor = 0;
		if(m_hResModule)
		{
			hCursor= LoadCursor(m_hResModule, MAKEINTRESOURCE( IDC_IBEAMV));
		}
		else
		{
			hCursor= LoadCursor(0, MAKEINTRESOURCE( IDC_IBEAM));
		}
		if(hCursor)
				SetCursor(hCursor);
	}
	WCHAR b[50];
	wsprintf(b,L"OnMouseMove x:%3d, y:%3d\n", mx, my);
	OutputDebugString(b);
	return 0;
}
//
//	WM_LBUTTONUP 
//
//	Release capture and cancel any mouse-scrolling
//
LONG MnTextView::OnLButtonUp(UINT nFlags, int mx, int my)
{
	// shift cursor to end of selection
	//if(m_nSelectionMode == SEL_MARGIN)
	//{
	//	m_nCursorOffset = m_nSelectionEnd;
	//	UpdateCaretOffset(m_nCursorOffset, FALSE, &m_nCaretPosX, &m_nCurrentLine);
	//}

	if(m_nSelectionMode)
	{
		// cancel the scroll-timer if it is still running
		//if(m_nScrollTimer != 0)
		//{
		//	KillTimer(m_hWnd, m_nScrollTimer);
		//	m_nScrollTimer = 0;
		//}

		m_nSelectionMode = SEL_NONE;
		ReleaseCapture();
		NotifyParent(TVN_SELECTION_CHANGED);
		
	}

	return 0;
}
void MnTextView::Smeg(BOOL fAdvancing)
{
	m_pTextDoc->init_linebuffer();

	m_nLineCount   = m_pTextDoc->linecount();

	m_visualLineView.setLineCount(m_nLineCount);
	
	FilePosToCharPos(m_nCursorOffset ,&m_CurrentCharPos);
	m_nCurrentLine_D = m_CurrentCharPos.logLine;
	updateCaretPos(m_CurrentCharPos);



	UpdateMetrics();
	SetupScrollbars();


	//UpdateCaretOffset(m_nCursorOffset, fAdvancing, &m_nCaretPosX, &m_nCurrentLine);
	
	
	//RepositionCaret();


	//m_nAnchorPosX = m_nCaretPosX;
	//ScrollToPosition(m_nCaretPosX, m_nCurrentLine);
	//RepositionCaret();
}
LONG MnTextView::InvalidateRange(const CHAR_POS& cp1, const CHAR_POS& cp2)
{
	RECT updateRect ,cliRect; 
	GetClientRect(m_hWnd, &cliRect);

	
	if(cp1== cp2)return 0;

	int h		= m_visualLineView.getLineHeight();
	CHAR_POS stCP = min(cp1, cp2);
	CHAR_POS enCP = max(cp1, cp2);

	POINT stPt, enPt;
	m_visualLineView.getLocation(&stCP,&stPt);
	m_visualLineView.getLocation(&enCP,&enPt);

	convertOut(&stPt);
	convertOut(&enPt);

	if(m_direction == WD_HORIZONTAL)
	{
		return 0;
	}
	else
	{

		if(stPt.x == enPt.x)
		{
			SetRect(&updateRect, stPt.x, stPt.y, stPt.x + h, enPt.y);
		}else 
		{
			int endX = min(enPt.x + h, cliRect.right - m_MarginRight);
			SetRect(&updateRect, stPt.x, m_MarginTop, endX, cliRect.bottom - m_MarginBottom);
		}
		InvalidateRect(m_hWnd,&updateRect,FALSE);
		return 0;
	}
}
//
//	Redraw any line which spans the specified range of text
//
LONG MnTextView::InvalidateRange(ULONG nStart, ULONG nFinish)
{
	//m_visualLineView.resetCache();
	ULONG start  = min(nStart, nFinish);
	ULONG finish = max(nStart, nFinish);
	
	int   ypos;
	RECT  rect;
	RECT  client;
	TextIterator itor;

	// information about current line:
	ULONG lineStart;
	ULONG lineEnd;
	ULONG off_chars;
	ULONG len_chars;

	// nothing to do?
	if(start == finish)
		return 0;

	//
	//	Find the start-of-line information from specified file-offset
	//
	//lineStart	= m_pTextDoc->lineno_from_offset(start);
	//lineEnd		= m_pTextDoc->lineno_from_offset(finish) + 1;

	CHAR_POS cp1,cp2;

	FilePosToCharPos(start	,&cp1);
	FilePosToCharPos(finish	,&cp2);

	lineStart	= m_visualLineView.getLineIndex(cp1).visLine;
	lineEnd		= m_visualLineView.getLineIndex(cp2).visLine + 1;

	RECT updateRect ,cliRect; 
	GetClientRect(m_hWnd, &cliRect);

	int h		= m_visualLineView.getLineHeight();

	/*
	if(lineStart == lineEnd)
	{
		POINT pt1,pt2;
		m_visualLineView.getLocation(&cp1,&pt1);
		m_visualLineView.getLocation(&cp2,&pt2);
		convertOut(&pt1);
		convertOut(&pt2);

		SetRect(
			 &updateRect		
			 , pt1.x
			 , pt1.y
			 , pt1.x + h
			 , pt2.y
		);

		InvalidateRect(m_hWnd,&updateRect,FALSE);
		return 0;
	}
	else
	{
		lineEnd += 1;
	}
	*/

	// clip to top of window

//rect
	if(lineStart < m_nScrollPos)
	{
		lineStart = m_nScrollPos;
	}
	

	
	int t	= (lineStart - m_nScrollPos) * h;
	int b	= (lineEnd	 - m_nScrollPos) * h;

	

	if( lineStart < lineEnd)
	{
		if(m_direction == WD_HORIZONTAL)
		{
			SetRect(
				 &updateRect		
				, m_MarginLeft				
				, m_MarginTop + t
				, cliRect.right	- m_MarginRight
				, m_MarginTop + b
			);
		}
		else
		{
			SetRect(
				 &updateRect
				, m_MarginLeft + t
				, m_MarginTop
				, m_MarginLeft + b
				, cliRect.bottom - m_MarginBottom
			);
		}
	}
	InvalidateRect(m_hWnd,&updateRect,FALSE);
	return 0;
}
BOOL MnTextView::InvalidateVisLine(const LINE_INDEX& idx)
{
	//RECT updateRect ,cliRect; 
	//GetClientRect(m_hWnd, &cliRect);
	//int h	= m_visualLineView.getLineHeight();

	//if(idx >= m_offset && idx.visLine < m_nWindowLines )
	//{
	//	if(m_direction == WD_HORIZONTAL)
	//	{
	//		int top = m_MarginTop + (idx.visLine - m_offset.visLine) * h;
	//		SetRect(&updateRect,
	//			0,
	//			max(0,top),
	//			cliRect.right,
	//			top + h
	//			);
	//	}
	//	else
	//	{
	//		int left = m_MarginLeft + (idx.visLine - m_nScrollPos) * h;
	//		SetRect(&updateRect,
	//			left,
	//			0,
	//			cliRect.bottom,
	//			left + h
	//			);
	//	}
	//}
	return 1;//InvalidateRect(m_hWnd,&updateRect,FALSE);
}
BOOL MnTextView::InvalidateLine(ULONG nLineNo)
{
	LINE_INDEX idx	= m_visualLineView.getLineIndex(nLineNo,0);
	int count		= m_visualLineView.getSubLineCount(nLineNo);
	int h			= m_visualLineView.getLineHeight();
	RECT updateRect ,cliRect; 
	GetClientRect(m_hWnd,&cliRect);

	if(m_direction == WD_HORIZONTAL)
	{
		int top		= m_MarginTop + (idx.visLine - m_nScrollPos) * h;
		int bottom	= top + h * count;

		SetRect(&updateRect,
			0,
			max(0,top),
			cliRect.right,
			min((long int)cliRect.bottom,bottom)
		);
	
	}else
	{
		int left	= m_MarginLeft + (idx.visLine - m_nScrollPos) * h;
		int right	= left + h * count;

		SetRect(&updateRect,
			max(0,left),
			0,
			min(cliRect.right,right),
			cliRect.bottom
		);
	}
	return InvalidateRect(m_hWnd,&updateRect,FALSE);
}
BOOL MnTextView::ValidatePoint(int x, int y)
{
	RECT cliRect;
	GetClientRect(m_hWnd,&cliRect);
	if(    x > m_MarginLeft
		&& x < cliRect.right - m_MarginRight
		&& y > m_MarginTop
		&& y < cliRect.bottom - m_MarginBottom)
	{
		return TRUE;
	}
	return FALSE;
}
//
//	Set scrollbar positions and range
//
VOID MnTextView::SetupScrollbars()
{
	SCROLLINFO si = { sizeof(si) };

	si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_DISABLENOSCROLL;

	////
	////	Vertical scrollbar
	////
	//si.nPos  = m_nVScrollPos;		// scrollbar thumb position
	//si.nPage = m_nWindowLines;		// number of lines in a page
	//si.nMin  = 0;					
	//si.nMax  = m_nLineCount - 1;	// total number of lines in file
	//
	//SetScrollInfo(m_hWnd, SB_VERT, &si, TRUE);

	//
	//	Horizontal scrollbar
	//
	si.nPos  = m_nScrollPos;		// scrollbar thumb position
	si.nPage = m_nWindowLines;	// number of lines in a page
	si.nMin  = 0;
	si.nMax  = m_visualLineView.getVisLineCount() - 1;	// total number of lines in file

	SetScrollInfo(m_hWnd, SB_HORZ, &si, TRUE);

	// adjust our interpretation of the max scrollbar range to make
	// range-checking easier. The scrollbars don't use these values, they
	// are for our own use.
	//m_nVScrollMax = m_nLineCount   - m_nWindowLines;
	//m_nHScrollMax = m_visualLineView.getVisLineCount() - m_nWindowLines;
	m_nScrollMax  = m_visualLineView.getVisLineCount() - m_nWindowLines;
}
//
//	ScrollRgn
//
//	Scrolls the viewport in specified direction. If fReturnUpdateRgn is true, 
//	then a HRGN is returned which holds the client-region that must be redrawn 
//	manually. This region must be deleted by the caller using DeleteObject.
//
//  Otherwise ScrollRgn returns NULL and updates the entire window 
//
HRGN MnTextView::ScrollRgn(int dx, int dy, bool fReturnUpdateRgn)
{
	RECT clip;

	GetClientRect(m_hWnd, &clip);

	//
	// make sure that dx,dy don't scroll us past the edge of the document!
	//

	// scroll up
	//if(dy < 0)
	//{
	//	dy = -(int)min((ULONG)-dy, m_nVScrollPos);
	//	clip.top = -dy * m_nLineHeight;
	//}
	//// scroll down
	//else if(dy > 0)
	//{
	//	dy = min((ULONG)dy, m_nVScrollMax-m_nVScrollPos);
	//	clip.bottom = (m_nWindowLines -dy) * m_nLineHeight;
	//}


	// scroll left
	if(dx < 0)
	{
		dx = -(int)min(-dx, m_nScrollMax/*m_nHScrollPos*/);
		clip.left = -dx * m_visualLineView.getHeight();
	}
	// scroll right
	else if(dx > 0)
	{
		dx = min((unsigned)dx, (unsigned)/*m_nHScrollMax*/m_nScrollMax - m_nScrollPos);
		clip.right = (m_nWindowLines - dx) * m_visualLineView.getHeight() ;
	}

	// adjust the scrollbar thumb position
	m_nScrollPos += dx;
	m_nScrollPos = max(0, min(m_nScrollMax,m_nScrollPos));
	//m_nVScrollPos += dy;

	// ignore clipping rectangle if its a whole-window scroll
	if(fReturnUpdateRgn == false)
		GetClientRect(m_hWnd, &clip);

	// take margin into account
	//clip.left += LeftMarginWidth();

	// perform the scroll
	if(dx != 0 || dy != 0)
	{
		// do the scroll!
		ScrollWindowEx(
			m_hWnd, 
			-dx * m_visualLineView.getHeight(),					// scale up to pixel coords
			0,
			NULL,								// scroll entire window
			&clip,								// clip the non-scrolling part
			0, 
			0, 
			SW_INVALIDATE
			);

		SetupScrollbars();

		if(fReturnUpdateRgn)
		{
			RECT client;

			GetClientRect(m_hWnd, &client);

			//clip.left -= LeftMarginWidth();

			HRGN hrgnClient  = CreateRectRgnIndirect(&client);
			HRGN hrgnUpdate  = CreateRectRgnIndirect(&clip);

			// create a region that represents the area outside the
			// clipping rectangle (i.e. the part that is never scrolled)
			CombineRgn(hrgnUpdate, hrgnClient, hrgnUpdate, RGN_XOR);

			DeleteObject(hrgnClient);

			return hrgnUpdate;
		}
	}

	if(dx != 0)
	{
		GetClientRect(m_hWnd, &clip);
		//clip.right = LeftMarginWidth();
		//ScrollWindow(m_hWnd, 0, -dy * m_nLineHeight, 0, &clip);
		InvalidateRect(m_hWnd, &clip, 0);
	}

	return NULL;
}
void MnTextView::ScrollToCaret()
{
	LINE_INDEX idx = m_visualLineView.getLineIndex(m_CurrentCharPos);

	int min = m_nScrollPos;
	int max = m_nScrollPos + m_nWindowLines - 1;
	if(idx.visLine < m_nScrollPos)
	{
		Scroll( idx.visLine - m_nScrollPos, 0);
	}
	else if(idx.visLine > max)
	{
		Scroll( idx.visLine - max, 0 );
	}
	//updateCaretPos(m_CurrentCharPos);
}
//
//	Scroll viewport in specified direction
//
VOID MnTextView::Scroll(int dx, int dy)
{
	// do a "normal" scroll - don't worry about invalid regions,
	// just scroll the whole window 
	ScrollRgn(dx, dy, false);
	updateCaretPos(m_CurrentCharPos);
}
//
//	Horizontal scrollbar support
//
LONG MnTextView::OnHScroll(UINT nSBCode, UINT nPos)
{
	int oldpos = m_nScrollPos;

	switch(nSBCode)
	{
	case SB_LEFT:
		m_nScrollPos = 0;
		RefreshWindow();
		break;

	case SB_RIGHT:
		m_nScrollPos = m_nScrollMax;
		RefreshWindow();
		break;

	case SB_LINELEFT:
		Scroll(-1, 0);
		break;

	case SB_LINERIGHT:
		Scroll(1, 0);
		break;

	case SB_PAGELEFT:
		Scroll(-m_nWindowLines, 0);
		break;

	case SB_PAGERIGHT:
		Scroll(m_nWindowLines, 0);
		break;

	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:

		m_nScrollPos = GetTrackPos32(m_hWnd, SB_HORZ);
		RefreshWindow();
		break;
	}

	if(oldpos != m_nScrollPos)
	{
		SetupScrollbars();
		RepositionCaret();
	}

	return 0;
}
VOID MnTextView::MoveWordPrev()
{
	int old = m_nCursorOffset;
	MoveWordStart();
	int i	= 1;
	while(m_nCursorOffset >= old && old > 0 )
	{
		m_nCursorOffset -= i++;
		FilePosToCharPos(m_nCursorOffset, &m_CurrentCharPos);
		MoveWordStart();
	}
	RepositionCaret();
}
VOID MnTextView::MoveWordNext()
{
	int old = m_nCursorOffset;
	MoveWordEnd();
	int en	= m_nCursorOffset;
	if(en <= old)
	{
	
		m_nCursorOffset = min(m_nCursorOffset + 2 , m_pTextDoc->charCount());

		MoveWordStart();
	}

	RepositionCaret();
}
VOID MnTextView::MoveWordStart()
{
	CHAR_POS charPos;
	m_visualLineView.moveToWordStart(m_CurrentCharPos, &charPos);
	CharPosToFilePos(charPos, &m_nCursorOffset);
	m_CurrentCharPos = charPos;
}
VOID MnTextView::MoveWordEnd()
{
	CHAR_POS charPos;
	m_visualLineView.moveToWordEnd(m_CurrentCharPos, &charPos);
	CharPosToFilePos(charPos, &m_nCursorOffset);
	m_CurrentCharPos = charPos;
}
VOID MnTextView::MoveCharPrev(bool bStopTail, bool bUpdateCaretXY )
{
	CHAR_POS prevCp	= m_CurrentCharPos;
	ULONG filepos	= m_nCursorOffset;
	//FilePosToCharPos(m_nCursorOffset + m_nCursorTrailing, &cp);
	if(m_CurrentCharPos.index + m_CurrentCharPos.trailing > 0)
	{
		m_visualLineView.moveToCharPrev(m_CurrentCharPos, &prevCp, bStopTail);
	}
	else if(m_CurrentCharPos.logLine > 0)
	{
		prevCp.logLine  = m_CurrentCharPos.logLine - 1;
		prevCp.index	= m_visualLineView.getCharCount_Without_CRLF(prevCp.logLine);
		prevCp.trailing = 0;
	}
	CharPosToFilePos(prevCp, &filepos);
	m_CurrentCharPos	= prevCp;
	m_nCursorOffset		= filepos;
	m_nCurrentLine_D	= m_CurrentCharPos.logLine;
	if(bUpdateCaretXY)
		updateCaretPos(m_CurrentCharPos);
}
VOID MnTextView::MoveCharNext(bool bStopHead, bool bUpdateCaretXY )
{
	CHAR_POS nextCp	= m_CurrentCharPos;
	ULONG filepos	= m_nCursorOffset;
	//FilePosToCharPos(m_nCursorOffset + m_nCursorTrailing, &cp);
	if(m_CurrentCharPos.index + m_CurrentCharPos.trailing 
		<  m_visualLineView.getCharCount_Without_CRLF(m_CurrentCharPos.logLine))
	{
		m_visualLineView.moveToCharNext(m_CurrentCharPos, &nextCp, bStopHead);
	}
	else if(m_CurrentCharPos.logLine + 1< m_visualLineView.getLogLineCount())
	{
		nextCp.logLine  = m_CurrentCharPos.logLine + 1;
		nextCp.index	= 0;
		nextCp.trailing = 0;
	}
	CharPosToFilePos(nextCp, &filepos);
	m_CurrentCharPos	= nextCp;
	m_nCursorOffset		= filepos;
	m_nCurrentLine_D	= m_CurrentCharPos.logLine;
	if(bUpdateCaretXY)
		updateCaretPos(m_CurrentCharPos);
}
VOID MnTextView::MoveLineUp(int numLines)
{
	CHAR_POS outCp;
	if(m_visualLineView.moveToVLinePrev(m_CurrentCharPos,numLines,&outCp))
	{
		CharPosToFilePos(outCp, &m_nCursorOffset);
		m_CurrentCharPos	= outCp;
		m_nCurrentLine_D	= m_CurrentCharPos.logLine;
		//updateCaretPos(m_CurrentCharPos);
		ScrollToCaret();
		updateCaretPos(m_CurrentCharPos);
	}
}
VOID MnTextView::MoveLineDown(int numLines)
{
	CHAR_POS outCp;
	if(m_visualLineView.moveToVLineNext(m_CurrentCharPos,numLines,&outCp))
	{
		CharPosToFilePos(outCp, &m_nCursorOffset);
		m_CurrentCharPos	= outCp;
		m_nCurrentLine_D	= m_CurrentCharPos.logLine;
		ScrollToCaret();
		updateCaretPos(m_CurrentCharPos);
	}
}
VOID MnTextView::MoveLineStart(ULONG lineNo, bool bUpdateCaret){
	CHAR_POS cp;
	if(m_visualLineView.moveToLineStart(m_CurrentCharPos, &cp))
	{
		m_CurrentCharPos = cp;
		CharPosToFilePos(cp, &m_nCursorOffset);
		if(bUpdateCaret)
			updateCaretPos(m_CurrentCharPos);
	}
}
VOID MnTextView::MoveLineEnd(ULONG lineNo, bool bUpdateCaret )	
{
	CHAR_POS cp;
	if(m_visualLineView.moveToLineEnd(m_CurrentCharPos, &cp))
	{
		m_CurrentCharPos = cp;
		CharPosToFilePos(cp, &m_nCursorOffset);
		if(bUpdateCaret)
			updateCaretPos(m_CurrentCharPos);
	}
}
VOID MnTextView::MovePageUp() 
{
	int oldpos = m_nScrollPos;
	m_nScrollPos -= m_nWindowLines;
	m_nScrollPos = max(m_nScrollPos,0 );
	MoveLineUp(oldpos - m_nScrollPos  );


	SetupScrollbars();
	RefreshWindow();
	updateCaretPos(m_CurrentCharPos);
	NotifyParent(TVN_CURSOR_CHANGE);
}
VOID MnTextView::MovePageDown() 
{
	int oldpos		= m_nScrollPos;
	m_nScrollPos	+= m_nWindowLines;
	m_nScrollPos	= min(m_nScrollPos, m_visualLineView.getVisLineCount() - m_nWindowLines );
	MoveLineDown(m_nScrollPos - oldpos);

	SetupScrollbars();
	RefreshWindow();
	updateCaretPos(m_CurrentCharPos);
	NotifyParent(TVN_CURSOR_CHANGE);
}
LONG MnTextView::OnGetSelText(WCHAR* pBuffer, ULONG bufferLength)
{
	long selStart		= min(m_nSelectionStart, m_nSelectionEnd);
	long selEnd			= max(m_nSelectionStart, m_nSelectionEnd);
	long selLength		= selEnd - selStart;
	ULONG request_length= min(selLength, bufferLength - 1);
	if(selLength > 0 && bufferLength > 0 && pBuffer)
	{
		long start_bytes	= m_pTextDoc->charoffset_to_byteoffset(selStart	);
		long end_bytes		= m_pTextDoc->charoffset_to_byteoffset(selEnd	);
		long length_bytes	= end_bytes - start_bytes;
		if(m_pTextDoc->gettext(start_bytes, length_bytes, pBuffer, &request_length))
		{
			pBuffer[request_length] = '\0';
			return bufferLength;
		}
	}else if(selLength == 0)
	{
		pBuffer[0] = '\0';
	}
	return 0;
}
void MnTextView::ImeSetCompWindowPos()
{
	HIMC hIMC = NULL;
	if (hIMC = ImmGetContext(m_hWnd))
    {
		COMPOSITIONFORM cpf = {0};
		cpf.dwStyle = CFS_POINT;
		//cpf.ptCurrentPos = cdf.ptCurrentPos;
		GetCaretPos(&cpf.ptCurrentPos);
		cpf.ptCurrentPos.x += m_pFontManager->getLineHeight();
		cpf.ptCurrentPos.y -= m_pFontManager->getLineHeight();
		if(cpf.ptCurrentPos.y < 0) cpf.ptCurrentPos.y = 0;
		ImmSetCompositionWindow(hIMC,&cpf);
		OutputDebugString(L"ImeSetCompWindowPos\n");
	}
}
void MnTextView::ImeSetCandWindowPos()
{
	HIMC hIMC = NULL;
	

    m_imeProperty	= ImmGetProperty(GetKeyboardLayout(0), IGP_PROPERTY);
	
    if (hIMC = ImmGetContext(m_hWnd))
    {
        CANDIDATEFORM cdf = {0};

        if (m_imeProperty & IME_PROP_AT_CARET)
        {
            cdf.dwIndex = 0;
            cdf.dwStyle = CFS_CANDIDATEPOS;
            //cdf.ptCurrentPos.x = ptImeUIPos.x;
            //cdf.ptCurrentPos.y = ptImeUIPos.y;
            GetCaretPos(&cdf.ptCurrentPos);
			cdf.ptCurrentPos.x += m_pFontManager->getLineHeight();
			cdf.ptCurrentPos.y -= m_pFontManager->getLineHeight();
        }
        else
        {
            UINT i;

            // The candidate position should be decided by a near caret
            // IME. There are 4 candidate form in the input context

            for (i = 0; i < 4; i++)
            {
                if (!ImmGetCandidateWindow(hIMC, i, &cdf))
                {
                    continue;
                }

                if (cdf.dwStyle == CFS_DEFAULT)
                {
                    continue;
                }

                cdf.dwStyle = CFS_DEFAULT;

                ImmSetCandidateWindow(hIMC, &cdf);
            }

        }

        ImmReleaseContext(m_hWnd, hIMC);
    }
	OutputDebugString(L"ImeSetCandWindowPos\n");
}
HRESULT MnTextView::OnInputLanChange(WPARAM wParam, LPARAM lParam)
{
    OutputDebugString(L"WM_INPUTLANGCHANGE\n");

	ImeSetCompWindowFont();
	ImeSetCompWindowPos();
	ImeSetCandWindowPos();
    return DefWindowProc(m_hWnd, WM_INPUTLANGCHANGE,wParam, lParam);
}
HRESULT MnTextView::OnEndComposition(WPARAM wParam, LPARAM lParam)
{
	return (DefWindowProc(m_hWnd, WM_IME_ENDCOMPOSITION, wParam, lParam));
}
HRESULT MnTextView::OnStartComposition(WPARAM wParam, LPARAM lParam)
{
	ImeSetCompWindowPos();
	return (DefWindowProc(m_hWnd, WM_IME_STARTCOMPOSITION, wParam, lParam));
}
HRESULT MnTextView::OnComposition(WPARAM wParam, LPARAM lParam)
{
	ImeSetCandWindowPos();
	return (DefWindowProc(m_hWnd, WM_IME_COMPOSITION, wParam, lParam));
}
BOOL MnTextView::OnDoStatistic(STATISTIC* stati)
{
	return (BOOL)m_pTextDoc->getStatistic(stati);
}
LONG MnTextView::OnSetResModule(HMODULE hModule)
{
	m_hResModule	= hModule;
	return 0;
}
LONG MnTextView::OnGetTextLen()
{
	return m_pTextDoc->charCount();
}
void MnTextView::OnTesterMode(bool mode)
{
	ClearFile();
	m_pFontManager->setTesterMode(mode);
	m_visualLineView.resetCache();
	m_visualLineView.setLineHeight(m_pFontManager->getLineHeight());
	Smeg(TRUE);
	OnKillFocus(0);
	OnSetFocus(0);
}
void MnTextView::ImeSetCompWindowFont()
{
	HIMC hIMC		= NULL;
	if (hIMC = ImmGetContext(m_hWnd))
	{
		////
		LOGFONT lf;
		HFONT   hFont = m_pFontManager->getFont(0);
		GetObject(hFont, sizeof(lf), &lf);
		if(lf.lfFaceName[0] =='@')
		{
			int i = 1;
			while(lf.lfFaceName[i] != '\0')
			{
				lf.lfFaceName[i-1] = lf.lfFaceName[i];
				i++;
			}
		}
		ImmSetCompositionFont(hIMC, &lf);
		ImmReleaseContext(m_hWnd,hIMC);
	}
	//return 0;

}