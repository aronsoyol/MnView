#include "TextViewBase.h"
#include <richedit.h>

LONG GetTrackPos32(HWND hwnd, int nBar)
{
	SCROLLINFO si = { sizeof(si), SIF_TRACKPOS };
	GetScrollInfo(hwnd, nBar, &si);
	return si.nTrackPos;
}
bool IsKeyPressed(UINT nVirtKey)
{
	return GetKeyState(nVirtKey) < 0 ? true : false;
}
TextViewBase::TextViewBase(HWND hwnd):

	m_hWnd				( hwnd		),
	// Runtime data
	
	m_nEditMode			( MODE_INSERT),
	m_nSelectionMode	( SEL_NONE	),
	m_nSelectionStart	( 0			),
	m_nSelectionEnd		( 0			),
	m_nSelectionType	( SEL_NONE	),
	//m_nCursorOffset		( 0),
	m_nCurrentLine		( 0			),
	m_nCurrentLine_D    ( 0			),
	//m_nScrollPos		( 0			),
	//ime	
	m_imeProperty		( 0			),
	m_bFocused			( false		),
	m_bDrawFocusRect	( true		),
	//
	m_pTextDoc			( 0			),
	m_pFndIterator		( 0			)
{
	m_pTextDoc			= new TextDocument();
	m_pFndIterator		= new FindIterator(m_pTextDoc);
	
	//UpdateMetrics();
}

TextViewBase::~TextViewBase(void)
{
	if(m_pTextDoc)
		delete m_pTextDoc;
	if(m_pFndIterator)
		delete m_pFndIterator;
	//if(hwnd)
}
LONG TextViewBase::OnMouseActivate(HWND hwndTop, UINT nHitTest, UINT nMessage)
{
	SetFocus(m_hWnd);
	return MA_ACTIVATE;
}
bool TextViewBase::HandleWndProc(UINT msg, WPARAM wParam, LPARAM lParam, LONG *pResult)
{
	HIMC hIMC = NULL;
	switch (msg)
	{
		// Draw contents of TextView whenever window needs updating
	case WM_ERASEBKGND:
		*pResult = 1;
		return true;
		// Need to custom-draw the border for XP/Vista themes
	case WM_NCPAINT:
		*pResult = OnNcPaint((HRGN)wParam);
		return true;

	case WM_PAINT:
		*pResult = OnPaint();
		return true;
		// Set a new font 
	case WM_SETFONT:
		*pResult = OnSetFont((HFONT)wParam);
		return true;

	case WM_SIZE:
		*pResult = OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
		return true;

	case WM_VSCROLL:
		*pResult = OnVScroll(LOWORD(wParam), HIWORD(wParam));
		return true;

	case WM_HSCROLL:
		*pResult = OnHScroll(LOWORD(wParam), HIWORD(wParam));
		return true;

	case WM_MOUSEACTIVATE:
		*pResult = OnMouseActivate((HWND)wParam, LOWORD(lParam), HIWORD(lParam));
		return true;

		//case WM_CONTEXTMENU:
		//	return OnContextMenu((HWND)wParam, (short)LOWORD(lParam), (short)HIWORD(lParam));

	case WM_MOUSEWHEEL:
		if (IsKeyPressed(VK_CONTROL))
			return false;
		else
			*pResult = OnMouseWheel((short)HIWORD(wParam));
		return true;

	case WM_SETFOCUS:
		*pResult = OnSetFocus((HWND)wParam);
		return true;

	case WM_KILLFOCUS:
		*pResult = OnKillFocus((HWND)wParam);
		return true;

		// make sure we get arrow-keys, enter, tab, etc when hosted inside a dialog
	case WM_GETDLGCODE:
		*pResult = DLGC_WANTALLKEYS;//DLGC_WANTMESSAGE;//DLGC_WANTARROWS;
		return true;

	case WM_LBUTTONDOWN:
		*pResult = OnLButtonDown(wParam, (short)LOWORD(lParam), (short)HIWORD(lParam));
		return true;

	case WM_LBUTTONUP:
		*pResult = OnLButtonUp(wParam, (short)LOWORD(lParam), (short)HIWORD(lParam));
		return true;

	case WM_LBUTTONDBLCLK:
		*pResult = OnLButtonDblClick(wParam, (short)LOWORD(lParam), (short)HIWORD(lParam));
		return true;

	case WM_RBUTTONDOWN:
		*pResult = OnRButtonDown(wParam, (short)LOWORD(lParam), (short)HIWORD(lParam));
		return true;
	case WM_MOUSEMOVE:
		*pResult = OnMouseMove(wParam, (short)LOWORD(lParam), (short)HIWORD(lParam));
		return true;

	case WM_KEYDOWN:
		*pResult = OnKeyDown(wParam, lParam);
		return true;

	case WM_UNDO: case TXM_UNDO: case EM_UNDO:
		*pResult = Undo();
		return true;

	case TXM_REDO : case EM_REDO:
		*pResult = Redo();
		return true;

	case TXM_CANUNDO: case EM_CANUNDO:
		*pResult = CanUndo();
		return true;

	case TXM_CANREDO: case EM_CANREDO:
		*pResult = CanRedo();
		return true;

	case WM_CHAR:
		OutputDebugString(L"WM_CHAR\n");
		*pResult = OnChar(wParam, lParam);
		return true;

	case WM_SETCURSOR:

		if (LOWORD(lParam) == HTCLIENT)
		{
			*pResult = TRUE;
			return true;
		}
		else
			return false;
	case WM_COPY:
		*pResult = OnCopy();
		return true;

	case WM_CUT:
		*pResult = OnCut();
		return true;

	case WM_PASTE:
		*pResult = OnPaste();
		return true;

	case WM_CLEAR:
		*pResult = OnClear();
		return true;
	
	case WM_GETTEXT:
		*pResult = GetText((WCHAR*)lParam, 0, (ULONG)wParam);
		return true;

	case WM_SETTEXT:
		*pResult = OnSetText((WCHAR*)lParam, lstrlen((WCHAR*)lParam));
		return true;
		//case TXM_SETTEXT:
		//	{
		//		ClearFile();
		//		EnterText((WCHAR*)lParam, (LONG)wParam);
		//		return 0;
		//	}
	case WM_TIMER:
		*pResult = OnTimer(wParam);
		return true;

	case WM_IME_STARTCOMPOSITION:
		OutputDebugString(L"WM_IME_STARTCOMPOSITION\n");
		*pResult = OnStartComposition(wParam, lParam);
		return true;
		//return DefWindowProc(m_hWnd, WM_IME_STARTCOMPOSITION, wParam, lParam);

	case WM_IME_COMPOSITION:
		OutputDebugString(L"WM_IME_COMPOSITION\n");
		*pResult = DefWindowProc(m_hWnd, WM_IME_COMPOSITION, wParam, lParam);
		return true;
		//return OnComposition(wParam, lParam);

	case WM_IME_ENDCOMPOSITION:
		OutputDebugString(L"WM_IME_ENDCOMPOSITION\n");
		*pResult = DefWindowProc(m_hWnd, WM_IME_ENDCOMPOSITION, wParam, lParam);
		return true;
		//return OnEndComposition(wParam, lParam);

	case WM_IME_CHAR:
		OutputDebugString(L"WM_IME_CHAR\n");
		*pResult = DefWindowProc(m_hWnd, WM_IME_CHAR, wParam, lParam);
		return true;

	case WM_IME_CONTROL:
		OutputDebugString(L"WM_IME_CONTROL\n");
		*pResult = DefWindowProc(m_hWnd, WM_IME_CONTROL, wParam, lParam);
		return true;


	case WM_IME_NOTIFY:
		OutputDebugString(L"WM_IME_NOTIFY\n");
		*pResult = DefWindowProc(m_hWnd, WM_IME_NOTIFY, wParam, lParam);
		return true;
		//return HandleImeNotify(wParam, lParam);

	case WM_IME_REQUEST:
		OutputDebugString(L"WM_IME_REQUEST\n");
		*pResult = DefWindowProc(m_hWnd, WM_IME_REQUEST, wParam, lParam);
		return true;
	case WM_INPUTLANGCHANGE:
		*pResult = OnInputLanChange(wParam, lParam);
		return true;

	case TXM_PRINT:
		*pResult = OnPrint((HDC)wParam, (int)lParam);
		return true;

		//
	case TXM_OPENFILE:
		*pResult = OpenFile((TCHAR *)lParam);
		return true;


	case TXM_SAVEFILE:
		*pResult = SaveFile((TCHAR *)lParam);
		return true;

	case TXM_IMPORTFILE:
		*pResult = ImportFile((TCHAR *)lParam, (int)wParam);
		return true;

	case TXM_EXPORTFILE:
	{
		int convertype = LOWORD(wParam);
		int utf_type = HIWORD(wParam);
		*pResult = ExportFile((TCHAR *)lParam, convertype, utf_type);
		return true;
	}

	case TXM_CLEAR:
		*pResult = ClearFile();
		return true;

	case TXM_GETFORMAT:
		*pResult = m_pTextDoc->getformat();
		return true;

	case TXM_SETFORMAT:
		*pResult = m_pTextDoc->setformat((int)wParam);
		return true;

	case TXM_GETSELSIZE:
		*pResult = SelectionSize();
		return true;

	case TXM_SETSELALL:
		*pResult = SelectAll();
		return true;

	case TXM_GETCURPOS:
		*pResult = m_CurrentCharPos.get();
		return true;

	case TXM_GETCURLINE_D:
		*pResult = m_nCurrentLine_D;
		return true;

	case TXM_GETCURLINE_V:
		*pResult = OnGetCurLineV();
		return true;

	case TXM_GETCURCOL:
		*pResult = OnGetCurCol();
		return true;

	case TXM_GETEDITMODE:
		*pResult = m_nEditMode;
		return true;

	case TXM_SETEDITMODE:
		lParam = m_nEditMode;
		m_nEditMode = wParam;
		*pResult = lParam;
		return true;
	case TXM_FIND_INIT:
		FindInitial((WCHAR*)lParam);
		*pResult = 0;
		return true;
	case TXM_FIND:
	{
		BOOL m = (BOOL)LOWORD(wParam);
		BOOL b = (BOOL)HIWORD(wParam);
		//FindText()
		if (b)
			*pResult = FindBackward(m, NULL);
		else
			*pResult = FindForward(m, NULL);
		return true;
	}
	case TXM_FIND_TEXT:
	{
		FIND_OPTION* fp = (FIND_OPTION*)(lParam);
		*pResult = Find_Text(fp->text, lstrlen(fp->text), fp->fBackward, fp->fMachCase, fp->fWarp);
		return true;
	}
	case TXM_REPLACE_TEXT:
	{
		*pResult = Replace_Text((REPLACE_OPTION*)(lParam));
		return true;
	}
	case TXM_SETRESMODULE:
	{
		*pResult = OnSetResModule((HMODULE)lParam);
		return true;
	}
	case WM_GETTEXTLENGTH:
	case TXM_GETTEXTLEN:
	{
		*pResult = OnGetTextLen();
		return true;
	}
	case TXM_REPLACE:
	{
		BOOL ra = (BOOL)LOWORD(wParam);
		WORD mb = (WORD)HIWORD(wParam);
		BOOL m = (BOOL)LOBYTE(mb);
		BOOL b = (BOOL)HIBYTE(mb);
		if (b)
			*pResult = FindBackward(m, (WCHAR*)lParam, ra);
		else
			*pResult = FindForward(m, (WCHAR*)lParam, ra);
		return true;
	}
	case TXM_FIND_GETTEXTLENGTH:
		*pResult = m_pFndIterator->find_text_length();
		return true;
	case TXM_GETSELSTART:
		*pResult = m_nSelectionStart;
		return true;
	case TXM_GETSELEND:
		*pResult = m_nSelectionEnd;
		return true;
	case TXM_GETSELTEXT:
		*pResult = OnGetSelText((WCHAR*)wParam, ULONG(lParam));
		return true;
	case TXM_SETTESTERMODE:
		OnTesterMode((bool)wParam);
		*pResult = 0;
		return true;
	case TXM_SETCONTEXTMENU:
		m_hUserMenu = (HMENU)wParam;
		*pResult = 0;
		return true;
	case TXM_STATISTIC:
		*pResult = OnDoStatistic((STATISTIC*)(lParam));
		return true;
	case TXM_GETCONVERTTYPES:
		*pResult = OnGetConvertTypes((convert_type*)(lParam));
		return true;
	case EM_GETSEL:
		*pResult = OnMsg_EM_GETSEL((ULONG*)wParam, (ULONG*)lParam);
		return true;
	case EM_SETSEL:
		*pResult = OnMsg_EM_SETSEL((LONG)wParam, (LONG)lParam);
		return true;
	default:
		return false;
	}
}
LONG WINAPI TextViewBase::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	LONG result = 0;
	if (HandleWndProc(msg, wParam, lParam, &result))
	{
		return result;
	}else
		return DefWindowProc(m_hWnd, msg, wParam, lParam);
}
//BOOL TextViewBase::OnTestLoadUmuLib()
//{
//	return (BOOL)m_pTextDoc->CanLoadUmuLib();
//}
LONG TextViewBase::OnGetConvertTypes(convert_type* convert_looup)
{
	return (BOOL)m_pTextDoc->GetConvertLookupTable(convert_looup);
}
LONG TextViewBase::OnChar(UINT nChar, UINT nFlags)
{
	WCHAR ch = (WCHAR)nChar;

	if(nChar < 32 && nChar != '\t' && nChar != '\r' && nChar != '\n')
		return 0;

	// change CR into a CR/LF sequence
	if(nChar == '\r')
		PostMessage(m_hWnd, WM_CHAR, '\n', 1);

	if(this->EnterText(&ch, 1))
	{
		if(nChar == '\n')
			m_pTextDoc->m_seq.breakopt();

		NotifyParent(TVN_CHANGED);
	}

	return 0;
}

ULONG TextViewBase::NotifyParent(UINT nNotifyCode, NMHDR *optional)
{
	UINT  nCtrlId = GetWindowLong(m_hWnd, GWL_ID);
	NMHDR nmhdr   = { m_hWnd, nCtrlId, nNotifyCode };
	NMHDR *nmptr  = &nmhdr;  
	
	if(optional)
	{
		nmptr  = optional;
		*nmptr = nmhdr;
	}

	HWND parent = GetParent(m_hWnd);
	SendMessage(m_hWnd, WM_NOTIFY, (WPARAM)nCtrlId, (LPARAM)nmptr);
	return SendMessage(parent, WM_NOTIFY, (WPARAM)nCtrlId, (LPARAM)nmptr);
}
ULONG TextViewBase::SelectionSize()
{
	ULONG s1 = min(m_nSelectionStart, m_nSelectionEnd); 
	ULONG s2 = max(m_nSelectionStart, m_nSelectionEnd); 
	return s2 - s1;
}

ULONG TextViewBase::SelectAll()
{	m_nSelectionStart = 0;
	m_nSelectionEnd   = m_pTextDoc->charCount();
	//m_nCursorOffset   = m_nSelectionEnd;

	//Smeg(TRUE);
	RefreshWindow();
	return 0;
}
//
//	Perform a full redraw of the entire window
//
VOID TextViewBase::RefreshWindow()
{
	InvalidateRect(m_hWnd, NULL, TRUE);
}
BOOL TextViewBase::Undo()
{
	if(m_nEditMode == MODE_READONLY)
		return FALSE;

	if(!m_pTextDoc->Undo(&m_nSelectionStart, &m_nSelectionEnd))
		return FALSE;

	//m_nCursorOffset = m_nSelectionEnd;

	ResetLineCache();
	RefreshWindow();

	Smeg(m_nSelectionStart != m_nSelectionEnd);
	NotifyParent(TVN_CHANGED);
	return TRUE;
}

BOOL TextViewBase::Redo()
{
	if(m_nEditMode == MODE_READONLY)
		return FALSE;

	if(!m_pTextDoc->Redo(&m_nSelectionStart, &m_nSelectionEnd))
		return FALSE;

	//m_nCursorOffset = m_nSelectionEnd;
				
	ResetLineCache();
	RefreshWindow();
	Smeg(m_nSelectionStart != m_nSelectionEnd);
	NotifyParent(TVN_CHANGED);
	return TRUE;
}
BOOL TextViewBase::CanUndo()
{
	return m_pTextDoc->m_seq.canundo() ? TRUE : FALSE;
}

BOOL TextViewBase::CanRedo()
{
	return m_pTextDoc->m_seq.canredo() ? TRUE : FALSE;
}
BOOL TextViewBase::CharPosToFilePos(const CHAR_POS& charPos, ULONG *pnFileOffset)
{
	ULONG	off_chars	;
	UINT	cp			= charPos.get();
	int nLineNo			= charPos.logLine;
	
	// make sure we don't go outside of the document
	if(nLineNo >= m_nLineCount)
	{
		nLineNo   = m_nLineCount ? m_nLineCount - 1 : 0;
		off_chars = m_pTextDoc->charCount();
	}

	TextIterator itor	= m_pTextDoc->iterate_line(nLineNo, &off_chars);
	*pnFileOffset		= cp + off_chars;
	return TRUE;
}

//
//	Convert mouse(client) coordinates to a file-relative offset
//
//	Currently only uses the main font so will not support other
//	fonts introduced by syntax highlighting
//
BOOL TextViewBase::MouseCoordToFilePos(	int		 mx,			// [in]  mouse x-coord
										int		 my,			// [in]  mouse x-coord
										ULONG	*pnLineNo,		// [out] line number
										ULONG	*pnFileOffset,  // [out] zero-based file-offset (in chars)
										int		*psnappedX		// [out] adjusted x coord of caret
										)
{
	/**/
	CHAR_POS charPos;
	MouseCoordToCharPos(mx, my, &charPos,psnappedX);
	CharPosToFilePos(charPos, pnFileOffset);
	*pnLineNo = charPos.logLine;
	return TRUE;
}
BOOL TextViewBase::FilePosToCharPos(const ULONG FileOffset, CHAR_POS* charPos)
{
	ULONG l,i, offset,size;
	size = m_pTextDoc->charCount();
	if(size > 0)
	{
		offset = min(size - 1, FileOffset);
	}else
	{
		offset = 0;
	}
	m_pTextDoc->lineinfo_from_offset(FileOffset, &l, &i, 0, 0, 0);
	if(l >= m_pTextDoc->linecount() && l > 0)
	{
		int stop =1;
	}
	charPos->logLine	= l;
	charPos->index		= FileOffset - i;
	charPos->trailing	= 0;
	return TRUE;
}
BOOL TextViewBase::ForwardDelete()
{

	ULONG selstart	= min(m_nSelectionStart, m_nSelectionEnd);
	ULONG selend	= max(m_nSelectionStart, m_nSelectionEnd);
	ULONG length	= selend - selstart;
	bool  nead_Smeg	= false;

	ULONG line_offset, line_length, line_no;

	m_pTextDoc->lineinfo_from_offset(selstart, &line_no, &line_offset, &line_length,NULL, NULL);

	if(selstart != selend)
	{
		if(selstart + length >= line_length + line_offset)
		{
			nead_Smeg = true;
		}

		m_pTextDoc->erase_text(selstart, length);
		//m_nCursorOffset = selstart;
		m_pTextDoc->m_seq.breakopt();
	}
	else
	{

		ULONG oldpos = m_nSelectionEnd;
		
		MoveCharNext();
		length = m_nSelectionEnd - oldpos;

		m_pTextDoc->erase_text(oldpos, length);
		m_nSelectionEnd = oldpos;
		

		if(oldpos + length >= line_length + line_offset)
		{
			nead_Smeg = true;
		}
		//else
		//	m_pTextDoc->erase_text(m_nCursorOffset, 1);
	}

	m_nSelectionStart = selstart;
	m_nSelectionEnd = selstart;

	FilePosToCharPos(selstart, &m_CurrentCharPos);


	if(nead_Smeg)
	{
		Smeg(FALSE);
	}else
	{
		m_pTextDoc->init_linebuffer();
		if(m_pTextDoc->lineinfo_from_lineno(m_nCurrentLine_D, &line_offset, &line_length ,NULL,NULL))
		{
			ResetLineCache( m_nCurrentLine_D);
			InvalidateRange(min(m_nSelectionEnd - 1, 0), line_offset + line_length);
			RepositionCaret();
		}
		
	}
	
	return TRUE;
}

BOOL TextViewBase::BackDelete()
{
	ULONG selstart	= min(m_nSelectionStart, m_nSelectionEnd);
	ULONG selend	= max(m_nSelectionStart, m_nSelectionEnd);
	ULONG length	= selend - selstart;
	bool  nead_Smeg	= false;

	ULONG line_offset, line_length, line_no;

	m_pTextDoc->lineinfo_from_offset(selstart, &line_no, &line_offset, &line_length, NULL, NULL);
	//m_pTextDoc->lineinfo_from_lineno(m_nCurrentLine_D, &line_offset, &line_length, NULL, NULL);
		
	// if there's a selection then delete it
	if(selstart != selend)
	{
		if(selstart + length >= line_length + line_offset)
		{
			nead_Smeg = true;
		}

		m_pTextDoc->erase_text(selstart, selend-selstart);
		m_nSelectionEnd = selstart;
		m_pTextDoc->m_seq.breakopt();
	}
	// otherwise do a back-delete
	else if (m_nSelectionEnd > 0)
	{
		//m_nCursorOffset--;
		ULONG oldpos = m_nSelectionEnd;
		MoveCharPrev();
		length = oldpos - m_nSelectionEnd;

		if (m_nSelectionEnd < line_offset)
		{
			nead_Smeg = true;
		}
		m_pTextDoc->erase_text(m_nSelectionEnd, length);
	}

	m_nSelectionStart = m_nSelectionEnd;
	//m_nSelectionEnd   = m_nCursorOffset;

	//FilePosToCharPos(m_nCursorOffset, &m_CurrentCharPos);

	if(nead_Smeg)
	{
		Smeg(FALSE);
	}else
	{
		int		old_offset = m_nSelectionEnd;

		m_pTextDoc->init_linebuffer();
		ResetLineCache( m_nCurrentLine_D);
	
		//FilePosToCharPos(m_nCursorOffset, &m_CurrentCharPos);

		MoveLineStart(0, false);
		InvalidateRange((m_nSelectionEnd ? m_nSelectionEnd - 1 : 0), line_offset + line_length);
		m_nSelectionEnd = old_offset;
		RepositionCaret();
		
		
	}
#ifdef _DEBUG
	wchar_t db_string[200];
	wsprintf(db_string, L"m_nSelectionEnd=%d\n", m_nSelectionEnd);
	OutputDebugString(db_string);
#endif
	return TRUE;
}

//
//	Move to start of file
//
VOID TextViewBase::MoveFileStart()
{
	m_nSelectionEnd = 0;
	RepositionCaret();
	ScrollToCaret();
}

//
//	Move to end of file
//
VOID TextViewBase::MoveFileEnd()
{
	m_nSelectionEnd = m_pTextDoc->charCount();
	RepositionCaret();
	ScrollToCaret();
}

//
//	TextView::EnterText
//
//	Import the specified text into the TextView at the current
//	cursor position, replacing any text-selection in the process
//
ULONG TextViewBase::EnterText(const TCHAR *szText, ULONG nLength)
{
#ifdef _DEBUG
	wchar_t db_string[200];
	wsprintf(db_string, L"EnterText  m_nSelectionEnd=%d\n", m_nSelectionEnd);
	OutputDebugString(db_string);
#endif
	ULONG selstart	= min(m_nSelectionStart, m_nSelectionEnd);
	ULONG selend	= max(m_nSelectionStart, m_nSelectionEnd);

	BOOL  fReplaceSelection = (selstart == selend) ? FALSE : TRUE;
	ULONG erase_len			= nLength;
	ULONG line_offset		= 0, line_length = 0;
	bool		result		= m_pTextDoc->lineinfo_from_lineno(m_nCurrentLine_D, &line_offset, &line_length, NULL, NULL);
	if(m_nCurrentLine_D != 0 && !result)
	{
		int stop = 1;
		throw MnException();
	}

	switch(m_nEditMode)
	{
	case MODE_READONLY:
		return 0;

	case MODE_INSERT:

		// if there is a selection then remove it
		if(fReplaceSelection)
		{
			// group this erase with the insert/replace operation
			m_pTextDoc->m_seq.group();
			m_pTextDoc->erase_text(selstart, selend-selstart);
			m_nSelectionEnd = selstart;
		}

		if(!m_pTextDoc->insert_text(m_nSelectionEnd, szText, nLength))
			return 0;

		if(fReplaceSelection)
			m_pTextDoc->m_seq.ungroup();
	
		break;

	case MODE_OVERWRITE:

		if(fReplaceSelection)
		{
			erase_len = selend - selstart;
			m_nSelectionEnd = selstart;
		}
		else
		{
			//ULONG lastPosition;

			ULONG lineoff;
			ULONG length_CRLF;
			/*
			USPCACHE *uspCache	= GetUspCache(0, m_nCurrentLine, &lineoff);*/
			GetOffsetAndLength_CRLF( m_nCurrentLine_D, &lineoff, &length_CRLF);


			// single-character overwrite - must behave like 'forward delete'
			// and remove a whole character-cluster (i.e. maybe more than 1 char)
			if(nLength == 1)
			{
				ULONG oldpos = m_nSelectionEnd;
				MoveCharNext();
				erase_len = m_nSelectionEnd - oldpos;
				m_nSelectionEnd = oldpos;
			}

			// if we are at the end of a line (just before the CRLF) then we must
			// not erase any text - instead we act like a regular insertion
			if (m_nSelectionEnd == lineoff + length_CRLF)
				erase_len = 0;

			
		}

		if(!m_pTextDoc->replace_text(m_nSelectionEnd, szText, nLength, erase_len))
			return 0;
		
		break;

	default:
		return 0;
	}

	// update cursor+selection positions
	m_nSelectionEnd += nLength;
	m_nSelectionStart = m_nSelectionEnd;
	//m_nSelectionEnd   = m_nCursorOffset;
	

	// we altered the document, recalculate line+scrollbar information

	

	//RefreshWindow();
	
	int a1 = '\n';
	int a2 = '\r';
	//ULONG offset, len;
	

	if(nLength == 1 && !fReplaceSelection &&  line_length < MAX_LINE_LENGTH - 1)
	{
		
		FilePosToCharPos(m_nSelectionEnd, &m_CurrentCharPos);
		if(szText[0] =='\n' )
		{
			wchar_t debug[50];
			wsprintf(debug, L"newline m_nCursorOffset%d", m_nSelectionEnd);
			OutputDebugString(debug);
			Smeg(TRUE);
		}
		else if(szText[0] =='\r') 
		{

		}
		else
		{
			m_pTextDoc->init_linebuffer();

			ResetLineCache( m_nCurrentLine_D);
			InvalidateRange(m_nSelectionEnd - 1, line_offset + line_length + 1);
			RepositionCaret();

		}
	}else
	{
		//ResetLineCache( );
		Smeg(TRUE);
	}
	
	NotifyParent(TVN_CURSOR_CHANGE);

	return nLength;
}

LONG TextViewBase::OnSetFocus(HWND hwndOld)
{
	//CreateCaret(m_hWnd, (HBITMAP)NULL, m_nCaretWidth, m_nLineHeight);
	m_bFocused = true;
	CreateMyCaret();
	RepositionCaret();

	ShowCaret(m_hWnd);
	RefreshWindow();
	return 0;
}
LONG TextViewBase::OnKillFocus(HWND hwndNew)
{
	// if we are making a selection when we lost focus then
	// stop the selection logic
	OutputDebugString(L"OnKillFocus\n");
	//RECT cliRect;//, zeroRect = {0,0,0,0};
	//GetClientRect(this->m_hWnd, &cliRect);
	//HBRUSH brush = CreateSolidBrush(m_colba);
	//FillRect(m_hWnd, & cliRect, );
	m_bFocused = false;
	if(m_nSelectionMode != SEL_NONE)
	{
		OnLButtonUp(0, 0, 0);
	}

	HideCaret(m_hWnd);
	DestroyCaret();
	RefreshWindow();
	return 0;
}


LONG TextViewBase::OnLButtonDblClick(UINT nFlags, int mx, int my)
{
	// remove any existing selection
	InvalidateRange(m_nSelectionStart, m_nSelectionEnd);


	ULONG lineno, fileoff;
	int   xpos;

	// map the mouse-coordinates to a real file-offset-coordinate
	MouseCoordToFilePos(mx, my, &lineno, &fileoff, &xpos);
	//m_nAnchorPosX = m_nCaretPosX;

	// move selection-start to start of word
	MoveWordStart();
	m_nSelectionStart = m_nSelectionEnd;// m_nCursorOffset;

	// move selection-end to end of word
	MoveWordEnd();
	//m_nSelectionEnd = m_nCursorOffset;

	// update caret position
	InvalidateRange(m_nSelectionStart, m_nSelectionEnd);
	//UpdateCaretOffset(m_nCursorOffset, TRUE, &m_nCaretPosX, &m_nCurrentLine);
	//m_nAnchorPosX = m_nCaretPosX;
	RepositionCaret();

	NotifyParent(TVN_CURSOR_CHANGE);
	NotifyParent(TVN_SELECTION_CHANGED);

	return 0;
}
//
//	Process keyboard-navigation keys
//
LONG TextViewBase::OnKeyDown(UINT nKeyCode, UINT nFlags)
{
	bool fCtrlDown	= IsKeyPressed(VK_CONTROL);
	bool fShiftDown	= IsKeyPressed(VK_SHIFT);
	BOOL fAdvancing = FALSE;
	long oldCursorOffset = m_nSelectionEnd;
	//
	//	Process the key-press. Cursor movement is different depending
	//	on if <ctrl> is held down or not, so act accordingly
	//
	switch(nKeyCode)
	{
	case VK_SHIFT: case VK_CONTROL:
		return 0;

	case 'a': case 'A':
		
		{
			if(fCtrlDown)
				SelectAll();
		}
		return 0;
	// CTRL+Z undo
	case 'z': case 'Z':
		
		if(fCtrlDown && Undo())
			/*NotifyParent(TVN_CHANGED);*/

		return 0;

	// CTRL+Y redo
	case 'y': case 'Y':
		
		if(fCtrlDown && Redo()) 
			//NotifyParent(TVN_CHANGED);

		return 0;
	// CTRL+C copy
	case 'c': case 'C':
	{
		//if(fCtrlDown && Redo()) 
		//	NotifyParent(TVN_CHANGED);
		if(fCtrlDown)
			return OnCopy();
		else
			break;
	}

	case 'x': case 'X':
		{
		if(fCtrlDown)
			return OnCut();
		else
			break;
		}
	case 'v': case 'V':
		{
		if(fCtrlDown)
			return OnPaste();
		else
			break;
		}

	
	// Change insert mode / clipboard copy&paste
	case VK_INSERT:

		if(fCtrlDown)
		{
			OnCopy();
			NotifyParent(TVN_CHANGED);
		}
		else if(fShiftDown)
		{
			OnPaste();
			NotifyParent(TVN_CHANGED);
		}
		else
		{
			if(m_nEditMode == MODE_INSERT)
				m_nEditMode = MODE_OVERWRITE;

			else if(m_nEditMode == MODE_OVERWRITE)
				m_nEditMode = MODE_INSERT;

			NotifyParent(TVN_EDITMODE_CHANGE);
		}

		return 0;

	case VK_DELETE:

		if(m_nEditMode != MODE_READONLY)
		{
			if(fShiftDown)
				OnCut();
			else
				ForwardDelete();

			NotifyParent(TVN_CHANGED);
		}
		return 0;

	case VK_BACK:

		if(m_nEditMode != MODE_READONLY)
		{
			BackDelete();
			fAdvancing = FALSE;

			NotifyParent(TVN_CHANGED);
		}
		return 0;

	case VK_LEFT:

		if(fCtrlDown)	MoveWordPrev();
		else			MoveCharPrev();

		fAdvancing = FALSE;
		break;

	case VK_RIGHT:
		
		if(fCtrlDown)	MoveWordNext();
		else			MoveCharNext();
			
		fAdvancing = TRUE;
		break;

	case VK_UP:
		if(fCtrlDown)	Scroll(0, -1);
		else			MoveLineUp(1);
		break;

	case VK_DOWN:
		if(fCtrlDown)	Scroll(0, 1);
		else			MoveLineDown(1);
		break;

	case VK_PRIOR:
		if(!fCtrlDown)	MovePageUp();
		break;

	case VK_NEXT:
		if(!fCtrlDown)	MovePageDown();
		break;

	case VK_HOME:
		if(fCtrlDown)	MoveFileStart();
		else			MoveLineStart(m_nCurrentLine);
		break;

	case VK_END:
		if(fCtrlDown)	MoveFileEnd();
		else			MoveLineEnd(m_nCurrentLine);
		break;

	default:
		return 0;
	}

	// Extend selection if <shift> is down
	if(fShiftDown)
	{		
		InvalidateRange(m_nSelectionEnd, oldCursorOffset);
		//m_nSelectionEnd	= m_nCursorOffset;
	}
	// Otherwise clear the selection
	else
	{
		if(m_nSelectionStart != m_nSelectionEnd)
			InvalidateRange(m_nSelectionStart, m_nSelectionEnd);

		//m_nSelectionEnd		= m_nCursorOffset;
		m_nSelectionStart = m_nSelectionEnd;
	}

	// update caret-location (xpos, line#) from the offset
	//UpdateCaretOffset(m_nCursorOffset, fAdvancing, &m_nCaretPosX, &m_nCurrentLine);
	CHAR_POS cp;
	FilePosToCharPos(m_nSelectionEnd, &cp);
	m_nCurrentLine_D = cp.logLine;
	
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
BOOL TextViewBase::isMultiLine(WCHAR *pText, UINT nLength)
{
	for(int i = 0; i < nLength; i++)
	{
		if(pText[i] == '\r'
		|| pText[i] == '\n'
		|| pText[i] == '\x0b'
		|| pText[i] == '\x0c'
		|| pText[i] == 0x2028
		|| pText[i] == 0x2029
		)
			return TRUE;
	}
	return FALSE;
}
LRESULT TextViewBase::HandleImeNotify(WPARAM wParam, LPARAM lParam)
{
    HIMC hIMC = NULL;
    BOOL fOpen = FALSE;
    //DWORD dwConvMode, dwSentMode;


    switch (wParam)
    {
        //case IMN_OPENSTATUSWINDOW: /* fall-through */
        //case IMN_CLOSESTATUSWINDOW:
        //    break;

        //case IMN_SETOPENSTATUS:
        //    SetStatusItems(hWnd);

        //    hIMC = ImmGetContext(hWnd);
        //    fOpen = ImmGetOpenStatus(hIMC);
        //    UpdateShowOpenStatusButton(fOpen);

        //    ImmReleaseContext(hWnd,hIMC);
        //    break;

        //case IMN_SETCONVERSIONMODE:
        //    hIMC = ImmGetContext(hWnd);
        //    fOpen = ImmGetOpenStatus(hIMC);
        //    ImmGetConversionStatus(hIMC,&dwConvMode,&dwSentMode);
        //    if (fOpen)
        //    {
        //        SetConvModeParts(dwConvMode);
        //        UpdateModeButton(dwConvMode);
        //    }
        //    else
        //    {
        //        ClearConvModeParts();
        //    }
        //    ImmReleaseContext(hWnd,hIMC);
        //    break;

        case IMN_OPENCANDIDATE:
            if (/*!fShowCand || */(lParam != 0x01))
            {
                if (m_imeProperty & IME_PROP_SPECIAL_UI)
                {
                    // Normally, we only need to set the composition window
                    // position for a special UI IME
                }
                else if (m_imeProperty & IME_PROP_AT_CARET)
                {
                    CANDIDATEFORM cdf;
                    HIMC          hIMC;
 
                    hIMC = ImmGetContext(m_hWnd);

                    cdf.dwIndex = 0;
                    cdf.dwStyle = CFS_CANDIDATEPOS;
                    /*cdf.ptCurrentPos.x = ptImeUIPos.x;
                    cdf.ptCurrentPos.y = ptImeUIPos.y;*/
					GetCaretPos(&cdf.ptCurrentPos);
                    ImmSetCandidateWindow(hIMC,&cdf);
					OutputDebugString(L"set comp window \n");

                    ImmReleaseContext(m_hWnd, hIMC);
                }
                else
                {
                    // Normally, we only need to set the composition window
                    // position for a near caret IME
                }

                return (DefWindowProc(m_hWnd, WM_IME_NOTIFY, wParam, lParam));
            }

        /*case IMN_CHANGECANDIDATE:

#ifdef _DEBUG
            {
                TCHAR szDev[80];
                DWORD dwSize;
                LPCANDIDATELIST lpC;

                hIMC = ImmGetContext(hWnd);
                if (dwSize = ImmGetCandidateList(hIMC,0x0,NULL,0))
                {
                    lpC = (LPCANDIDATELIST)GlobalAlloc(GPTR,dwSize);
                   
                    ImmGetCandidateList(hIMC,0x0,lpC,dwSize);

                    OutputDebugString(TEXT("DumpCandList!!!\r\n"));
                    StringCchPrintf((LPTSTR)szDev,ARRAYSIZE(szDev),TEXT("dwCount %d\r\n"),lpC->dwCount);
                    OutputDebugString((LPTSTR)szDev);
                    StringCchPrintf((LPTSTR)szDev,ARRAYSIZE(szDev),TEXT("dwSelection %d\r\n"),lpC->dwSelection);
                    OutputDebugString((LPTSTR)szDev);
                    StringCchPrintf((LPTSTR)szDev,ARRAYSIZE(szDev),TEXT("dwPageStart %d\r\n"),lpC->dwPageStart);
                    OutputDebugString((LPTSTR)szDev);
                    StringCchPrintf((LPTSTR)szDev,ARRAYSIZE(szDev),TEXT("dwPageSize %d\r\n"),lpC->dwPageSize);
                    OutputDebugString((LPTSTR)szDev);
                    GlobalFree((HANDLE)lpC);
                }
            }
#endif
            if (fShowCand && (lParam == 0x01))
            {
                DWORD dwSize;

                if (!lpCandList)
                    lpCandList = (LPCANDIDATELIST)GlobalAlloc(GPTR,sizeof(CANDIDATELIST));

                hIMC = ImmGetContext(hWnd);
                if (dwSize = ImmGetCandidateList(hIMC,0x0,NULL,0))
                {
                    GlobalFree((HANDLE)lpCandList);
                    lpCandList = (LPCANDIDATELIST)GlobalAlloc(GPTR,dwSize);
                   
                    ImmGetCandidateList(hIMC,0x0,lpCandList,dwSize);
                }
                else
                {
                    memset(lpCandList, 0, sizeof(CANDIDATELIST));
                }

                InvalidateRect(hWndCandList,NULL,TRUE);
                UpdateWindow(hWndCandList);
                    

                ImmReleaseContext(hWnd,hIMC);
            }
            else
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            break;

        case IMN_CLOSECANDIDATE:
            if (fShowCand && (lParam == 0x01))
            {
                if (!lpCandList)
                {
                    lpCandList = (LPCANDIDATELIST)GlobalAlloc(GPTR,sizeof(CANDIDATELIST));
                }

                memset(lpCandList, 0, sizeof(CANDIDATELIST));
                InvalidateRect(hWndCandList,NULL,TRUE);
                UpdateWindow(hWndCandList);
            }
            else
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            break;


       default:
            return (DefWindowProc(hWnd, message, wParam, lParam));
    }*/
			}

		return 0;
}
	//
	//	Retrieve the specified range of text and copy it to supplied buffer
	//	szDest must be big enough to hold nLength characters
	//	nLength includes the terminating NULL
	//
ULONG TextViewBase::GetText(wchar_t *szDest, ULONG nStartOffset, ULONG nLength)
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
void TextViewBase::SetProperty_DrawFocusRect(bool value)
{
	m_bDrawFocusRect = value;
}
bool TextViewBase::GetProperty_DrawFocusRect(void)
{
	return m_bDrawFocusRect;

}
HWND TextViewBase::GetHwnd()
{
	return m_hWnd;
}
VOID TextViewBase::SetHwnd(HWND hWnd)
{
	m_hWnd = hWnd;
}