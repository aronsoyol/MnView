#pragma once
#include <Windows.h>
#include "TextDocument.h"
#include "textview.h"
#include "../MyLib/MyLib.h"
#include "../MyLib/MnException.h"

//
//	TextView edit modes
//
#define MODE_READONLY	0
#define MODE_INSERT		1
#define MODE_OVERWRITE	2

//typedef struct _TVPRINTINFO
//{
//	int			textSizePoint;
//	LPCWSTR*   	pDocName;
//	DOCINFO		di;
//} TVPRINTINFO;

//
//	TextView Window Messages defined here
//
//#define TXM_BASE				(WM_USER)
//#define TXM_OPENFILE			(TXM_BASE + 0 )
//#define TXM_CLEAR				(TXM_BASE + 1 )
//#define TXM_SETLINESPACING		(TXM_BASE + 2 )
//#define TXM_ADDFONT				(TXM_BASE + 3 )
//#define TXM_SETCOLOR			(TXM_BASE + 4 )
//#define TXM_GETCOLOR			(TXM_BASE + 5 )
//#define TXM_SETSTYLE			(TXM_BASE + 6 )
//#define TXM_GETSTYLE			(TXM_BASE + 7 )
//#define TXM_SETCARETWIDTH		(TXM_BASE + 8 )
//#define TXM_SETIMAGELIST		(TXM_BASE + 9 )
//#define TXM_SETLONGLINE			(TXM_BASE + 10)
//#define TXM_SETLINEIMAGE		(TXM_BASE + 11)
//#define TXM_GETFORMAT			(TXM_BASE + 12)
//#define TXM_UNDO				(TXM_BASE + 13)
//#define TXM_REDO				(TXM_BASE + 14)
//#define TXM_CANUNDO				(TXM_BASE + 15)
//#define TXM_CANREDO				(TXM_BASE + 16)
//#define TXM_GETSELSIZE			(TXM_BASE + 17)
//#define TXM_SETSELALL			(TXM_BASE + 18)
//#define TXM_GETCURPOS			(TXM_BASE + 19)
//#define TXM_GETCURLINE			(TXM_BASE + 20)
//#define TXM_GETCURCOL			(TXM_BASE + 21)
//#define TXM_SETEDITMODE			(TXM_BASE + 22)
//#define TXM_GETEDITMODE			(TXM_BASE + 23)
//#define TXM_SETCONTEXTMENU		(TXM_BASE + 24)
//#define TXM_SAVEFILE			(TXM_BASE + 25)
//#define TXM_SETFONTFACE			(TXM_BASE + 26)
//#define TXM_GETCURLINE_D		(TXM_BASE + 27)
//#define TXM_GETCURLINE_V		(TXM_BASE + 28)
//#define TXM_PRINT				(TXM_BASE + 29)
//#define TXM_FIND_INIT			(TXM_BASE + 30)
//#define TXM_FIND_GETTEXTLENGTH	(TXM_BASE + 31)
//#define TXM_FIND				(TXM_BASE + 33)
//#define TXM_REPLACE				(TXM_BASE + 34)
//#define TXM_GETSELTEXT			(TXM_BASE + 35)
//#define TXM_GETSELSTART			(TXM_BASE + 36)
//#define TXM_GETSELEND			(TXM_BASE + 37)
////
////	TextView Notification Messages defined here - 
////	sent via the WM_NOTIFY message
////
//#define TVN_BASE				(WM_USER)
//#define TVN_CURSOR_CHANGE		(TVN_BASE + 0)
//#define TVN_SELECTION_CHANGE	(TVN_BASE + 1)
//#define TVN_EDITMODE_CHANGE		(TVN_BASE + 2)
//#define TVN_CHANGED				(TVN_BASE + 3)
//#define TVN_CHANGING			(TVN_BASE + 4)

enum SELMODE { SEL_NONE, SEL_NORMAL, SEL_MARGIN, SEL_BLOCK };
LONG GetTrackPos32(HWND hwnd, int nBar);
bool IsKeyPressed(UINT nVirtKey);
//{
//	SCROLLINFO si = { sizeof(si), SIF_TRACKPOS }; 
//	GetScrollInfo(hwnd, nBar, &si);
//	return si.nTrackPos;
//}

class TextViewBase
{
private:
		// Scrollbar-related data
	ULONG		m_nVScrollPos;
	ULONG		m_nVScrollMax;
	int			m_nHScrollPos;
	int			m_nHScrollMax;
protected:
	HWND			m_hWnd;
	TextDocument*	m_pTextDoc;
	FindIterator*	m_pFndIterator;


	// Cursor/Caret position 
	ULONG		m_nCurrentLine;
	ULONG		m_nCurrentLine_D;
	ULONG		m_nSelectionStart;
	ULONG		m_nSelectionEnd;
	ULONG		m_nCursorOffset;
	CHAR_POS	m_CurrentCharPos;


	int			m_nWindowLines;

	SELMODE		m_nSelectionMode;
	SELMODE		m_nSelectionType;
	//CURPOS		m_cpBlockStart;
	//CURPOS		m_cpBlockEnd;
	UINT		m_nEditMode;

	// File-related data
	ULONG		m_nLineCount;

	//IME-related date
	DWORD		m_imeProperty;
	

	HMENU		m_hUserMenu;
	
public:
	TextViewBase(HWND hwnd);
	virtual ~TextViewBase(void);
	virtual LONG WINAPI WndProc(UINT msg, WPARAM wParam, LPARAM lParam);
protected:

	//
	//	Message handlers
	//
	virtual LONG OnPaint()									= 0;
	virtual LONG OnNcPaint(HRGN hrgnUpdate)					= 0;
	virtual LONG OnSetFont(HFONT hFont)						= 0;
	virtual LONG OnSetFont(WCHAR* fontName)					= 0;
	virtual LONG OnSize(UINT nFlags, int width, int height) = 0;
	virtual LONG OnVScroll(UINT nSBCode, UINT nPos)			= 0;
	virtual LONG OnHScroll(UINT nSBCode, UINT nPos)			= 0;
	virtual LONG OnMouseWheel(int nDelta)					= 0;
	virtual LONG OnTimer(UINT nTimer)						= 0;

	//virtual LONG OnPrint(HDC printDC, UINT width, UINT height)	= 0;

	//virtual LONG OnPrint(HDC printDC, TVPRINTINFO* pPrintInfo)	= 0;
	virtual LONG OnPrint(HDC printDC, int fontSizePoint)		= 0;
	virtual LONG OnMouseActivate(HWND hwndTop, UINT nHitTest, 
		UINT nMessage)											;
	virtual LONG OnContextMenu(HWND wParam, int x, int y)		= 0;

	virtual LONG OnLButtonDown(UINT nFlags, int x, int y)		= 0;
	virtual LONG OnRButtonDown(UINT nFlags, int x, int y)		= 0;
	virtual LONG OnLButtonUp(UINT nFlags, int x, int y)			= 0;
	virtual LONG OnLButtonDblClick(UINT nFlags, int x, int y)	;
	virtual LONG OnMouseMove(UINT nFlags, int x, int y)			= 0;

	virtual LONG OnKeyDown(UINT nKeyCode, UINT nFlags)		;
	virtual LONG OnChar(UINT nChar, UINT nFlags)			;

	virtual LONG OnSetFocus(HWND hwndOld)			;
	virtual LONG OnKillFocus(HWND hwndNew)			;

	virtual BOOL OnCut()							;
	virtual BOOL OnCopy()							;
	virtual BOOL OnPaste()							;
	virtual BOOL OnClear()							;

	virtual	LONG OnGetCurCol()						= 0 ;
	virtual	LONG OnGetCurLineV()					= 0 ;
	virtual	LONG OnGetCurLineD()					= 0 ;
	virtual LONG OnGetSelText(WCHAR* pBuffer, ULONG bufferLength) = 0;
	//
	//	Internal private functions
	//
	virtual LONG		OpenFile(TCHAR *szFileName)					= 0;
	virtual LONG		OnSetText(WCHAR* buffer, ULONG length)		= 0;
	//virtual LONG		OnGetText(WCHAR* buffer, ULONG length)		= 0;
	virtual LONG		SaveFile(TCHAR *szFileName)	
	{
		return m_pTextDoc->save(szFileName);
	}

	virtual LONG		ImportFile(WCHAR *szFileName, int conver_type) =0 ;
	virtual LONG		ExportFile(WCHAR *szFileName, int conver_type, int utf_type){return m_pTextDoc->save(szFileName, conver_type, utf_type);}
	virtual LONG		ClearFile()					= 0;
	virtual void		ResetLineCache()			= 0;
	virtual void		ResetLineCache(ULONG line)	{};
	virtual ULONG		GetText(TCHAR *szDest, ULONG nStartOffset, ULONG nLength) ;
	
	//
	//	Cursor/Selection
	//
	virtual ULONG		SelectionSize()	;
	virtual ULONG		SelectAll()		;

	//void		Toggle


	//
	//	Painting support
	//
	virtual void		RefreshWindow()	;
	//virtual void		PaintLine(HDC hdc, ULONG line, int x, int y, HRGN hrgnUpdate)	= 0;
	//virtual void		PaintText(HDC hdc, ULONG nLineNo, int x, int y, RECT *bounds)	= 0;
	//virtual int		PaintMargin(HDC hdc, ULONG line, int x, int y)					= 0;

	virtual LONG		InvalidateRange(ULONG nStart, ULONG nFinish)	= 0;
	//virtual LONG		InvalidateLine(ULONG nLineNo, bool forceAnalysis)	= 0;
	virtual VOID		UpdateLine(ULONG nLineNo)						= 0;


	//
	//	Caret/Cursor positioning
	//
	virtual BOOL		CreateMyCaret() = 0;
	virtual BOOL		MouseCoordToFilePos(int x, int y, ULONG *pnLineNo, ULONG *pnFileOffset, int *px);
	virtual BOOL		MouseCoordToCharPos(int x, int y,__out CHAR_POS* charPos, int *px =NULL)			= 0;
	virtual BOOL		CharPosToFilePos(__in const CHAR_POS& charPos, __out ULONG *pnFileOffset);
	virtual	BOOL		FilePosToCharPos(__in const ULONG FileOffset, __out  CHAR_POS* charPos);
	virtual VOID		RepositionCaret()																	= 0;
	//virtual VOID		UpdateCaretXY(int x, ULONG visLineNo)												= 0;
	//virtual VOID		UpdateCaretOffset(ULONG offset, BOOL fTrailing, int *outx=0, ULONG *outlineno=0)	= 0;
	virtual VOID		Smeg(BOOL fAdvancing)	= 0;

	virtual VOID		MoveWordPrev()	= 0;
	virtual VOID		MoveWordNext()	= 0;
	virtual VOID		MoveWordStart()	= 0;
	virtual VOID		MoveWordEnd()	= 0;
	virtual VOID		MoveCharPrev(bool bStopTail = false, bool bUpdateCaretXY = false)	= 0;
	virtual VOID		MoveCharNext(bool bStopHead = false, bool bUpdateCaretXY = false)	= 0;
	virtual VOID		MoveLineUp(int numLines)	= 0;
	virtual VOID		MoveLineDown(int numLines)	= 0;
	virtual VOID		MovePageUp() 	= 0;
	virtual VOID		MovePageDown() 	= 0;
	virtual VOID		MoveLineStart(ULONG lineNo, bool bUpdateCaret = true)	= 0;
	virtual VOID		MoveLineEnd(ULONG lineNo,   bool bUpdateCaret = true)	= 0;
	virtual VOID		MoveFileStart()	;
	virtual VOID		MoveFileEnd()	;
	//
	//	Editing
	//	
	virtual BOOL		Undo()			;
	virtual BOOL		Redo()			;
	virtual BOOL		CanUndo()		;
	virtual BOOL		CanRedo()		;
	virtual BOOL		ForwardDelete() ;
	virtual BOOL		BackDelete()	;
	virtual ULONG		EnterText(const TCHAR *szText, ULONG nLength) ;
	//
	//	Search
	//
	virtual void		FindInitial (const WCHAR *find_text)	= 0;
	//virtual LONG		FindForward (const WCHAR *find_text, BOOL bMatchcase, BOOL bRepalce)	= 0;
	//virtual LONG		FindBackward(const WCHAR *find_text, BOOL bMatchcase, BOOL bRepalce)	= 0;
	virtual LONG		FindForward (BOOL bMatchcase, const WCHAR *pReplaceText, BOOL bReplaceAll	= FALSE)	= 0;
	virtual LONG		FindForward2 (BOOL bMatchcase, const WCHAR *pReplaceText, BOOL bReplaceAll = FALSE)		= 0;
	virtual LONG		Find_Text(const WCHAR *pFindText, ULONG length, BOOL bBack = 0, BOOL bMatchCase = 0, BOOL bWrap = 0, BOOL bSelFound = TRUE)	= 0;
	virtual LONG		Replace_Text(const REPLACE_OPTION *pOption)	= 0;
	virtual LONG		FindBackward(BOOL bMatchcase, const WCHAR *pReplaceText, BOOL bReplaceAll	= FALSE)	= 0;
	//
	//	Scrolling
	//
	virtual HRGN		ScrollRgn(int dx, int dy, bool fReturnUpdateRgn) = 0;
	virtual void		Scroll(int dx, int dy)	= 0;
	virtual void		ScrollToCaret()			= 0;
	virtual void		ScrollToPosition(int xpos, ULONG lineno) = 0;
	virtual VOID		SetupScrollbars()		= 0;
	virtual VOID		UpdateMetrics()			= 0;
	virtual VOID		RecalcLineHeight()		= 0;
	virtual bool		PinToBottomCorner()		= 0;


	//
	//	Miscallaneous
	//
	//virtual HMENU		CreateContextMenu()	= 0;
	virtual ULONG		NotifyParent(UINT nNotifyCode, NMHDR *optional = 0);



	//
	virtual	BOOL		ValidatePoint(int x, int y)	= 0;
	virtual	BOOL		GetOffsetAndLength_CRLF(ULONG line, __out ULONG* lineOffset, ULONG *length_CRLF) = 0;
	virtual BOOL		isMultiLine(WCHAR *pText, UINT nLength);

	virtual HRESULT		OnStartComposition(WPARAM wParam, LPARAM lParam)	= 0;
	virtual HRESULT		OnComposition(WPARAM wParam, LPARAM lParam)			= 0;
	virtual HRESULT		OnEndComposition(WPARAM wParam, LPARAM lParam)		= 0;
	virtual LRESULT		HandleImeNotify(WPARAM wParam, LPARAM lParam);
	virtual HRESULT		OnInputLanChange(WPARAM wParam, LPARAM lParam)		= 0;
	virtual void		ImeSetCandWindowPos()								= 0;
	virtual void		ImeSetCompWindowPos()								= 0;
	virtual void		ImeSetCompWindowFont()								= 0;
	


	virtual void		OnTesterMode(bool mode)				= 0;
	virtual BOOL		OnDoStatistic(STATISTIC* stati)		= 0;
	virtual LONG		OnGetConvertTypes(convert_type* convert_looup);
	virtual	LONG		OnSetResModule(HMODULE)				= 0;
	virtual LONG		OnGetTextLen()						= 0;
};
