#ifndef MnTextView_H
#define MnTextView_H

#include <windows.h>
#include <math.h>
#include <tchar.h>
#include "TextViewBase.h"
//#include "TextViewInternal.h"
#include "..\mylib\mylib.h"
#include "..\mylib\VisLineView.h"
//#include "..\MongolianNote\resource.h"
#include "MnStaticResource.h"
#pragma comment(lib, "imm32.lib") 
#define MNTEXTVIEW_CLASS		L"MNTEXTVIEW_CLASS"
#define	WD_HORIZONTAL			0
#define WD_VERTICAL				1
#define Margin					2
#define DFAULT_CARET_WIDTH		1

int ScrollDir(int counter, int dir);
HCURSOR CreateMyCursor(HMODULE module);

class MnTextView:public TextViewBase
{
	friend class VisLineView;
	FILE *fp;
	//WCHAR			*m_buffer;
	//UINT			m_bufLen;
	//POINT			m_caretPos;
	//CHAR_POS		m_caretCharPos;
	//BOOL			m_isLButtonDown;
	//CHAR_POS		m_selStart;
	//UINT			m_selLength;
	static MnStaticResource		m_Res;
protected:
	BOOL			m_direction;


	int				m_MarginLeft;
	int				m_MarginRight;
	int				m_MarginTop;
	int				m_MarginBottom;
	//LINE_INDEX		m_offset;
	LINE_INDEX		m_updateStart;
	int				m_updateCount;
	POINT			m_cursorPoint;
	//int				m_lineHeight;
	VisLineView     m_visualLineView;

	int				m_nScrollPos;
	int				m_nScrollMax;
	MNFontManager*	m_pFontManager;
	HCURSOR			m_hCursor;
	//MNUiPopupMenu*	m_pMenu;
	bool			m_fMenuVisible;
	HMODULE			m_hResModule;
	HMODULE			m_hMainModule;

	COLORREF		m_colFore;
	COLORREF		m_colBack;

	
	
public:
	MnTextView(HWND hwnd);
	~MnTextView(void);



private:
	//
	//	Message handlers
	//
	virtual LONG OnPaint();
	virtual LONG OnNcPaint(HRGN hrgnUpdate);
	virtual LONG OnSetFont(HFONT hFont);
	virtual LONG OnSetFont(WCHAR* fontName){return 0;}
	virtual LONG OnSize(UINT nFlags, int width, int height);
	virtual LONG OnVScroll(UINT nSBCode, UINT nPos){return 0;}
	virtual LONG OnHScroll(UINT nSBCode, UINT nPos);
	virtual LONG OnMouseWheel(int nDelta)
	{
		#ifndef	SPI_GETWHEELSCROLLLINES	
		#define SPI_GETWHEELSCROLLLINES   104
		#endif


		if(!IsKeyPressed(VK_SHIFT))
		{
			int nScrollLines;

			SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &nScrollLines, 0);

			if(nScrollLines <= 1)
				nScrollLines = 3;

			Scroll((-nDelta/120) * nScrollLines, 0);
			//RepositionCaret();
		}
	
		return 0;
	}
	virtual LONG OnTimer(UINT nTimer){return 0;}

	//virtual LONG OnPrint(HDC printDC, UINT width, UINT height){return 0;}
	//virtual LONG OnPrint(HDC printDC, TVPRINTINFO* pPrintInfo)	= 0;
	virtual LONG OnPrint(HDC printDC, int fontSizePoint);
	//virtual LONG OnMouseActivate(HWND hwndTop, UINT nHitTest, UINT nMessage);
	virtual LONG OnContextMenu(HWND wParam, int x, int y){
		return 0;
	}

	virtual LONG OnLButtonDown(UINT nFlags, int x, int y);
	virtual LONG OnLButtonUp(UINT nFlags, int x, int y);
	//virtual LONG OnLButtonDblClick(UINT nFlags, int x, int y){return 0;}
	virtual LONG OnRButtonDown(UINT nFlags, int x, int y);
	
	virtual LONG OnMouseMove(UINT nFlags, int x, int y);

	virtual LONG OnKeyDown(UINT nKeyCode, UINT nFlags);
	//virtual LONG OnChar(UINT nChar, UINT nFlags);

	virtual LONG OnSetFocus(HWND hwndOld);
	virtual LONG OnKillFocus(HWND hwndNew);

	//virtual BOOL OnCut(){return 0;}
	//virtual BOOL OnCopy(){return 0;}
	//virtual BOOL OnPaste(){return 0;}
	//virtual BOOL OnClear(){return 0;}
	virtual	LONG OnGetCurCol()
	{ 
		CHAR_LOC cl;
		if(m_visualLineView.getCharLoc(&m_CurrentCharPos,&cl))
			return cl.cp;
		return 0;
	}
	virtual	LONG OnGetCurLineV()
	{ 
		LINE_INDEX idx = m_visualLineView.getLineIndex(m_CurrentCharPos);
		return idx.visLine;
	}
	virtual LONG OnGetSelText(WCHAR* pBuffer, ULONG bufferLength);
	virtual	LONG OnGetCurLineD()
	{
		return m_nCurrentLine_D;
	}
protected:
	int				getMarginLeft();
	int				getMarginRight();
	int				getMarginBottom();
	int				getMarginTop();
	int				getMarginLR();
	int				getMarginTB();
	void			setMargin(int MarginALLSides);
	void			setMarginLeft(int MarginLeft);
	void			setMarginRight(int MarginRight);
	void			setMarginBottom(int MarginBottom);
	void			setMarginTop(int MarginTop);

	int				getLineHeight();//{return m_lineHeight;}

	void			updateCaretPos(const CHAR_POS &charPos, bool autoScrollToViewPort = true);	
	void			updateCaretPos(const POINT &point);
	int				breakLines(int width = 0,int height = 0);
	//BOOL			getSubLineRect(int index,RECT* pRect);

	//BOOL			getCharPos(int x, int y, __out CHAR_POS* charPos);

	BOOL			getVisLineRect(int vline,RECT* pRect);
	void			drawVisLine(HDC*  pDC,LINE_INDEX *vline,int x, int y);
	void			initialCharPos();
	BOOL			convertIn(POINT* point);
	BOOL			convertOut(POINT* point);
	void			OnDrawV(HDC* pDC, RECT& updateRect);
	void			OnDrawH(HDC* pDC, RECT& updateRect);
	void			drawBorder(HDC* pDC, RECT& updateRect);
	void			drawMarginLeft(HDC* pDC);
	void			drawMarginTop(HDC* pDC);
	void			drawMarginRight(HDC* pDC);
	void			drawMarginBottom(HDC* pDC);


	///
	//TextDocument	*m_pTextDoc;
//override
protected :
	
	LONG				OpenFile(TCHAR *szFileName);
	LONG				OnSetText(WCHAR* buffer, ULONG length);
	//LONG				SaveFile(TCHAR *szFileName);
	LONG				ImportFile(WCHAR *szFileName, int conver_type);
	LONG				ClearFile();
	void				ResetLineCache();
	void				ResetLineCache(ULONG line);
	//ULONG		GetText(TCHAR *szDest, ULONG nStartOffset, ULONG nLength) ;


	virtual LONG		InvalidateRange(ULONG nStart, ULONG nFinish);
	//virtual LONG		InvalidateRange(const POINT& stPt, const POINT& enPt);
	virtual LONG		InvalidateRange(const CHAR_POS& cp1, const CHAR_POS& cp2);
	virtual BOOL		InvalidateVisLine(const LINE_INDEX& idx);
	virtual BOOL		InvalidateLine(ULONG nLineNo);
	virtual VOID		UpdateLine(ULONG nLineNo){}
	//
	//	Caret/Cursor positioning
	//

	BOOL				CreateMyCaret() ;
	
	//BOOL				MouseCoordToFilePos(int x, int y, ULONG *pnLineNo, ULONG *pnFileOffset, int *px);//, ULONG *pnLineLen=0);
	BOOL				MouseCoordToCharPos(int x, int y,__out CHAR_POS* charPos, int *px =NULL);
	//BOOL				CharPosToFilePos(__in const CHAR_POS& charPos, __out ULONG *pnFileOffset);
	VOID				RepositionCaret();

	//VOID				UpdateCaretOffset(ULONG offset, BOOL fTrailing, int *outx=0, ULONG *outlineno=0);
	VOID				Smeg(BOOL fAdvancing);

	virtual VOID		MoveWordPrev();
	virtual VOID		MoveWordNext();

	virtual VOID		MoveWordStart();
	virtual VOID		MoveWordEnd();

	virtual VOID		MoveCharPrev(bool bStopTail = false, bool bUpdateCaretXY = false)	;
	virtual VOID		MoveCharNext(bool bStopHead = false, bool bUpdateCaretXY = false)	;
	virtual VOID		MoveLineUp(int numLines);
	virtual VOID		MoveLineDown(int numLines);
	virtual VOID		MovePageUp() ;
	virtual VOID		MovePageDown() ;
	virtual VOID		MoveLineStart(ULONG lineNo, bool bUpdateCaret = true);
	virtual VOID		MoveLineEnd(ULONG lineNo  , bool bUpdateCaret = true);
	//virtual VOID		MoveFileStart();
	//virtual VOID		MoveFileEnd();

	//
	//	Editing
	//	
	//virtual BOOL		Undo();
	//virtual BOOL		Redo();
	//virtual BOOL		CanUndo();
	//virtual BOOL		CanRedo();
	//virtual BOOL		ForwardDelete();
	//virtual BOOL		BackDelete();
	//virtual ULONG		EnterText(TCHAR *szText, ULONG nLength);

	virtual void		FindInitial (const WCHAR *find_text);
	//virtual LONG		FindForward (const WCHAR *find_text, BOOL bMatchcase, BOOL bRepalce)		;
	//virtual LONG		FindBackward(const WCHAR *find_text, BOOL bMatchcase, BOOL bRepalce)	;
	virtual LONG		FindForward (BOOL bMatchcase, const WCHAR *pReplaceText, BOOL bReplaceAll = FALSE);
	virtual LONG		FindForward2 (BOOL bMatchcase, const WCHAR *pReplaceText, BOOL bReplaceAll = FALSE);
	virtual LONG		Find_Text(const WCHAR *pFindText, ULONG length, BOOL bBack = FALSE, BOOL bMatchCase = FALSE, BOOL bWrap = FALSE, BOOL bSelFound = TRUE);
	virtual LONG		FindBackward(BOOL bMatchcase, const WCHAR *pReplaceText, BOOL bReplaceAll = FALSE);

	virtual LONG		Replace_Text(const REPLACE_OPTION *pOption);

	virtual LONG		ReplaceALLForward (BOOL bMatchcase, const WCHAR *pReplaceText);
	virtual LONG		ReplaceALLBackward(BOOL bMatchcase, const WCHAR *pReplaceText);

	//virtual LONG		ReplaceALLForward2 (BOOL bMatchcase, const WCHAR *pReplaceText);
	//virtual LONG		ReplaceALLBackward(BOOL bMatchcase, const WCHAR *pReplaceText);
	//
	//	Scrolling
	//
	virtual HRGN		ScrollRgn(int dx, int dy, bool fReturnUpdateRgn);// {return (HRGN)0;}
	virtual void		Scroll(int dx, int dy);
	virtual void		ScrollToCaret();//			{}
	virtual void		ScrollToPosition(int xpos, ULONG lineno) {}
	virtual VOID		SetupScrollbars();
	virtual VOID		UpdateMetrics()			;
	virtual VOID		RecalcLineHeight()		{}
	virtual bool		PinToBottomCorner()		{return false;}

	//
	virtual	BOOL		ValidatePoint(int x, int y);
	virtual	BOOL		GetOffsetAndLength_CRLF(ULONG line, __out ULONG* lineOffset, __out ULONG *length_CRLF) {return 0;}
	//
	//	Miscallaneous
	//
	//virtual HMENU		CreateContextMenu()	= 0;


	//virtual	LONG OnGetCurCol();
	//VOID	RefreshWindow();
	virtual HRESULT		OnStartComposition(WPARAM wParam, LPARAM lParam) ;
	virtual HRESULT		OnComposition(WPARAM wParam, LPARAM lParam)		;
	virtual HRESULT		OnEndComposition(WPARAM wParam, LPARAM lParam);
	virtual HRESULT		OnInputLanChange(WPARAM wParam, LPARAM lParam);
	virtual void		ImeSetCandWindowPos();
	virtual void		ImeSetCompWindowPos();
	virtual void		ImeSetCompWindowFont();
	BOOL				IsInside(const RECT &rect, const POINT &point)
	{
		
		return !(point.x < rect.left || point.x > rect.right || point.y < rect.top || point.y > rect.bottom);
	}

	virtual void		OnCtrlSpaceDown()
	{
		MessageBox(m_hWnd, L"haha", L"202F", 0);
		HIMC hIMC		= NULL;
		if (hIMC = ImmGetContext(m_hWnd))
		{
			WCHAR ch = 0x202F;
			ImmSetCompositionString(hIMC, SCS_SETSTR, (void*)&ch, 2, NULL, 0);
		}
		ImmReleaseContext(m_hWnd,hIMC);
	}
	virtual void		OnTesterMode(bool fmode);
	virtual BOOL		OnDoStatistic(STATISTIC* stati);
	virtual LONG		OnSetResModule(HMODULE hModule);
	virtual LONG		OnGetTextLen();

	//
	//EM_ message handler
	//
	virtual LONG		OnMsg_EM_GETSEL(ULONG *pStart, ULONG * pEnd);
	virtual	LONG		OnMsg_EM_SETSEL(long nStart, long nEnd);
};


#endif//MnTextView_H