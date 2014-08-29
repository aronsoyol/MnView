#pragma once
#include "mylib.h"
#include <windows.h>
#include <usp10.h>
#pragma comment(lib, "usp10.lib")
class UspData
{
protected :
	int					m_RunCount;
	int					m_CharCount;
	int					m_GlyphCount;
	int					m_GlyphBufferLen;
	//int					m_CharBufferLen;
	//int					m_StringLength;
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
	WCHAR*				m_pText;
	TextAttribute *		m_pTextAttr;
	COLORREF*			m_pColorList;
	WORD				m_SelStart;
	WORD				m_SelEnd;

	RUN*				m_pRunList;
	
	int					m_RunBufferlen;
	UspFontManager *	m_pFontManager;
	SUBLINE*			m_pSubLineList;
	int					m_subLineBufferLength;
	int					m_subLineCount;
	//int				m_maxLineHeight;
	int					m_maxAscent;
	int					m_maxDescent;
	//HRGN				m_selectedRegion;

	char * fSoftBreak   ;//= new char[length+13];     // Potential linebreak point
    char * fWhiteSpace  ;//= new char[length+13];     // A unicode whitespace character, except NBSP, ZWNBSP
    char * fCharStop    ;//= new char[length+13];     // Valid cursor position (for left/right arrow)
    char * fWordStop    ;//= new char[length+13];     // Valid cursor position (for ctrl + left/right arrow)
    char * fInvalid     ;//= new char[length+13];     // Invalid character sequence
	char * clustStart   ;//= new char[length+13];    
	char * itemStart    ;//= new char[length+13];  
	char * runStart     ;//= new char[length+13]; 

	void	init();
	void	preAllocate();
	void	reAllocate();
	void	freeMemory();
	BOOL	analyze(WCHAR* text,int length);
	BOOL	itemize(WCHAR* text,int length);
	BOOL	eqaul(ATTR* attr0,ATTR* attr1);
	void	shapeAndPlace();
	
	HRESULT shapeAndPlaceRun(RUN *run,HDC *pDC) ;
	HRESULT shapeRun(RUN *run,HDC *pDC);
	HRESULT placeRun(RUN *run,HDC *pDC);

	//HRESULT shapeOneRun(RUN *run,HDC *pDC);
	//HRESULT placeOneRun(RUN *run,HDC *pDC);
	//HRESULT breakRun(RUN *run,HDC *pDC);
	SCRIPT_PROPERTIES getScriptProperty(int index);
	void	setColor(int start,int length,COLORREF color);
	void	createRunList();
	void	mergeSimpleScripts();
	HRESULT drawRun(RUN *run,HDC *pDc,int x,int y);
	HRESULT drawRun2(RUN *run,HDC *pDC,int x,int y);
	//HRESULT drawClust(int clustPos,HDC *pDc,int x,int y);
	//HRESULT	drawClust(HDC *pDc,int x,int y,int charPos,int charLen);
	int		getGlyphsWidth(int stGlyphPos,int enGlyphPos);
	
	HRESULT drawWords(HDC *pDC,SCRIPT_CACHE* cache, USPFONT* uspFont,int x,int y,int *pCharPos,int run,int *pWidth);
	HRESULT drawChars(HDC *pDC,int x,int y,int stCharPos,int enCharPos,int runIndex,int stGlyphPos=-1);
	HRESULT drawBacground(HDC *pDC,int x,int y,int stCharPos,int enCharPos,int runIndex,int stGlyphPos,RECT* selRect);
	HRESULT drawSelection(HDC *pDC,int x,int y,int stCharPos,int enCharPos,int runIndex,int stGlyphPos=-1);
	HRESULT drawBacground2(HDC *pDC,int x,int y,int stCharPos,int enCharPos,int runIndex,int stGlyphPos=-1);
	HRESULT drawClusts(HDC *pDC,SCRIPT_CACHE* cache, USPFONT* uspFont,int x,int y,int *pCharPos,int run,int *pWidth);
	HRESULT drawClust (HDC *pDC, SCRIPT_CACHE* cache, USPFONT* uspFont,int x,int y, RECT* rect, int *pCharPos, int *pGlyphCount, int run, int *pWidth);
	//int		getGlyphPos(int charPos,RUN *pRun);
	int		getGlyphPos(int charPos ,int *pRunIndex);
	int		getNextBreakPos(int charPos);
	//HRESULT	drawEx(HDC *pDc,int x,int y,int charPos,int width);
	int		correctMongolian(int start,int len);
	int		getMongolianScriptID();
	//int		getRunFromLineAndX(int subLineIndex,int x,int *pXInRun = NULL);
	int		getRunFromLineAndX(int subLineIndex,int x);
	int		getRunFromXy(int x,int y,int* xInRun);
	int		getRunFromCharPos(int charPos);
	int		getMaxRunIndexInLine(int subLineIndex);
	ABC		getClusterABCWidth(HDC* pDC,SCRIPT_CACHE *pCache,int clGlyphPos,int length);
	

public:
	//UspData(HWND hwnd,UspFontManager* fontManager,WCHAR *text,int length,ATTR *attrList);
	UspData(HWND hwnd,UspFontManager* fontManager,WCHAR *text,int length,TextAttribute *textAttr);
	//HDC		getDC();
	//WCHAR*	getText(){return this->m_Text;}
	//int		getTextLength(){return this->m_CharCount;}
	//WORD	getSelStart(){return this->m_SelStart;}
	
	int			getLineHeight();
	virtual int	breakLine(int width) ;
	int			getLineCount(int width);
	void		draw(HDC *pDc,int x,int y);
	int			drawEx(HDC *pDC,int x ,int y,int lineHeight);
	void		drawSubLine(HDC *pDC,int lineIndex,int x,int y);
	CHAR_POS&	getCharPos(int x,int y);
	BOOL		getCharPos(int x,int y,__out CHAR_POS*);
	BOOL		getCharPosFromSubLine(int subLineNo,int x, __out CHAR_POS*);
	CHAR_POS&	getCharPosFromSubLine(int subLineNo,int x);
	//int			getSubLine(CHAR_POS* charPos);
	int			getLineFromCharPos(int charPos);
	//POINT		getXyFromCharPos(int charPos,BOOL trailing);
	POINT		getLocation(CHAR_POS *charPos);
	CHAR_LOC&	getCharLocation(CHAR_POS *charPos);
	BOOL		getCharLocation(CHAR_POS *charPos,__out CHAR_LOC*);
	int			getRunXInSubLine(int runIndex,int lineIndex);
	//WORD	getSelEnd(){return this->m_SelEnd;}
	//void	addAttribute(int charPos,int length,CharAttribute *attribute);
	void	setFont();
	virtual ~UspData(void);
private:
	UspData(UspData&nothing){};

public:
	
	int aaaaaaaaaaaaaaaaaaaaaaaaaa(void);
	int ffffffffffffffffffffffff(void);
};
