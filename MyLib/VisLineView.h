#pragma once
#include "MyLib.h"
#include "MNLineGlyfCache.h"
#include "../textview/TextDocument.h"

#include <windows.h>
#include <vector>

class MnTextView;

//#define TEXTBUFSIZE  5120
#define CACHE_COUNT 20
typedef struct _LINE_INDEX
{
	int		visLine;
	int		logLine;
	int		subLine;
	_LINE_INDEX(UINT v,UINT l,UINT s):
		visLine(v),
		logLine(l),
		subLine(s)
	{}
	_LINE_INDEX():
		visLine(0),
		logLine(0),
		subLine(0)
	{}
	void print()
	{
		printf("v:%d,l:%d,s:%d",visLine,logLine,subLine);
	}
	friend bool operator==(const _LINE_INDEX&,const _LINE_INDEX&);
	friend bool operator!=(const _LINE_INDEX&,const _LINE_INDEX&);
	friend bool operator >(const _LINE_INDEX&,const _LINE_INDEX&);
	friend bool operator <(const _LINE_INDEX&,const _LINE_INDEX&);
	friend bool operator>=(const _LINE_INDEX&,const _LINE_INDEX&);

	friend bool operator<=(const _LINE_INDEX&,const _LINE_INDEX&);
	//friend int  operator -(const _LINE_INDEX&,const _LINE_INDEX&);
} LINE_INDEX;

class VisLineView
{

private :
	//std::vector<MNLogLine> m_LogLineList;
	typedef std::vector<MNLineGlyfCache> MNCahceList;
	MnTextView*		m_pTextView;
	MNCahceList		m_cacheList;
	std::vector<int>m_v2s;
	//int				m_avrageSublineCount;
	HWND			m_hwnd;

	UINT			m_width;
	UINT			m_height;

	UINT			m_lineHeight;
	UINT			m_lineWidth;

	UINT			m_logLineCount;
	int				m_visLineCount;


	CHAR_POS		m_selStartPos;
	CHAR_POS		m_selEndPos;

	TextDocument*	m_pTextDoc;

	WCHAR			m_buff[MAX_LINE_LENGTH];
	int				m_mruc_ID;//m_mostRecntlyUsedCacheID
	int				m_mruc_Line;//m_mostRecntlyUsedCacheLine_D

	void		initialize(UINT loglineCount);//{m_hwnd = hwnd;m_width}
	void		initLogLine(UINT logLineIndex, WCHAR* text,UINT length, MNTextAttr& textAttr);
	void		initLogLine(UINT logLineIndex, WCHAR* text,UINT length );

	void		initialize(HWND hwnd);//{m_hwnd = hwnd;m_width}
	void		initialize(HWND hwnd, UINT loglineCount);//{m_hwnd = hwnd;m_width}
public:

	
	//VisLineView(void);	

	//VisLineView(HWND hwnd,TextDocument* pDoc);
	VisLineView(MnTextView* pTextView);
	~VisLineView(void);
	int			MAX	;
	//void		initLogLine(UINT logLineIndex, UspFontManager* fontManager,WCHAR *text,int length,TextAttribute *textAttr);

	


	void		clearSelection();
	void		setSelection(CHAR_POS& cp1, CHAR_POS& cp2);
	void		invertSelection(CHAR_POS& cp1, CHAR_POS& cp2);
	UINT		getWidth();		
	int 		setWidth(UINT width);
	UINT		getHeight();

	UINT		getLineHeight();
	void		setLineHeight(UINT);
	void		setLineCount(UINT logLineCount);
	UINT		getLogLineCount();
	UINT		getSubLineCount(UINT logLineIndex);
	UINT		getVisLineCount();

	BOOL		getCharPos(int x, int y,__out CHAR_POS*, __out POINT* pPoint = NULL);
	BOOL		getCharLoc(CHAR_POS *charPos,__out CHAR_LOC*);
	BOOL		getLocation(__in const CHAR_POS* pCharPos, __out POINT* point);

	int			getCharCount_Without_CRLF(int logline);
	

	LINE_INDEX& getLineIndex(const CHAR_POS& charPos);
	LINE_INDEX& getLineIndex(UINT visLine);
	LINE_INDEX& getLineIndex(UINT logLine,UINT subLine);
	LINE_INDEX& next(LINE_INDEX&);
	LINE_INDEX& last(LINE_INDEX&);
	LINE_INDEX& getEnd();
	LINE_INDEX&	getBegin();

	LINE_INDEX& drawVisLine(HDC hdc,LINE_INDEX& idx,int x, int y);
	void		drawVisLine(HDC hdc,UINT visLine,int x, int y);

	void		resetCache(int line );
	void		resetCache( );



	BOOL		moveToCharPrev(const CHAR_POS &cp, __out CHAR_POS *outCP, bool bStopTail);
	BOOL		moveToCharNext(const CHAR_POS &cp, __out CHAR_POS *outCP, bool bStopHead);

	BOOL		moveToWordPrev(const CHAR_POS &cp, __out CHAR_POS *outCP);
	BOOL		moveToWordNext(const CHAR_POS &cp, __out CHAR_POS *outCP);

	BOOL		moveToWordStart(const CHAR_POS &charPos, __out CHAR_POS *outCP);
	BOOL		moveToWordEnd  (const CHAR_POS &charPos, __out CHAR_POS *outCP);

	BOOL		getWord(const CHAR_POS &cp, __out CHAR_POS *pWordStart, __out CHAR_POS *pWordEnd);
	
	BOOL		moveToVLineNext(const CHAR_POS &cp, int nVline, __out CHAR_POS *outCP);
	BOOL		moveToVLinePrev(const CHAR_POS &cp, int nVline, __out CHAR_POS *outCP);

	BOOL		moveToLineStart(const CHAR_POS &cp, __out CHAR_POS *outCP);
	BOOL		moveToLineEnd(const CHAR_POS &cp, __out CHAR_POS *outCP);
	//////
protected:
	int			getLineCache(UINT line);
	//int			CRLF_size(TCHAR *szText, int nLength);

};
