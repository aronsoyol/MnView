#pragma once
#include "mylib.h"
#include "MnException.h"
#include "MNTextAttr.h"
#include "MNFont.h"
#include "MNRun.h"
#include "MNFontFallback.h"
#include "MNFontManager.h"

typedef  SCRIPT_VISATTR VISATTR;
typedef  SCRIPT_LOGATTR LOGATTR;
typedef  SCRIPT_ITEM    ITEM;

class GlyfData
{
	static MNFontFallback	s_fallbackList;
	
protected :
	int					m_RunCount;
	int					m_CharCount;
	int					m_GlyphCount;
	int					m_GlyphBufferLen;
	UINT				m_selStart;
	UINT				m_selLength;
	//int					m_CharBufferLen;
	//int					m_StringLength;
	MNTextAttr			m_textAttr;
	UINT				m_charBufferLength;
	WORD*				m_pClusterList;
	int*				m_pWidthList;
	WORD*				m_pGlyphList;
	GOFFSET*			m_pGoffsetList;
	VISATTR*			m_pVisAttrList;
	LOGATTR*			m_pLogAttrList; 
	ITEM*				m_pItemList;
	int					m_ItemCount;
	int					m_ItemBufferLength;
	HWND				m_Hwnd;
	//WCHAR*				m_pText; //do not save real text 
	int				*	m_pGalig;

	//TextAttribute *		m_pTextAttr;
	//COLORREF*			m_pColorList;
	MNFontManager*		m_pFontManager;

	//RUN*				m_pRunList;
	std::vector<MNRun>	m_pRunList;
	
	int					m_RunBufferlen;
	//UspFontManager *	m_pFontManager;
	SUBLINE*			m_pSubLineList;
	int					m_subLineBufferLength;
	int					m_subLineCount;
	//int				m_maxLineHeight;
	//int					m_maxAscent;
	//int					m_maxDescent;
	//HRGN				m_selectedRegion;
	int					m_recentlyUsedRun;
	int					m_recentlyUsedRunX;
	int					m_recentlyUsedSubLine;
	int					m_mongolianScriptId;
/*
	char * fSoftBreak   ;//= new char[length+13];     // Potential linebreak point
    char * fWhiteSpace  ;//= new char[length+13];     // A unicode whitespace character, except NBSP, ZWNBSP
    char * fCharStop    ;//= new char[length+13];     // Valid cursor position (for left/right arrow)
    char * fWordStop    ;//= new char[length+13];     // Valid cursor position (for ctrl + left/right arrow)
    char * fInvalid     ;//= new char[length+13];     // Invalid character sequence
	char * clustStart   ;//= new char[length+13];    
	char * itemStart    ;//= new char[length+13];  
	char * runStart     ;//= new char[length+13]; 
*/
	
	void	preAllocate();
	void	reAllocate();
	
	void	reallocRunBuffer(UINT newSize);
	void	reallocGlyfBuffer(UINT newSize);
	void	reallocCharBuffer(UINT newSize);
	void	reallocItemBuffer(UINT newSize);
	void	reallocSlineBuffer(UINT newSize);

	void	freeMemory();
	
	void	freeRunBuffer();
	void	freeGlyfBuffer();
	void	freeCharBuffer();
	void	freeItemBuffer();
	void	freeSlineBuffer();

	BOOL	analyze(WCHAR* text,int length);
	BOOL	itemize(WCHAR* text,int length);

	void	shapeAndPlace(HDC hdc, WCHAR* pText,int length);
						  // n(RUN *run, HDC *pDC, WCHAR* pText, int length)
	HRESULT shapeAndPlaceRun(RUN *run, HDC *pDC, WCHAR *pText, LONG length) ;
	HRESULT shapeRun(RUN *run,HDC *pDC);
	HRESULT placeRun(RUN *run,HDC *pDC);

	void	replaceMonCtrlCharGlyf(MNRun* run, WCHAR *pText, int length, WORD replaceGlyphId);

	SCRIPT_PROPERTIES getScriptProperty(int index);
	//void	setColor(int start,int length,COLORREF color);

	void	convert2Galig(WCHAR* text, UINT len);
	void	createRunList2(MNTextAttr& textAttr);
	void	createRunListSimply(void);
	void	mergeSimpleScripts();
	HRESULT drawRun(RUN *run,HDC *pDc,int x,int y);
	HRESULT drawRun2(RUN *run,HDC *pDC,int x,int y);

	int		getGlyphsWidth(int stGlyphPos,int enGlyphPos);
	HRESULT drawChars		(HDC *pDC, int x,int y,int stCharPos,int enCharPos,int runIndex,int stGlyphPos=-1, bool fDrawPhonec = false);
	HRESULT drawVowelCheck	(HDC *pDC, int x,int y,int stCharPos,int enCharPos,int runIndex,int stGlyphPos=-1);
	HRESULT drawGaligs		(HDC *pDC, int x,int y,int stCharPos,int enCharPos,int runIndex,int stGlyphPos=-1);
	HRESULT drawBackground	(HDC *pDC, int x,int y,int stCharPos,int enCharPos,int runIndex,int stGlyphPos, RECT* selRect);
	HRESULT drawSelection	(HDC *pDC, int x,int y,int stCharPos,int enCharPos,int runIndex,int stGlyphPos=-1);
	//HRESULT drawBacground2	(HDC *pDC, int x,int y,int stCharPos,int enCharPos,int runIndex,int stGlyphPos=-1);
	
	//HRESULT drawClusts(HDC *pDC,SCRIPT_CACHE* cache, USPFONT* uspFont,int x,int y,int *pCharPos,int run,int *pWidth);
	//HRESULT drawClust (HDC *pDC, SCRIPT_CACHE* cache, USPFONT* uspFont,int x,int y, RECT* rect, int *pCharPos, int *pGlyphCount, int run, int *pWidth);
	//int		getGlyphPos(int charPos,RUN *pRun);
	int		getGlyphPos(int charPos ,int *pRunIndex);
	int		getNextBreakPos(int charPos);
	//HRESULT	drawEx(HDC *pDc,int x,int y,int charPos,int width);




	int		correctMongolian(WCHAR* pText, UINT start, UINT end);
	int		getMongolianScriptID();
	//int		getRunFromLineAndX(int subLineIndex,int x,int *pXInRun = NULL);
	int		getRunFromLineAndX(int subLineIndex,int x, __out int* pRunX = NULL);
	//int		getRunFromXy(int x,int y,int* xInRun);
	int		getRunFromCharPos(int charPos);
	int		getMaxRunIndexInLine(int subLineIndex);
	ABC		getClusterABCWidth(HDC* pDC,SCRIPT_CACHE *pCache,int clGlyphPos,int length);
	
	void	updataCharSel(UINT charPos,UINT length);
	void	updataCharAttr(UINT charPos,UINT length);
	void	updateSubLineInfo();
	void	initialize(HWND hwnd,WCHAR* text,UINT len, MNTextAttr& textAttr);
	void	initialize(WCHAR* text,UINT len);
	//void	initialize(WCHAR* text,UINT len, const MNFontManager* pFm);
	//GlyfData(HWND hwnd,UspFontManager* fontManager,WCHAR *text,int length,TextAttribute *textAttr);

	CHAR_POS&	getCharPos(int x, int y);
	CHAR_POS&	getCharPosFromSubLine(int subLineNo,int x);
	CHAR_LOC&	getCharLocation(CHAR_POS *charPos);

	POINT		getLocation(const CHAR_POS *charPos);

public:
	//UspData(HWND hwnd,UspFontManager* fontManager,WCHAR *text,int length,ATTR *attrList);
	
	//
	GlyfData(void);
	GlyfData(HWND hwnd);
	GlyfData(const GlyfData&);
	GlyfData& operator = (const GlyfData&);
	//void		initialize(HWND hwnd,UspFontManager* fontManager,WCHAR *text,int length,TextAttribute *textAttr);

	void		initialize(HWND hwnd, WCHAR* text, UINT len);
	
	void		generateGlyph(HDC hdc,WCHAR* text,UINT len);
	//HDC		getDC();
	//WCHAR*	getText(){return this->m_Text;}
	int			getTextLength(){return this->m_CharCount;}
	//WORD	getSelStart(){return this->m_SelStart;}
	
	int			getLineWidth(int i);
	int			breakLine(int width);
	int			getLineCount();
	//void		draw(HDC *pDc,int x,int y);
	//int		drawEx(HDC *pDC,int x ,int y,int lineHeight);
	//void		drawSubLine(HDC *pDC, MNTextAttr& textAttr,int lineIndex,int x,int y);
	void		drawSubLine(HDC *pDC, int lineIndex,int x,int y);
	
	int			getWordStartPos(int charPos, __out CHAR_POS*);
	int			getWordEndPos(int charPos,   __out CHAR_POS*);

	int			getNextWordStop(int charPos);
	int			getPrevWordStop(int charPos);

	BOOL		getSlineStartPos(const CHAR_POS& charPos, __out CHAR_POS* pOutCharPos);
	BOOL		getSlineEndPos(const CHAR_POS& charPos, __out CHAR_POS* pOutCharPos);
	//BOOL		getCharPos(int x, int y, __out CHAR_POS*, __out POINT*);
	//BOOL		getCharPos(int X, int Y, __out CHAR_POS*, __out CHAR_LOC* );
	BOOL		getCharPos(__inout CHAR_LOC*, __out CHAR_POS*);
	//BOOL		getCharPosFromSubLine(int subLineNo,int x, __out CHAR_POS*);
	BOOL		getCharPosFromSubLine(int subLineNo, int x, __out CHAR_POS*, __out POINT* pPoint);
	BOOL		getCharPosFromSubLine(int subLineNo, int x, __out CHAR_POS*, __out CHAR_LOC* pCharLoc = NULL);
	
	//int			getSubLine(CHAR_POS* charPos);
	int			getLineFromCharPos(int charPos);
	//POINT		getXyFromCharPos(int charPos,BOOL trailing);
	
	BOOL		getLocation(const CHAR_POS *charPos, __out POINT* pPoint);
	//BOOL		getInfoFromCharPos(int charPos, __out int* pLine = NULL, __out int* pRun = NULL, int* pRunX = NULL);
	BOOL		CharPosToInfo(int charPos, __out int* pLine = NULL, __out int* pRun = NULL, int* pRunX = NULL);

	BOOL		getCharLocation(const CHAR_POS &charPos, __out CHAR_LOC*);
	BOOL		getCharLocation(const CHAR_POS *charPos, __out CHAR_LOC*);
	int			getRunXInSubLine(int runIndex,int lineIndex);
	//WORD	getSelEnd(){return this->m_SelEnd;}
	//void	addAttribute(int charPos,int length,CharAttribute *attribute);
	BOOL		moveToCharPrev(const CHAR_POS &cp, __out CHAR_POS *outCP, bool bStopTail);
	BOOL		moveToCharNext(const CHAR_POS &cp, __out CHAR_POS *outCP, bool bStopHead);

	BOOL		moveToWordPrev(const CHAR_POS &cp, __out CHAR_POS *outCP);
	BOOL		moveToWordNext(const CHAR_POS &cp, __out CHAR_POS *outCP);
	
	BOOL		moveToSLineNext(const CHAR_POS &cp, __out CHAR_POS *outCP);
	BOOL		moveToSLinePrev(const CHAR_POS &cp, __out CHAR_POS *outCP);

	int			setFont(MNText& fontName, UINT charPos, UINT len);
	int			setSize(UINT size, UINT charPos, UINT len);
	int			setTextSize(UINT size, UINT charPos, UINT len);
	UINT		getTextSize(UINT charPos);


	int			setSelect(int charPos, int len);
	void		setFgColor(UINT charPos, UINT len, COLORREF& col);
	void		setBgColor(UINT charPos, UINT len, COLORREF& col);
	MNText&		getFontName(UINT index);
	COLORREF&	getFgColor(UINT charPos);
	COLORREF&	getBgColor(UINT charPos);


	virtual UINT	getCharCount(){return m_CharCount;}
	//
	void	setFont();
	virtual ~GlyfData(void);

	

	
};

