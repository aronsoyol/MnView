//
//	TextView public interface - include this file
//	when you want a TextView edit control
//
#ifndef TEXTVIEW_INCLUDED
#define TEXTVIEW_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UNICODE
#pragma message("Warning: UNICODE is not defined\n")
#endif

#include <windows.h>
//
//	TextView API declared here
//
//BOOL	 InitTextView();
//HWND	 CreateTextView(HWND hwndParent);

BOOL	 InitMnTextView();
HWND	 CreateMnTextView(HWND hwndParent);
HWND	 CreateMnConvertTextView(HWND hwndParent);

COLORREF RealizeColour(COLORREF col);

typedef struct STATISTIC_
{
	int nMongolWord;
	int nMongolChar;
	int nChineseChar;
	int nEnglishChar;
	int nPunctuation;
	int nTotalChar;
}STATISTIC;


//
// currently supported Neatpad Codepages
//

#define NCP_ASCII		0
#define NCP_UTF8		1
#define NCP_UTF16		2
#define NCP_UTF16BE		3
#define NCP_UTF32		4
#define NCP_UTF32BE		5
#define NCP_UNKNOWN		6

//
//	TextView edit modes
//
#define MODE_READONLY	0
#define MODE_INSERT		1
#define MODE_OVERWRITE	2

//
//	TextView Convert type
//
#define CONVERT_MENK2UNICODE			1
#define CONVERT_FANGZHENG2UNICODE		2
#define CONVERT_SAIYIN2UNICODE			3

typedef struct 
{
	WCHAR		zsDescript[256];
	int			nCommand;
} convert_type;
typedef struct 
{
	WCHAR	zsDescript[256];
	int		nEncodingType;
} encoding_type;

//extern convert_type Convert_Lookup[3];

extern encoding_type Encoding_Lookup[2] ;
//
//	TextView Window Messages defined here
//
#define TXM_BASE				(WM_USER)
#define TXM_OPENFILE			(TXM_BASE + 0)
#define TXM_CLEAR				(TXM_BASE + 1)
#define TXM_SETLINESPACING		(TXM_BASE + 2)
#define TXM_ADDFONT				(TXM_BASE + 3)
#define TXM_SETCOLOR			(TXM_BASE + 4)
#define TXM_GETCOLOR			(TXM_BASE + 5)
#define TXM_SETSTYLE			(TXM_BASE + 6)
#define TXM_GETSTYLE			(TXM_BASE + 7)
#define TXM_SETCARETWIDTH		(TXM_BASE + 8)
#define TXM_SETIMAGELIST		(TXM_BASE + 9)
#define TXM_SETLONGLINE			(TXM_BASE + 10)
#define TXM_SETLINEIMAGE		(TXM_BASE + 11)
#define TXM_GETFORMAT			(TXM_BASE + 12)
#define TXM_SETFORMAT			(TXM_BASE + 14)
#define TXM_UNDO				(TXM_BASE + 15)
#define TXM_REDO				(TXM_BASE + 16)
#define TXM_CANUNDO				(TXM_BASE + 17)
#define TXM_CANREDO				(TXM_BASE + 18)
#define TXM_GETSELSIZE			(TXM_BASE + 19)
#define TXM_SETSELALL			(TXM_BASE + 20)
#define TXM_GETCURPOS			(TXM_BASE + 21)
#define TXM_GETCURLINE			(TXM_BASE + 22)
#define TXM_GETCURCOL			(TXM_BASE + 23)
#define TXM_SETEDITMODE			(TXM_BASE + 24)
#define TXM_GETEDITMODE			(TXM_BASE + 25)
#define TXM_SETCONTEXTMENU		(TXM_BASE + 26)
#define TXM_SAVEFILE			(TXM_BASE + 27)
#define TXM_SETFONTFACE			(TXM_BASE + 28)
#define TXM_GETCURLINE_D		(TXM_BASE + 29)
#define TXM_GETCURLINE_V		(TXM_BASE + 30)
#define TXM_PRINT				(TXM_BASE + 31)
#define TXM_FIND_INIT			(TXM_BASE + 32)
#define TXM_FIND_GETTEXTLENGTH	(TXM_BASE + 33)
#define TXM_FIND				(TXM_BASE + 34)
#define TXM_REPLACE				(TXM_BASE + 35)
#define TXM_GETSELTEXT			(TXM_BASE + 36)
#define TXM_GETSELSTART			(TXM_BASE + 37)
#define TXM_GETSELEND			(TXM_BASE + 38)
#define TXM_SETTESTERMODE		(TXM_BASE + 39)
#define TXM_GETTEXTLEN			(TXM_BASE + 40)
#define TXM_IMPORTFILE			(TXM_BASE + 41)
#define TXM_EXPORTFILE			(TXM_BASE + 42)
#define TXM_STATISTIC			(TXM_BASE + 43)
#define TXM_CANLOADUMULIB		(TXM_BASE + 44)
#define TXM_GETCONVERTTYPES		(TXM_BASE + 45)
#define TXM_FIND_TEXT			(TXM_BASE + 46)
#define TXM_REPLACE_TEXT		(TXM_BASE + 47)
#define TXM_SETRESMODULE		(TXM_BASE + 48)

//
//	TextView Notification Messages defined here - 
//	sent via the WM_NOTIFY message
//
#define TVN_BASE				(WM_USER)
#define TVN_CURSOR_CHANGE		(TVN_BASE + 0)
#define TVN_SELECTION_CHANGED	(TVN_BASE + 1)
#define TVN_SELECTION_CHANGING	(TVN_BASE + 2)
#define TVN_EDITMODE_CHANGE		(TVN_BASE + 3)
#define TVN_CHANGED				(TVN_BASE + 4)



typedef struct
{
	NMHDR	hdr;
	ULONG	nLineNo;
	ULONG	nColumnNo;
	ULONG	nOffset;
} TVNCURSORINFO;

//typedef struct _TVPRINTINFO
//{
//	int			textSizePoint;
//	LPCWSTR*   	pDocName;
//	DOCINFO		di;
//} TVPRINTINFO;
//
//	TextView Window Styles defined here
//	(set using TXM_SETSTYLE)
//
#define TXS_SELMARGIN			1
#define TXS_LINENUMBERS			2
#define TXS_TREECTRL			4
#define TXS_LONGLINES			8
#define TXS_HIGHLIGHTCURLINE	16

//
//	End-of-line mode
//
#define TXL_LF				1		// line-feed
#define TXL_CR				2		// carriage-return
#define TXL_CRLF			4		// carriage-return, line-feed (default)
#define TXL_ALL				7		// allow all forms regardless

//
//	TextView Macros defined here
//
#define TEXTVIEW_CLASS _T("TextView32")

//
//	TextView colours
//
#define TXC_FOREGROUND			0			// normal foreground colour
#define TXC_BACKGROUND			1			// normal background colour
#define TXC_HIGHLIGHTTEXT		2			// normal text highlight colour
#define TXC_HIGHLIGHT			3			// normal background highlight colour
#define TXC_HIGHLIGHTTEXT2		4			// inactive text highlight colour
#define TXC_HIGHLIGHT2			5			// inactive background highlight colour
#define TXC_SELMARGIN1			6			// selection margin colour#1
#define TXC_SELMARGIN2			7			// selection margin colour#2
#define TXC_LINENUMBERTEXT		8			// line number text
#define TXC_LINENUMBER			9			// line number background
#define TXC_LONGLINETEXT		10			// long-line text
#define TXC_LONGLINE			11			// long-line background
#define TXC_CURRENTLINETEXT		12			// active line text
#define TXC_CURRENTLINE			13			// active line background
#define TXC_MAX_COLOURS			14			// keep this updated!

#define SYSCOL(COLOR_IDX)					   ( 0x80000000 |                     COLOR_IDX  )
#define MIXED_SYSCOL(COLOR_IDX1, COLOR_IDX2)   ( 0xC0000000 | (COLOR_IDX2 << 8) | COLOR_IDX1 )
#define MIXED_SYSCOL2(COLOR_IDX1, COLOR_IDX2)  ( 0xE0000000 | (COLOR_IDX2 << 8) | COLOR_IDX1 )

#define SYSCOLIDX(COLREF)   ( 0x00FFFFFF & COLREF )
#define REALIZE_SYSCOL(col) /*(RealizeColour(col))*/

typedef struct FIND_OPTION
{
	LPCWSTR	text;
	//UINT	length;
	BOOL	fMachCase;
	BOOL	fBackward;
	BOOL	fWarp;
	BOOL	fInSelection;
	//ULONG	nStartOffset;
} FIND_OPTION;
typedef struct REPLACE_OPTION
{
	FIND_OPTION fop;
	LPCWSTR		text;
	BOOL		bReplaceAll;
} REPLACE_OPTION;
//
//	TextView Message Macros defined here
//
#define TextView_OpenFile(hwndTV, szFile)	\
	SendMessage((hwndTV), TXM_OPENFILE, 0, (LPARAM)(TCHAR *)(szFile))

#define TextView_SaveFile(hwndTV, szFile)	\
	SendMessage((hwndTV), TXM_SAVEFILE, 0, (LPARAM)(TCHAR *)(szFile))

#define TextView_ImportFile(hwndTV, nConvertType, szFile)	\
	SendMessage((hwndTV), TXM_IMPORTFILE, (WPARAM)(int)nConvertType, (LPARAM)(TCHAR *)(szFile))

#define TextView_ExportFile(hwndTV, nConvertType, szFile)	\
	SendMessage((hwndTV), TXM_EXPORTFILE, (WPARAM)(int)nConvertType, (LPARAM)(TCHAR *)(szFile))

#define TextView_Clear(hwndTV)	\
	SendMessage((hwndTV), TXM_CLEAR, 0, 0)

#define TextView_SetLineSpacing(hwndTV, nAbove, nBelow) \
	SendMessage((hwndTV), TXM_SETLINESPACING, (int)(nAbove), (int)(nBelow))

#define TextView_AddFont(hwndTV, hFont) \
	SendMessage((hwndTV), TXM_ADDFONT, (WPARAM)(HFONT)(hFont), 0)

#define TextView_SetColor(hwndTV, nIdx, rgbColor) \
	SendMessage((hwndTV), TXM_SETCOLOR, (WPARAM)(nIdx), (LPARAM)(rgbColor))

#define TextView_SetStyle(hwndTV, uMask, uStyles) \
	SendMessage((hwndTV), TXM_SETSTYLE, (WPARAM)(uMask), (LPARAM)(uStyles))

#define TextView_SetStyleBool(hwndTV, uStyle, fBoolean) \
	SendMessage((hwndTV), TXM_SETSTYLE, (WPARAM)(uStyle), (LPARAM)(fBoolean ? uStyle : 0))
	
#define TextView_SetCaretWidth(hwndTV, nWidth) \
	SendMessage((hwndTV), TXM_SETCARETWIDTH, (WPARAM)(nWidth), 0)

#define TextView_SetImageList(hwndTV, hImgList) \
	SendMessage((hwndTV), TXM_SETIMAGELIST, (WPARAM)(HIMAGELIST)(hImgList), 0)

#define TextView_SetLongLine(hwndTV, nLength) \
	SendMessage((hwndTV), TXM_SETLONGLINE, (WPARAM)(0), (LPARAM)(nLength))

#define TextView_SetLineImage(hwndTV, nLineNo, nImageIdx) \
	SendMessage((hwndTV), TXM_SETLINEIMAGE, (WPARAM)(ULONG)(nLineNo), (LPARAM)(ULONG)nImageIdx)

#define TextView_GetFormat(hwndTV) \
	SendMessage((hwndTV), TXM_GETFORMAT, 0, 0)

#define TextView_SetFormat(hwndTV, Format) \
	SendMessage((hwndTV), TXM_SETFORMAT, (WPARAM)(int)(Format), 0)

#define TextView_Undo(hwndTV) \
	SendMessage((hwndTV), TXM_UNDO, 0, 0)

#define TextView_Redo(hwndTV) \
	SendMessage((hwndTV), TXM_REDO, 0, 0)

#define TextView_CanUndo(hwndTV) \
	SendMessage((hwndTV), TXM_CANUNDO, 0, 0)

#define TextView_CanRedo(hwndTV) \
	SendMessage((hwndTV), TXM_CANREDO, 0, 0)

#define TextView_GetSelSize(hwndTV) \
	SendMessage((hwndTV), TXM_GETSELSIZE, 0, 0)

#define TextView_SelectAll(hwndTV) \
	SendMessage((hwndTV), TXM_SETSELALL, 0, 0)

#define TextView_GetCurPos(hwndTV) \
	SendMessage((hwndTV), TXM_GETCURPOS, 0, 0)

#define TextView_GetCurLine(hwndTV) \
	SendMessage((hwndTV), TXM_GETCURLINE, 0, 0)

#define TextView_GetCurLineD(hwndTV) \
	SendMessage((hwndTV), TXM_GETCURLINE_D, 0, 0)

#define TextView_GetCurLineV(hwndTV) \
	SendMessage((hwndTV), TXM_GETCURLINE_V, 0, 0)

#define TextView_GetCurCol(hwndTV) \
	SendMessage((hwndTV), TXM_GETCURCOL, 0, 0)

#define TextView_SetEditMode(hwndTV, nEditMode) \
	SendMessage((hwndTV), TXM_SETEDITMODE, (WPARAM)(nEditMode), 0)

#define TextView_GetEditMode(hwndTV) \
	SendMessage((hwndTV), TXM_GETEDITMODE, 0, 0)

#define TextView_SetContextMenu(hwndTV, hPopupMenu) \
	SendMessage((hwndTV), TXM_SETCONTEXTMENU, (WPARAM)(hPopupMenu), 0)

#define TextView_SetFont(hwndTV, hFont) \
	SendMessage((hwndTV), WM_SETFONT, (WPARAM)(HFONT)(hFont), 0)

#define TextView_FindInit(hwndTV, string) \
	SendMessage((hwndTV), TXM_FIND_INIT, 0, (LPARAM) string)

#define TextView_FINDTEXTLENGTH(hwndTV) \
	SendMessage((hwndTV), TXM_FIND_GETTEXTLENGTH, 0, 0)

#define TextView_Find(hwndTV, bMatchCase, bBackward) \
	SendMessage((hwndTV), TXM_FIND,	   MAKELONG(bMatchCase, bBackward), 0)

#define TextView_Replace(hwndTV, bMatchCase, bBackward, bReplaceAll, string) \
	SendMessage((hwndTV), TXM_REPLACE, MAKELONG(bReplaceAll, MAKEWORD(bMatchCase, bBackward)), (LPARAM) string)

#define TextView_FindText(hwndTV, pFindOption) \
	SendMessage((hwndTV), TXM_FIND_TEXT,	0 , (LPARAM)pFindOption)

#define TextView_ReplaceText(hwndTV, pReplaceOption) \
	SendMessage((hwndTV), TXM_REPLACE_TEXT,	0 , (LPARAM)pReplaceOption)

#define TextView_GetSelStart(hwndTV) \
	SendMessage((hwndTV), TXM_GETSELSTART,	0, 0)

#define TextView_GetSelEnd(hwndTV) \
	SendMessage((hwndTV), TXM_GETSELEND,	0, 0)

#define TextView_GetSelText(hwndTV, buffer, buflen) \
	SendMessage((hwndTV), TXM_GETSELTEXT, (WPARAM)buffer, (LPARAM)buflen)

#define TextView_SetTesterMode(hwndTV, mode) \
	SendMessage((hwndTV), TXM_SETTESTERMODE, (WPARAM)mode, (LPARAM)0)

#define TextView_SetText(hwndTV, text) \
	SendMessage((hwndTV), WM_SETTEXT, 0, (LPARAM)text)

#define TextView_GetConvertLookup(hwndTV, convert_lookup) \
	SendMessage((hwndTV), TXM_GETCONVERTTYPES, 0, (LPARAM)(convert_lookup))

#define TextView_SetResModule(hwndTV, module) \
	SendMessage((hwndTV), TXM_SETRESMODULE, 0, (LPARAM)(module))

#define TextView_GetTextLen(hwndTV) \
	SendMessage((hwndTV), TXM_GETTEXTLEN, 0, 0)

#ifdef __cplusplus
}
#endif

#endif
