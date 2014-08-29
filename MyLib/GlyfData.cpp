#include "StdAfx.h"
#include "GlyfData.h"
#include "conv2galig.h"
MNFontFallback GlyfData::s_fallbackList;

GlyfData::GlyfData(void):
	////3
	m_Hwnd			(0),
	//m_pFontManager	(NULL),
	//m_pText			(NULL),
	m_pGalig		(0),
	////2
	m_selStart		(0),
	m_selLength		(0),
	////3
	//m_pTextAttr		(NULL),
	//m_maxAscent		(0),
	//m_maxDescent	(0),

	///////5
	m_ItemCount		(0),
	m_CharCount		(0),
	m_GlyphCount	(0),
	m_RunCount		(0),
	m_subLineCount	(0),
	///////5
	m_charBufferLength		(0),
	m_ItemBufferLength		(0),
	m_RunBufferlen			(0),
	m_subLineBufferLength	(0),
	m_GlyphBufferLen		(0),
	//////9
	m_pVisAttrList	(NULL),
	m_pLogAttrList	(NULL),
	m_pClusterList	(NULL),
	m_pGlyphList	(NULL),
	m_pWidthList	(NULL),
	m_pGoffsetList	(NULL),
	m_pItemList		(NULL),
	//m_pRunList		(),
	m_pSubLineList	(NULL),
	/*
	fSoftBreak 		(NULL),
	fWhiteSpace 	(NULL),
	fCharStop   	(NULL),
	fWordStop   	(NULL),
	fInvalid    	(NULL),
	clustStart  	(NULL),
	itemStart   	(NULL),
	runStart    	(NULL),
	*/
	m_recentlyUsedRun(-1 ),
	m_recentlyUsedRunX(0 ),
	m_recentlyUsedSubLine(0)
{
	//MNRun run();
	m_pRunList.assign(20,MNRun());
	m_mongolianScriptId = getMongolianScriptID();
	//_CrtDumpMemoryLeaks();
}
GlyfData& GlyfData::operator = (const GlyfData& src)
{
	m_Hwnd			= src.m_Hwnd			;
	//m_pFontManager	= src.m_pFontManager	;
	//m_pText			= src.m_pText			;
	m_pGalig		= NULL;
	////2

	m_selStart		= src.m_selStart		;
	m_selLength		= src.m_selLength		;
	////3
	//m_pTextAttr		= src.m_pTextAttr	;
	//m_maxAscent		= src.m_maxAscent	;
	//m_maxDescent	= src.m_maxDescent		;
	///////5
	m_ItemCount		= src.m_ItemCount		;
	m_CharCount		= src.m_CharCount		;
	m_GlyphCount	= src.m_GlyphCount		;
	m_RunCount		= src.m_RunCount		;
	m_subLineCount	= src.m_subLineCount	;
		//
	m_recentlyUsedRun = -1 ;
	m_recentlyUsedRunX=0 ;

	return *this;
}

GlyfData::GlyfData(HWND hwnd):
	////3
	m_Hwnd			(hwnd),
	//m_pFontManager	(NULL),
	//m_pText			(NULL),
	m_pGalig		(0),
	////2
	m_selStart		(0),
	m_selLength		(0),
	////3
	//m_pTextAttr		(NULL),
	//m_maxAscent		(0),
	//m_maxDescent	(0),
	///////5
	m_ItemCount		(0),
	m_CharCount		(0),
	m_GlyphCount	(0),
	m_RunCount		(0),
	m_subLineCount	(0),
	///////5
	m_charBufferLength		(0),
	m_ItemBufferLength		(0),
	m_RunBufferlen			(0),
	m_subLineBufferLength	(0),
	m_GlyphBufferLen		(0),
	//////9
	m_pVisAttrList	(NULL),
	m_pLogAttrList	(NULL),
	m_pClusterList	(NULL),
	m_pGlyphList	(NULL),
	m_pWidthList	(NULL),
	m_pGoffsetList	(NULL),
	m_pItemList		(NULL),
	//m_pRunList		(),
	m_pSubLineList	(NULL),
	/*
	fSoftBreak 		(NULL),
	fWhiteSpace 	(NULL),
	fCharStop   	(NULL),
	fWordStop   	(NULL),
	fInvalid    	(NULL),
	clustStart  	(NULL),
	itemStart   	(NULL),
	runStart    	(NULL),
	*/
	m_recentlyUsedRun(-1 ),
	m_recentlyUsedRunX(0 ),
	m_recentlyUsedSubLine(0)
{
	m_mongolianScriptId = getMongolianScriptID();
}
GlyfData::GlyfData(const GlyfData& src):
	////3
	m_Hwnd			(src.m_Hwnd			),
	//m_pFontManager	(src.m_pFontManager	),
	//m_pText			(src.m_pText		),
	m_pGalig		(NULL ),
	////2
	m_selStart		(src.m_selStart		),
	m_selLength		(src.m_selLength	),
	////3
	//m_pTextAttr		(src.m_pTextAttr	),
	//m_maxAscent		(src.m_maxAscent	),
	//m_maxDescent	(src.m_maxDescent	),
	///////5

	m_ItemCount		(src.m_ItemCount	),
	m_CharCount		(src.m_CharCount	),
	m_GlyphCount	(src.m_GlyphCount	),
	m_RunCount		(src.m_RunCount		),
	m_subLineCount	(src.m_subLineCount	),
	///////5
	m_charBufferLength		(0),
	m_ItemBufferLength		(0),
	m_RunBufferlen			(0),
	m_subLineBufferLength	(0),
	m_GlyphBufferLen		(0),
	///////9
	m_pVisAttrList	(NULL),
	m_pLogAttrList	(NULL),
	m_pClusterList	(NULL),
	m_pGlyphList	(NULL),
	m_pWidthList	(NULL),
	m_pGoffsetList	(NULL),
	m_pItemList		(NULL),
	//m_pRunList		(),
	m_pSubLineList	(NULL),
	/*
	fSoftBreak 		(NULL),
	fWhiteSpace 	(NULL),
	fCharStop   	(NULL),
	fWordStop   	(NULL),
	fInvalid    	(NULL),
	clustStart  	(NULL),
	itemStart   	(NULL),
	runStart    	(NULL),
	*/
	m_recentlyUsedRun(-1 ),
	m_recentlyUsedRunX(0 ),
	m_recentlyUsedSubLine(0)
{
	m_mongolianScriptId = getMongolianScriptID();
	//memcpy(
}
	/*
GlyfData::GlyfData(HWND hwnd,UspFontManager* fontManager,WCHAR *text,int length,TextAttribute *textAttr):
	////3
	m_Hwnd			(0),
	m_pFontManager	(NULL),
	m_pText			(NULL),
	////2
	m_SelStart		(0),
	m_SelEnd		(0),
	////3
	m_pTextAttr		(NULL),
	m_maxAscent		(0),
	m_maxDescent	(0),
	///////5
	m_ItemCount		(0),
	m_CharCount		(0),
	m_GlyphCount	(0),
	m_RunCount		(0),
	m_subLineCount	(0),
	///////5
	m_charBufferLength		(0),
	m_ItemBufferLength		(0),
	m_RunBufferlen			(0),
	m_subLineBufferLength	(0),
	m_GlyphBufferLen		(0),
	//////9
	m_pVisAttrList	(NULL),
	m_pLogAttrList	(NULL),
	m_pClusterList	(NULL),
	m_pGlyphList	(NULL),
	m_pWidthList	(NULL),
	m_pGoffsetList	(NULL),
	m_pItemList		(NULL),
	m_pRunList		(NULL),
	m_pSubLineList	(NULL)
{
	preAllocate() ;
	itemize(text,length) ;
	mergeSimpleScripts() ;
	createRunList() ;
	shapeAndPlace() ;

	fSoftBreak   = new char[length+13];     // Potential linebreak point
    fWhiteSpace  = new char[length+13];     // A unicode whitespace character, except NBSP, ZWNBSP
    fCharStop    = new char[length+13];     // Valid cursor position (for left/right arrow)
    fWordStop    = new char[length+13];     // Valid cursor position (for ctrl + left/right arrow)
    fInvalid     = new char[length+13];     // Invalid character sequence
	clustStart   = new char[length*4+13];    
	itemStart    = new char[length+13];  
	runStart     = new char[length+13];  
	sprintf(fSoftBreak  ,"%-12s","fSoftBreak   ");
	sprintf(fWhiteSpace ,"%-12s","fWhiteSpace  ");
	sprintf(fCharStop	,"%-12s","fCharStop    ");
	sprintf(fWordStop	,"%-12s","fWordStop    ");
	sprintf(fInvalid	,"%-12s","fInvalid     ");
	sprintf(clustStart	,"%-13s","clustStart   ");
	sprintf(itemStart	,"%-13s","itemStart    ");
	sprintf(runStart	,"%-13s","runStart     ");
	int item = 0;
	int run  = 0;
	for(int i=0; i<length;i++)
	{
		sprintf(fSoftBreak  + i+12,"%d",  m_pLogAttrList[i].fSoftBreak);
		sprintf(fWhiteSpace + i+12,"%d",  m_pLogAttrList[i].fWhiteSpace);
		sprintf(fCharStop	+ i+12,"%d",  m_pLogAttrList[i].fCharStop);
		sprintf(fWordStop	+ i+12,"%d",  m_pLogAttrList[i].fWordStop);
		sprintf(fInvalid	+ i+12,"%d",  m_pLogAttrList[i].fInvalid);
		int j;
		if(i==0)
		{
			sprintf(clustStart	+ i+12,"%02d|", m_pClusterList[i]);
		}
		else if(i > 0)
		{
			//j = (m_pClusterList[i]!=m_pClusterList[i-1])?1:0;
			sprintf(clustStart	+ i*3 +12,"%02d|", m_pClusterList[i]);
		}
		if(this->m_pRunList[run+1].charPos==i)
		{
			run++;
			sprintf(runStart	+ i+12,"%d",  1);
		}else
		{
			sprintf(runStart	+ i+12,"%d",  0);
		}
		if(this->m_pItemList[item+1].iCharPos==i)
		{
			item++;
			sprintf(itemStart	+ i+12,"%d",  1);
		}else
		{
			sprintf(itemStart	+ i+12,"%d",  0);
		}
	}
	//delete fSoftBreak  ;
	//delete fWhiteSpace ;
	//delete fCharStop   ;
	//delete fWordStop   ;
	//delete fInvalid    ;
	//delete clustStart  ;
	//delete itemStart   ;
	//delete runStart    ;
}*/
//void GlyfData::init()
//{
//	p
//}
void GlyfData::initialize(WCHAR* pText, UINT length)
{
	//m_pText			= text;//(NULL),
	////2
	m_selStart		= 0;//(0),
	m_selLength		= 0;//(0),
	////3
	//m_pTextAttr		= textAttr;//(NULL),
	//m_maxAscent		= 0;//(0),
	//m_maxDescent	= 0;//(0),
	///////5
	m_ItemCount		= 0;//(0),
	m_CharCount		= length;//(0),
	m_GlyphCount	= 0;//(0),
	m_RunCount		= 0;//(0),
	m_subLineCount	= 0;//(0),

	m_recentlyUsedRun =-1;
	///
	if(pText == NULL ||length == 0) return ;
	m_textAttr.reset();
	if((int)m_charBufferLength < m_CharCount + 1) reallocCharBuffer	( m_CharCount + 1 );

	if(m_ItemBufferLength		== 0)reallocItemBuffer	( 10 );
	itemize(pText, length) ;
	//mergeSimpleScripts() ;
	///
	m_pRunList.clear();
	m_RunBufferlen  = (int)m_pRunList.size();
	if(m_RunBufferlen			== 0)reallocRunBuffer	( m_ItemCount * 2 );
	if(m_subLineBufferLength	== 0)reallocSlineBuffer	( 10 );
	if(m_GlyphBufferLen			== 0)reallocGlyfBuffer	( UINT(length * 1.5) + 1 );
}

void GlyfData::initialize(HWND hwnd,WCHAR* text,UINT length)
{
	m_Hwnd			= hwnd;//(0),
	//m_pFontManager	= fontManager;//(NULL),
	//m_pText			= text;//(NULL),
	////2
	m_selStart		= 0;//(0),
	m_selLength		= 0;//(0),
	////3
	//m_pTextAttr		= textAttr;//(NULL),
	//m_maxAscent		= 0;//(0),
	//m_maxDescent	= 0;//(0),
	///////5
	m_ItemCount		= 0;//(0),
	m_CharCount		= length;//(0),
	m_GlyphCount	= 0;//(0),
	m_RunCount		= 0;//(0),
	m_subLineCount	= 1;//(0),

	///
	m_recentlyUsedRun = -1;
	///
	if(text ==NULL ||length == 0) return ;
	if(m_charBufferLength < m_CharCount + 1) reallocCharBuffer	( m_CharCount + 1 );

	if(m_ItemBufferLength		== 0)reallocItemBuffer	( 10 );
	itemize(text, length) ;
	mergeSimpleScripts() ;
	///
	if(m_RunBufferlen			== 0)reallocRunBuffer	( m_ItemCount * 2 );
	if(m_subLineBufferLength	== 0)reallocSlineBuffer	( 10 );
	if(m_GlyphBufferLen			== 0)reallocGlyfBuffer	( UINT(length * 1.5) + 1 );

}
void GlyfData::generateGlyph(HDC hdc, WCHAR* pText, UINT length)
{
	if(m_CharCount == 0  ) 

		return ;
	if(m_CharCount != length)
	{
		return ;
	}

	//itemize(pText,length) ;
	createRunListSimply();
	
	shapeAndPlace(hdc, pText, length) ;
	if(m_pClusterList[0] == 52685)
	{
		int stop =1;
	}
	convert2Galig(pText, length) ;
	if(m_pClusterList[0] == 52685)
	{
		int stop =1;
	}
	
}
/*
void GlyfData::initialize(HWND hwnd,WCHAR* text,UINT length, MNTextAttr& textAttr)
{
		////3
	m_Hwnd			= hwnd;//(0),
	//m_pFontManager	= fontManager;//(NULL),
	m_pText			= text;//(NULL),
	////2
	m_selStart		= 0;//(0),
	m_selLength		= 0;//(0),
	////3
	//m_pTextAttr		= textAttr;//(NULL),
	//m_maxAscent		= 0;//(0),
	//m_maxDescent	= 0;//(0),
	///////5
	m_ItemCount		= 0;//(0),
	m_CharCount		= length;//(0),
	m_GlyphCount	= 0;//(0),
	m_RunCount		= 0;//(0),
	m_subLineCount	= 0;//(0),

	///
	m_recentlyUsedRun = -1;
	///
	if(m_charBufferLength < m_CharCount + 1) reallocCharBuffer	( m_CharCount + 1 );

	if(m_ItemBufferLength		== 0)reallocItemBuffer	( 10 );
	itemize(text,length) ;
	mergeSimpleScripts() ;
	///
	if(m_RunBufferlen			== 0)reallocRunBuffer	( m_ItemCount * 2 );
	if(m_subLineBufferLength	== 0)reallocSlineBuffer	( 10 );
	if(m_GlyphBufferLen			== 0)reallocGlyfBuffer	( UINT(length * 1.5) + 1 );

	
	
	createRunList2(textAttr) ;
	shapeAndPlace() ;
}

void GlyfData::initialize(HWND hwnd,UspFontManager* fontManager,WCHAR *text,int length,TextAttribute *textAttr)
{
		////3
	m_Hwnd			= hwnd;//(0),
	m_pFontManager	= fontManager;//(NULL),
	m_pText			= text;//(NULL),
	////2
	m_SelStart		= 0;//(0),
	m_SelEnd		= 0;//(0),
	////3
	m_pTextAttr		= textAttr;//(NULL),
	m_maxAscent		= 0;//(0),
	m_maxDescent	= 0;//(0),
	///////5
	m_ItemCount		= 0;//(0),
	m_CharCount		= length;//(0),
	m_GlyphCount	= 0;//(0),
	m_RunCount		= 0;//(0),
	m_subLineCount	= 0;//(0),

	if(m_charBufferLength		== 0)reallocCharBuffer	( length + 1 );
	if(m_ItemBufferLength		== 0)reallocItemBuffer	( 5 );
	if(m_RunBufferlen			== 0)reallocRunBuffer	( 5 * 2 );
	if(m_subLineBufferLength	== 0)reallocSlineBuffer	( 10 );
	if(m_GlyphBufferLen			== 0)reallocGlyfBuffer	( UINT(length * 1.5) + 1 );

	itemize(text,length) ;
	mergeSimpleScripts() ;
	createRunList() ;
	shapeAndPlace() ;
}
*/
BOOL GlyfData::itemize(WCHAR* text, int length)
{
	HRESULT hr;
	int rellocSize = 0;
	do
	{
		if(rellocSize > m_ItemBufferLength)
		{
			this->m_pItemList = (ITEM*)realloc(m_pItemList,sizeof(ITEM) * rellocSize);
			m_ItemBufferLength = rellocSize;
		}
		 
		hr = ScriptItemize(
			text,
			length,
			m_ItemBufferLength,
			NULL,
			NULL,
			this->m_pItemList,
		   &this->m_ItemCount
		);
		if(hr != S_OK && hr != E_OUTOFMEMORY)
			return FALSE;
		rellocSize += (m_ItemBufferLength + 20);
	}while(hr == E_OUTOFMEMORY);
	
	
	return TRUE;
}
/*
BOOL GlyfData::eqaul(ATTR* attr0,ATTR* attr1)
{
	if(   attr0->bgColor	!=attr1->bgColor
		||attr0->bold		!=attr1->bold
		||attr0->italic		!=attr1->italic
		||attr0->size		!=attr1->size
		||attr0->underLine	!=attr1->underLine
		||attr0->bgColor	!=attr1->bgColor
		||attr0->fgColor	!=attr1->fgColor
	)
		return FALSE;
	else
		return TRUE;
}

void GlyfData::createRunList()
{
	int run			= 0;
	int item		= 0;
	int charCount	= 1;

	if(m_RunBufferlen == 0)
		throw UspException();
	this->m_pRunList[0].charPos   = 0;
	this->m_pRunList[0].fontIndex = this->m_pFontManager->getFontIndex( &m_pTextAttr->GetAttr(0));

	USPFONT* uspFont= m_pFontManager->getUspFont(m_pRunList[0].fontIndex);
	this->m_maxDescent = m_pFontManager->getUspFont(m_pRunList[0].fontIndex)->tm.tmDescent;
	this->m_maxAscent  = m_pFontManager->getUspFont(m_pRunList[0].fontIndex)->tm.tmAscent;
	for(int i=1 ;i<=this->m_CharCount;i++)
	{
		BOOL b = m_pTextAttr->canBreakRun(i-1,i);
		if(b || m_pItemList[item + 1 ].iCharPos == i)
		{
			this->m_pRunList[run].charCount = charCount;
			this->m_pRunList[run].glyphPos  = 0;
			this->m_pRunList[run].scriptAnalyze = m_pItemList[item ].a;
			uspFont			= m_pFontManager->getUspFont(m_pRunList[run].fontIndex);
			charCount		= 0;
			TEXTMETRIC* pTm = &uspFont->tm;
			m_maxAscent		= max(m_maxAscent,pTm->tmAscent  );
			m_maxDescent	= max(m_maxDescent,pTm->tmDescent );
			run ++;
			if(run + 1 > m_RunBufferlen)
				reallocRunBuffer(m_RunBufferlen + 10);
			this->m_pRunList[run].charPos   = i ;
			this->m_pRunList[run].fontIndex = 
				this->m_pFontManager->getFontIndex( &m_pTextAttr->GetAttr(i));
			if(this->m_pItemList[item + 1].iCharPos == i)item ++;
		}
		charCount++;
	}
	m_RunCount = run;
}
*//*
void GlyfData::createRunList(MNTextAttr& textAttr)
{
	int run			= 0;
	int item		= 0;
	int charCount	= 1;

	if(m_RunBufferlen == 0)
		throw UspException();
	

	int haha = m_pRunList[0].charPos;
	this->m_pRunList[0].charPos	= 0;

	this->m_pRunList[0].font.init(
				textAttr.getFontName(textAttr[0].fontIndex),
				textAttr[0].size,
				textAttr[0].bold,
				textAttr[0].italic,
				textAttr[0].underLine
			);
	//USPFONT* uspFont= m_pFontManager->getUspFont(m_pRunList[0].fontIndex);
	HDC hdc	= GetDC(m_Hwnd);

	//TextOut(hdc,0,0,L"aasdf",5);
	this->m_maxDescent = m_pRunList[0].font.tm.tmDescent;
	this->m_maxAscent  = m_pRunList[0].font.tm.tmAscent;
	for(int i = 1 ; i <= m_CharCount; i++)
	{
		bool b = textAttr.canBreakRun(i-1,i);
		if(b || m_pItemList[item + 1 ].iCharPos == i)
		{
			this->m_pRunList[run].charCount		= charCount;
			this->m_pRunList[run].glyphPos		= 0;
			this->m_pRunList[run].scriptAnalyze = m_pItemList[item ].a;
			


			//uspFont			= m_pFontManager->getUspFont(m_pRunList[run].fontIndex);
			charCount		= 0;
			TEXTMETRIC* pTm = &m_pRunList[run].font.tm;
			GetTextMetrics(hdc,pTm);
			m_maxAscent		= max(m_maxAscent,pTm->tmAscent  );
			m_maxDescent	= max(m_maxDescent,pTm->tmDescent );

			
			if(run + 1 >= m_RunBufferlen)
				reallocRunBuffer(m_RunBufferlen + 10);

			this->m_pRunList[run].font.init(
				textAttr.getFontName(textAttr[i-1].fontIndex),
				textAttr[i-1].size,
				textAttr[i-1].bold,
				textAttr[i-1].italic,
				textAttr[i-1].underLine
			);
			run ++;

			if( run >= m_RunBufferlen)
			{
				int stop=1;
			}
			this->m_pRunList[run].charPos   = i ;

			if(run > 0)
			{

				if(m_pRunList[1].charPos == 1)
				{
					int stop =1;
				}
			}
			if(this->m_pItemList[item + 1].iCharPos == i)item ++;
		}
		charCount++;
	}
	if(m_pRunList[1].charPos != m_pRunList[0].charPos + m_pRunList[0].charCount)
	{
		int stop =1;
	}
	m_RunCount = run;
	ReleaseDC(m_Hwnd,hdc);
}
*/
void GlyfData::createRunListSimply(void)
{
	if(m_RunBufferlen == 0)
		throw UspException();
	if(m_RunBufferlen < m_ItemCount)
		reallocRunBuffer(m_ItemCount + 1);
	m_RunCount = m_ItemCount;
	
	for(int i = 0; i < m_ItemCount; i++)
	{	
		m_pRunList[i].charPos		= m_pItemList[i].iCharPos;
		m_pRunList[i].charCount		= m_pItemList[i + 1].iCharPos - m_pItemList[i].iCharPos;
		m_pRunList[i].glyphPos		= 0;
		m_pRunList[i].scriptAnalyze = m_pItemList[i ].a;
		m_pRunList[i].fontIndex		= 0;
	}
	m_pRunList[m_RunCount].charPos	= m_CharCount;
}
void GlyfData::convert2Galig(WCHAR* pText, UINT length)
{
	Convert(pText, m_pGalig, length);
}
void GlyfData::createRunList2(MNTextAttr& textAttr)
{
	int run			= 0;
	int item		= 0;
	int charCount	= 1;

	if(m_RunBufferlen == 0)
		throw UspException();
	

	int haha = m_pRunList[0].charPos;
	MNCharAttr& charAttr0	= textAttr[0];
	m_pRunList[0].charPos	= 0;

	m_pRunList[0].fontIndex = charAttr0.fontIndex;
		//= m_pFontManager->getFontIndex(
		//		textAttr.getFontName(charAttr0.fontIndex),
		//		charAttr0.size,
		//		charAttr0.bold,
		//		charAttr0.italic,
		//		charAttr0.underLine
		//	);
	//USPFONT* uspFont= m_pFontManager->getUspFont(m_pRunList[0].fontIndex);
	//HDC hdc	= GetDC(m_Hwnd);

	//TextOut(hdc,0,0,L"aasdf",5);
	//MNFont &font0 = *m_pFontManager->m_fontList[0];
	//this->m_maxDescent = font0.tm.tmDescent;
	//this->m_maxAscent  = font0.tm.tmAscent;
	for(int i = 1 ; i <= m_CharCount; i++)
	{
		bool b = textAttr.canBreakRun(i-1,i);
		if(b || m_pItemList[item + 1 ].iCharPos == i)
		{
			this->m_pRunList[run].charCount		= charCount;
			this->m_pRunList[run].glyphPos		= 0;
			this->m_pRunList[run].scriptAnalyze = m_pItemList[item ].a;
			


			//uspFont			= m_pFontManager->getUspFont(m_pRunList[run].fontIndex);
			charCount		= 0;
			
			//TEXTMETRIC* pTm = &m_pFontManager->m_fontList[m_pRunList[run].fontIndex]->tm;
			//
			//m_maxAscent		= max(m_maxAscent,pTm->tmAscent  );
			//m_maxDescent	= max(m_maxDescent,pTm->tmDescent );

			
			if(run + 1 >= m_RunBufferlen)
				reallocRunBuffer(m_RunBufferlen + 10);

			MNCharAttr& charAttr	= textAttr[i - 1];
			run ++;
			if( run >= m_RunBufferlen)
			{
				int stop=1;
			}
			m_pRunList[run].fontIndex = charAttr.fontIndex;
			
			this->m_pRunList[run].charPos   = i ;

			if(run > 0)
			{

				if(m_pRunList[1].charPos == 1)
				{
					int stop =1;
				}
			}
			if(this->m_pItemList[item + 1].iCharPos == i)item ++;
		}
		charCount++;
	}
	if(m_pRunList[1].charPos != m_pRunList[0].charPos + m_pRunList[0].charCount)
	{
		int stop =1;
	}
	m_RunCount = run;
	//ReleaseDC(m_Hwnd,hdc);
}
void GlyfData::mergeSimpleScripts()
{
	// global script-table, used for merging non-complex runs together :)
	const SCRIPT_PROPERTIES **propList;
	int					propCount;
	int					i =0;;

	// get pointer to the global script table
	ScriptGetProperties(&propList, &propCount);
	while(i  <m_ItemCount - 1)
	{
		if( propList[m_pItemList[i+0].a.eScript]->fComplex == FALSE 
		 && propList[m_pItemList[i+1].a.eScript]->fComplex == FALSE)
		{
			memmove(&m_pItemList[i+1],&m_pItemList[i+2],sizeof(ITEM) * m_ItemCount-i-1);
			m_pItemList[i].a.eScript = SCRIPT_UNDEFINED;
			m_ItemCount --;
		}
		else
			i++;
	}
}
//void GlyfData::drawEx(HDC *pDc,int x,int y,int lineWidth)
//{	int Margin		= x ;
//	int tmpWidth	= 0;
//	int tmp			= 0;
//	for(int i= 0; i<m_RunCount; i++ )
//	{
//		//int runWidth = getRunWidth();
//		if( x + m_pRunList[i].abc.abcB > lineWidth + Margin)
//		{
//			int charPos  = m_pRunList[i].charPos;
//			int remained = lineWidth + Margin - x;// + m_pRunList[i].abc.abcB);
//			
//			drawClusts(
//				pDc,
//				m_pFontManager->getFontCache(m_pRunList[i].fontIndex),
//				m_pFontManager->getUspFont(m_pRunList[i].fontIndex),
//				x,
//				y,
//				&charPos,
//				i,
//				&remained
//			);
//				
//			x = Margin;
//			y+= getLineHeight();
//			remained = lineWidth ;
//			if(charPos < m_pRunList[i+1].charPos)
//			{
//				drawClusts(
//					pDc,
//					m_pFontManager->getFontCache(m_pRunList[i].fontIndex),
//					m_pFontManager->getUspFont(m_pRunList[i].fontIndex),
//					x,
//					y,
//					&charPos,
//					i,
//					&remained
//				);
//			}
//
//			x+=remained;
//		}
//		else
//		{
//			drawRun2(&m_pRunList[i],pDc,x,y);
//			x += m_pRunList[i].abc.abcB;
//		}
//	}
//
//}
BOOL GlyfData::moveToSLineNext(const CHAR_POS &cp, __out CHAR_POS *outCP)
{
	return FALSE;
}
BOOL GlyfData::moveToSLinePrev(const CHAR_POS &cp, __out CHAR_POS *outCP)
{
	CHAR_LOC cl;
	int maxPos,charPos = cp.index + cp.trailing;
	
	getCharLocation(&cp, &cl);


	charPos = max(0, min(charPos, m_CharCount - 1));

	if(charPos == 0) return FALSE;

	if(cl.subLine == 0) return FALSE;
	charPos = charPos - m_pSubLineList[cl.subLine].charPos;
	maxPos  = m_pSubLineList[cl.subLine].charPos 
			- m_pSubLineList[cl.subLine - 1].charPos;
	charPos = charPos + m_pSubLineList[cl.subLine - 1].charPos;
	charPos = min(charPos, maxPos);

	//if(charpos.fCharStop != 1)??
	outCP->set(cp.logLine,charPos,cp.trailing);
	return TRUE;
}
BOOL GlyfData::moveToCharPrev(const CHAR_POS &cp, __out CHAR_POS *outCP, bool bStopTail)
{
	CHAR_LOC cl;
	int charPos = cp.index + cp.trailing;
	
	getCharLocation(&cp, &cl);

	charPos = max(0, min(charPos, m_CharCount));

	if(charPos == 0) return FALSE;
	if(bStopTail && charPos == m_pSubLineList[cl.subLine].charPos && cl.subLine > 0 )
	{
		outCP->set(cp.logLine, m_pSubLineList[cl.subLine].charPos - 1, 1);
		return TRUE;
	}
	
	//charPos --;
	//--charPos;
	if(charPos < 0)charPos = 0;
	
	while(--charPos > 0)
	{
		if(m_pLogAttrList[charPos].fInvalid == 0)
			break; 
	}
	
	outCP->set(cp.logLine,charPos,0);
	return TRUE;
}
BOOL GlyfData::moveToCharNext(const CHAR_POS &cp, __out CHAR_POS *outCP, bool bStopHead)
{
	CHAR_LOC cl;
	int charPos = cp.index + cp.trailing;
	if(charPos == 5)
	{
		int stop = 1;
	}
	getCharLocation(&cp, &cl);


	charPos = max(0, min(charPos, m_CharCount - 1));

	if(charPos == m_CharCount) return FALSE;
	if(bStopHead && cl.subLine + 1 < m_subLineCount && charPos == m_pSubLineList[cl.subLine + 1].charPos &&  cp.trailing == 1)
	{
		outCP->set(cp.logLine, charPos, 0);
		return TRUE;
	}
	
	//charPos --;
	
	while(++charPos < m_CharCount)
	{
		if(m_pLogAttrList[charPos].fInvalid == 0)
			break; 
	}
	
	//++charPos;
	outCP->set(cp.logLine,charPos - 1, 1);
	return TRUE;
}
//BOOL GlyfData::moveToCharNext(const CHAR_POS &cp, __out CHAR_POS *outCP);
//
//BOOL GlyfData::moveToWordPrev(const CHAR_POS &cp, __out CHAR_POS *outCP);
//BOOL GlyfData::moveToWordNext(const CHAR_POS &cp, __out CHAR_POS *outCP);
//
//BOOL GlyfData::moveToLineNext(const CHAR_POS &cp, __out CHAR_POS *outCP);
//BOOL GlyfData::moveToLinePrev(const CHAR_POS &cp, __out CHAR_POS *outCP);
int	GlyfData::getLineWidth(int i)
{
	return m_pSubLineList[i].width;
}
int GlyfData::breakLine(int lineWidth)
{
	if(m_CharCount == 0) return 1;
	//updateSubLineInfo();

	int dx				= 0;
	//int dy				= 0;
	//int	dY				= (y < 0)? -getLineHeight() : getLineHeight();

	int lineCount		= 1;

	int wordWidth		= 0;

	int	runIndex0		= 0;
	int	runIndex1		= 0;

	int glyphPos0		= 0;
	int	glyphPos1		= 0;

	int charPos0		= 0;
	int charPos1		= 0;
	//int charPos2		= 0;
	//USPFONT *uspFont	= NULL;

	m_subLineCount		= 1;
	//UspFont
	///
	m_recentlyUsedRun	= -1;

	charPos1			= getNextBreakPos(0);
	glyphPos1			= getGlyphPos(	charPos1,
										&runIndex1 );

	if(glyphPos1 == 52685)
	{
		int stop =1;
	}
	wordWidth			= getGlyphsWidth(glyphPos0, glyphPos1);
	dx					= wordWidth;

	m_pSubLineList[0].runIndex	= 0;
	m_pSubLineList[0].glyphPos	= 0;
	m_pSubLineList[0].charPos	= 0;
	m_pSubLineList[0].width		= dx;
	m_pSubLineList[0].isUpdata	= false;


	while( runIndex1 < m_RunCount && charPos1 < m_CharCount)
	{
		runIndex0	= runIndex1;
		glyphPos0	= glyphPos1;
		charPos0	= charPos1;
		//nextWordCharPos = getNextBreakPos(*pCharPos);
		//glyphPos1	= getGlyphPos(charPos,&runIndex0);
		charPos1	= getNextBreakPos(charPos0);
		glyphPos1	= getGlyphPos(
									charPos1
									,&runIndex1
					);
		if(glyphPos1 > m_GlyphCount)
		{
			int stop =1;
		}
		//assert(glyphPos0 < glyphPos1);
		while(glyphPos0 >= glyphPos1)
		{
			charPos1	= getNextBreakPos(charPos1);
			glyphPos1	= getGlyphPos(
										charPos1
										,&runIndex1
						);
		}

		wordWidth	= getGlyphsWidth(glyphPos0, glyphPos1);
		if(   charPos1	< 0	|| charPos1  >	m_CharCount
			||glyphPos1	< 0	|| glyphPos1 >	m_GlyphCount
			||runIndex1	< 0	|| runIndex1 >=	m_RunCount  )
			throw UspException();

		//uspFont		= m_pFontManager->getUspFont(m_pRunList[runIndex0].fontIndex);
		
		//int clustPos	= charPos0;

		
		//SelectObject(*pDC,uspFont->hFont);
		if(dx + wordWidth > lineWidth)
		{
			// new line
			if(lineCount + 1 >= m_subLineBufferLength - 1)
			{
				m_subLineBufferLength += 10;
				if(m_pSubLineList == NULL)
					throw UspException();
				size_t size = sizeof(SUBLINE);
				try
				{
					reAllocate();
					m_pSubLineList  = (SUBLINE*)realloc(m_pSubLineList, /*200*/size * m_subLineBufferLength);
					//m_pVisAttrList	= (VISATTR*)realloc(m_pVisAttrList ,sizeof(WORD)* m_GlyphBufferLen);
					//m_pSubLineList = (SUB_LINE*)realloc(m_pSubLineList, size * m_subLineBufferLength);
				}
				catch(...)
				{
					throw UspException();
				}
				if(m_pSubLineList == NULL) 
					throw UspException();
			}
			


			dx =	0 ;
			//dy +=	dY;	

			

			if(charPos0<0||charPos0>m_CharCount
			||glyphPos0<0||glyphPos0>m_GlyphCount
			||runIndex0<0||runIndex0>=m_RunCount)
			throw UspException();

			m_pSubLineList[lineCount].runIndex	= runIndex0;
			m_pSubLineList[lineCount].glyphPos	= glyphPos0;
			m_pSubLineList[lineCount].charPos	= charPos0;
			m_pSubLineList[lineCount].isUpdata	= false;
			//WCHAR *line = m_pText + charPos0;
			if(charPos0<0)throw UspException();
			lineCount ++;
		}


		//drawBacground(
		//	pDC,
		//	dx,
		//	dy,
		//	charPos0,
		//	charPos1,
		//	runIndex0,
		//	glyphPos0
		//);

		dx += wordWidth;
		if(runIndex1 != runIndex0)//if run count >2
		{
			//dx -= m_pRunList[runIndex0].abc.abcC;
			for(int i= 1;i<runIndex1-runIndex0;i++)
			{
				dx += (m_pRunList[runIndex0 + i].abc.abcB + m_pRunList[runIndex0 + i].abc.abcA + m_pRunList[runIndex0 + i].abc.abcC);
			}

			//dx -= m_pRunList[runIndex1].abc.abcA;
		}

		m_pSubLineList[lineCount-1].width = dx;

		//printf("r%d,g%d,c%d,w%d",
		//	m_pSubLineList[lineCount].runIndex ,
		//	m_pSubLineList[lineCount].glyphPos,
		//	m_pSubLineList[lineCount].charPos,
		//	m_pSubLineList[lineCount].width
		//);

		

	}
	//lineCount ++;
	m_pSubLineList[lineCount].charPos	= m_CharCount;
	m_subLineCount = lineCount;
	if(m_subLineCount>20)
	{
		int I=0;
	}
	/*updataSelection();*/
	return m_subLineCount;
}
void GlyfData::updateSubLineInfo()
{
	for(UINT i=0;i<m_subLineCount;i++)
	{
		if(m_pSubLineList[i].isUpdata == false)
		{
			updataCharSel(m_pSubLineList[i].charPos, m_pSubLineList[i+1].charPos - m_pSubLineList[i].charPos);
			m_pSubLineList[i].isUpdata = true;
		}
	}
}
void GlyfData::drawSubLine(HDC *pDC, int lineIndex,int x,int y)
{
	//this
	if(m_CharCount == 0) return;


	if(lineIndex	>= m_subLineCount)throw UspException();
	int stCharPos	= m_pSubLineList[lineIndex].charPos;
	int enCharPos	= m_pSubLineList[lineIndex + 1].charPos;
	int runIndex	= m_pSubLineList[lineIndex].runIndex;
	int glyphPos	= m_pSubLineList[lineIndex].glyphPos;
	if(   stCharPos	>=	m_CharCount
		||enCharPos	>	m_CharCount
		||runIndex	>=	m_RunCount
		||glyphPos	>	m_GlyphCount
		||stCharPos	<	0
		||enCharPos	<	0
		||runIndex	<	0
		||glyphPos	<	0  )
		throw UspException();
	RECT selRect={-1,-1,-1,-1};
	HRGN selRgn;
	bool allSelected		= false;
	bool partialSelected	= false;
	if(m_selStart <= stCharPos && m_selStart + m_selLength >= enCharPos)
	{
		allSelected = true;
	}
	if(m_selLength > 0)
	{
		int selEnd = m_selStart + m_selLength;
		if( (m_selStart >= stCharPos && m_selStart <  enCharPos)
		  ||(selEnd		>  stCharPos && selEnd     <= enCharPos))
		  
		  partialSelected = true;
	}

	/*int isRgn = */
	//int ret = GetClipRgn(*pDC,oldRgn);
	//if(ret == -1)
	//	throw UspException();
	//if(m_pSubLineList[lineIndex].isUpdata == false)
	//{
	//	updataCharSel(stCharPos,enCharPos - stCharPos);
	//	m_pSubLineList[lineIndex].isUpdata = true;
	//}
	int phoneticY;
	bool fTesterMode =m_pFontManager->isTesterMode();
	if(fTesterMode)
	{
		phoneticY	= y - m_pFontManager->getPhoneticFontInternalLeading();
		y			= y + (int)m_pFontManager->getPhoneticOffset();
	}
	drawBackground(pDC, x, y, stCharPos, enCharPos, runIndex, glyphPos, &selRect);
	if(selRect.right < selRect.left) throw UspException();
	selRgn = CreateRectRgnIndirect(&selRect);
	
	if(!allSelected)
	{
		ExcludeClipRect(*pDC, selRect.left, selRect.top, selRect.right, selRect.bottom);
		drawChars(pDC, x, y, stCharPos, enCharPos, runIndex, glyphPos, fTesterMode);

	}

	if(partialSelected || allSelected)
	{
		HBRUSH bBrush	= CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
		SelectClipRgn(*pDC,selRgn);
		FillRect(*pDC, &selRect,bBrush);
		drawSelection(pDC, x, y, stCharPos, enCharPos, runIndex, glyphPos);
		DeleteObject(bBrush);
	}
	SelectClipRgn(*pDC,NULL);
	DeleteObject(selRgn);
	if(fTesterMode)
		drawGaligs(pDC, x, phoneticY , stCharPos, enCharPos, runIndex, glyphPos);

}


int GlyfData::correctMongolian(WCHAR *pText, UINT start, UINT end)
{
	for(int i = start; i < end; i++)
	{
		if((int)pText[i] == 0x180e)//
		{

			m_pLogAttrList[i].fCharStop		= 0;
			m_pLogAttrList[i].fWhiteSpace	= 0;
			if(i < end - 1)
				m_pLogAttrList[i+1].fSoftBreak=0;
		}
	}
	return 0;
}
int GlyfData::getMongolianScriptID()
{
	WCHAR tmp[]={0x1800,'\0'};
	ITEM  item[2];
	int count;
	HRESULT hr = ScriptItemize(tmp,1,2,NULL,NULL,item,&count);
	return item[0].a.eScript;
}
//inline int GlyfData::getLineHeight()
//{
//	return m_maxAscent + m_maxDescent;
//}

//HRESULT drawClust(int clustPos,HDC *pDC,int x,int y)
//{
//	HGDIOBJ
//	obj = SelectObject(*pDC,CreateSolidBrush(RGB(0,0,0)));
//}
int GlyfData::getGlyphsWidth(int stGlyphPos,int enGlyphPos)
{
	if(stGlyphPos >= enGlyphPos) throw UspException();
	if(enGlyphPos >  m_GlyphCount)throw UspException();
	int width = 0;
	while(stGlyphPos<enGlyphPos)
		width += m_pWidthList[stGlyphPos++];
	return width;
}


int	GlyfData::getGlyphPos(int charPos ,int *pRunIndex)
{
	if(*pRunIndex > m_RunCount || charPos> m_CharCount) 
		throw UspException();

	if(charPos == m_CharCount) return m_GlyphCount;
	while(charPos >= m_pRunList[*pRunIndex + 1].charPos && *pRunIndex< m_RunCount) 
		(*pRunIndex)++;
	return m_pRunList[*pRunIndex].glyphPos + m_pClusterList[charPos];
}

//POINT GlyfData::getXyFromCharPos(int charPos)
//{
//
//	return ;
//}
BOOL GlyfData::getCharPosFromSubLine(int subLineNo, int X, CHAR_POS* pCharPos, CHAR_LOC* pCharLoc)
{
	if (pCharPos == NULL )
	{
		return FALSE;
	}

	CHAR_POS&ret	= *pCharPos;
	ret.index		= 0;
	ret.trailing	= 0;

	if(m_CharCount == 0)
	{
		if(pCharLoc != NULL)
		{
			pCharLoc->subLine	= 0;
			pCharLoc->x			= 0;
		}
		return TRUE;
	}
	int maxLineWidth= m_pSubLineList[subLineNo].width;
	
	if(X < 0)
	{
		X = 0;
	}
	if(X >= maxLineWidth)
	{
		X = maxLineWidth;
	}

	int x			= X;
	int runX;
	int runIndex	= getRunFromLineAndX(subLineNo,x, &runX);//getRunFromXy( x, y,&xInRun);

	if(runIndex >= m_RunCount) 
		throw UspException();

		//

			;
	//if(m_recentlyUsedRun > 0 && runIndex == m_recentlyUsedRun && m_recentlyUsedSubLine == subLineNo )
	//{
	//	runX	= m_recentlyUsedRunX;
	//}else
	//{
	//	runX	= getRunXInSubLine(runIndex,subLineNo);
	//}
	int xInRun		= x - runX;
	int charPos		= -1;
	int trailing	= -100;

	
	
	HRESULT hr ;

	hr = ScriptXtoCP(
		xInRun,
		m_pRunList[runIndex].charCount,
		m_pRunList[runIndex].glyphCount,
		m_pClusterList	+ m_pRunList[runIndex].charPos,
		m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
		m_pWidthList	+ m_pRunList[runIndex].glyphPos,
		&m_pRunList[runIndex].scriptAnalyze,
		&charPos,
		&trailing
	);
	
	if(hr == S_OK)
	{
		ret.index		= m_pRunList[runIndex].charPos + charPos;
		ret.trailing	= trailing;


		if(pCharLoc != NULL)
		{
			ScriptCPtoX(
				charPos,
				trailing,
				m_pRunList[runIndex].charCount,
				m_pRunList[runIndex].glyphCount,
				m_pClusterList	+ m_pRunList[runIndex].charPos,
				m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
				m_pWidthList	+ m_pRunList[runIndex].glyphPos,
				&m_pRunList[runIndex].scriptAnalyze,
				(int*)&pCharLoc->x
			);
			pCharLoc->x			+= runX ;
			pCharLoc->subLine	 = subLineNo;
		}
		return TRUE;
	}
	else
		throw UspException();
	return FALSE;
}
/*
BOOL GlyfData::getCharPosFromSubLine(int subLineNo, int X, CHAR_POS* pCharPos, POINT* pPoint)
{
	CHAR_POS&ret	= *pCharPos;
	ret.index		= 0;
	ret.trailing	= 0;
	int maxLineWidth= m_pSubLineList[subLineNo].width;
	
	if(X < 0)
	{
		ret.index	= m_pSubLineList[subLineNo].charPos;
		ret.trailing= 0;
		return TRUE;
	}
	if(X >= maxLineWidth)
	{
		ret.trailing= 1;
		if(subLineNo < m_subLineCount - 1)
			ret.index	= m_pSubLineList[subLineNo + 1].charPos - 1;
		else
			ret.index	= m_CharCount -	1;
		
		return TRUE;
	}

	int x			= X;
	int runIndex	= getRunFromLineAndX(subLineNo,x);//getRunFromXy( x, y,&xInRun);

	if(runIndex >= m_RunCount) 
		throw UspException();

	int runX		= getRunXInSubLine(runIndex,subLineNo);
	int xInRun		= x - runX;
	int charPos		= -1;
	int trailing	= -100;

	
	
	HRESULT hr ;

	hr = ScriptXtoCP(
		xInRun,
		m_pRunList[runIndex].charCount,
		m_pRunList[runIndex].glyphCount,
		m_pClusterList	+ m_pRunList[runIndex].charPos,
		m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
		m_pWidthList	+ m_pRunList[runIndex].glyphPos,
		&m_pRunList[runIndex].scriptAnalyze,
		&charPos,
		&trailing
	);
	
	if(hr == S_OK)
	{
		ret.index		= m_pRunList[runIndex].charPos + charPos;
		ret.trailing	= trailing;


		if(pPoint != NULL)
		{
			ScriptCPtoX(
				charPos,
				trailing,
				m_pRunList[runIndex].charCount,
				m_pRunList[runIndex].glyphCount,
				m_pClusterList	+ m_pRunList[runIndex].charPos,
				m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
				m_pWidthList	+ m_pRunList[runIndex].glyphPos,
				&m_pRunList[runIndex].scriptAnalyze,
				(int*)&pPoint->x
			);
			pPoint->x += runX;
			pPoint->y = subLineNo * getLineHeight();
		}
		return TRUE;
	}
	else
		throw UspException();
	return FALSE;
}
*/
CHAR_POS& GlyfData::getCharPosFromSubLine(int subLineNo,int X)
{
	CHAR_POS		ret (0,0,0) ;
	int maxLineWidth= m_pSubLineList[subLineNo].width;
	
	if(X < 0)
	{
		ret.index	= m_pSubLineList[subLineNo].charPos;
		ret.trailing= 0;
		return ret;
	}
	if(X >= maxLineWidth)
	{
		ret.trailing= 1;
		if(subLineNo < m_subLineCount - 1)
			ret.index	= m_pSubLineList[subLineNo + 1].charPos - 1;
		else
			ret.index	= m_CharCount -	1;
		
		return ret;
	}

	int x			= X;
	int runIndex	= getRunFromLineAndX(subLineNo,x);//getRunFromXy( x, y,&xInRun);

	if(runIndex >= m_RunCount) 
		throw UspException();

	int runX		= getRunXInSubLine(runIndex,subLineNo);
	int xInRun		= x - runX;
	int charPos		= -1;
	int trailing	= -100;

	
	
	HRESULT hr ;

	hr = ScriptXtoCP(
		xInRun,
		m_pRunList[runIndex].charCount,
		m_pRunList[runIndex].glyphCount,
		m_pClusterList	+ m_pRunList[runIndex].charPos,
		m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
		m_pWidthList	+ m_pRunList[runIndex].glyphPos,
		&m_pRunList[runIndex].scriptAnalyze,
		&charPos,
		&trailing
	);
	
	if(hr == S_OK)
	{
		ret.index		= m_pRunList[runIndex].charPos + charPos;
		ret.trailing	= trailing;
		return ret;
	}
	else
		throw UspException();
}
/*
CHAR_POS& GlyfData::getCharPos(int X,int Y)
{
	int subLineNo	= min(Y/getLineHeight(),m_subLineCount -1);
	return getCharPosFromSubLine(subLineNo,X);
}
*/
BOOL GlyfData::getCharPos(CHAR_LOC* pCharLoc, CHAR_POS* pCharPos)
{
	if (pCharPos == NULL || pCharLoc == NULL || pCharLoc->subLine < 0 )
	{
		return FALSE;
	}

	if(m_CharCount == 0)
	{
		if(pCharLoc != NULL)
		{
			pCharLoc->subLine	= 0;
			pCharLoc->x			= 0;
			pCharPos->index		= 0;
			pCharPos->trailing	= 0;
			return TRUE;
		}
		else 
			return FALSE;
	}
	if(pCharLoc->subLine >= m_subLineCount)
		return FALSE;

	int runX;
	int maxLineWidth	= m_pSubLineList[pCharLoc->subLine].width;
	int x				= min(maxLineWidth, max(0, pCharLoc->x));
	int runIndex		= getRunFromLineAndX(pCharLoc->subLine, x, &runX);//getRunFromXy( x, y,&xInRun);
	int xInRun			= x - runX;
	//int charPos			= -1;
	//int trailing		= -100;

	if(runIndex >= m_RunCount) 
		throw UspException();
	
	HRESULT hr = ScriptXtoCP(
		xInRun,
		m_pRunList[runIndex].charCount,
		m_pRunList[runIndex].glyphCount,
		m_pClusterList	+ m_pRunList[runIndex].charPos,
		m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
		m_pWidthList	+ m_pRunList[runIndex].glyphPos,
		&m_pRunList[runIndex].scriptAnalyze,
		&pCharPos->index,
		&pCharPos->trailing
	);
	
	if(hr == S_OK)
	{
		
		hr = ScriptCPtoX(
			pCharPos->index,
			pCharPos->trailing,
			m_pRunList[runIndex].charCount,
			m_pRunList[runIndex].glyphCount,
			m_pClusterList	+ m_pRunList[runIndex].charPos,
			m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
			m_pWidthList	+ m_pRunList[runIndex].glyphPos,
			&m_pRunList[runIndex].scriptAnalyze,
			(int*)&pCharLoc->x
		);
		pCharPos->index		+= m_pRunList[runIndex].charPos;
		if(pCharLoc->subLine < m_subLineCount - 1 && pCharPos->index == m_pSubLineList[pCharLoc->subLine + 1].charPos && pCharPos->trailing == 0)
		{
			pCharPos->index--;
			pCharPos->trailing = 1;
		}
		if(hr == S_OK)
		{
			pCharLoc->x			+= runX ;
			return TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}
/*
BOOL GlyfData::getCharPos(int X, int Y, CHAR_POS* pCharPos, CHAR_LOC* pCharLoc)
{
	int h = getLineHeight();
	int subLineNo	= min(Y/h,m_subLineCount - 1);

	//WCHAR b[50];
	//wsprintf(b,L"subLineNo %d\n",subLineNo);
	if(subLineNo != pCharLoc->subLine)
	{
		int stop = 1;
	}
	//OutputDebugString(b)/*;
	return getCharPosFromSubLine(subLineNo,X,pCharPos,pCharLoc);
}
*/
int GlyfData::getRunXInSubLine(int runIndex,int lineIndex)
{
	if(m_recentlyUsedRun >= 0 && runIndex == m_recentlyUsedRun && m_recentlyUsedSubLine == lineIndex )
	{
		return m_recentlyUsedRunX;
	}
	if(runIndex >= m_RunCount)

		throw UspException();
	if(lineIndex >= m_subLineCount)
		throw UspException();
	if(runIndex < m_pSubLineList[lineIndex].runIndex)
		throw UspException();
	if(lineIndex < m_subLineCount - 1 
		&& runIndex >= m_pSubLineList[lineIndex + 1].runIndex
		&& m_pSubLineList[lineIndex + 1].charPos == m_pRunList[m_pSubLineList[lineIndex + 1].runIndex].charPos)
		throw UspException();

	int curRunIndex = m_pSubLineList[lineIndex].runIndex;
	int x	= 0;
	if(m_pRunList[curRunIndex].charPos < m_pSubLineList[lineIndex].charPos)
	{
		x = -(getGlyphsWidth(m_pRunList[curRunIndex].glyphPos,m_pSubLineList[lineIndex].glyphPos));
		//curRunIndex ++;
	}
	while(curRunIndex < runIndex)
	{
		x += m_pRunList[curRunIndex].abc.abcA;
		x += m_pRunList[curRunIndex].abc.abcB;
		x += m_pRunList[curRunIndex].abc.abcC;
		curRunIndex++;
	}

	m_recentlyUsedRun		= runIndex;
	m_recentlyUsedSubLine	= lineIndex;
	m_recentlyUsedRunX		= x;

	return m_recentlyUsedRunX;
}
BOOL GlyfData::CharPosToInfo(int charPos, __out int* pLine, __out int* pRun, int* pRunX )
{
	int lineIndex	= getLineFromCharPos(charPos);
	int runIndex	= getRunFromCharPos(charPos);

	if(pLine)
	{
		*pLine	= lineIndex;
	}
	if(pRun)
	{
		*pRun	= runIndex;
	}
	if(pRunX)
	{
		*pRunX	= getRunXInSubLine(runIndex, lineIndex);
	}
	return TRUE;
}
//BOOL GlyfData::getInfoFromCharPos(int charPos, __out int* pLine, __out int* pRun, int* pRunX)
//{
//	int lineIndex	= getLineFromCharPos(charPos);
//	int runIndex	= getRunFromCharPos(charPos);
//
//	if(pLine)
//	{
//		*pLine	= lineIndex;
//	}
//	if(pRun)
//	{
//		*pRun	= runIndex;
//	}
//	if(pRunX)
//	{
//		*pRunX	= getRunXInSubLine(runIndex, lineIndex);
//	}
//	return TRUE;
//}
BOOL GlyfData::getCharLocation(const CHAR_POS *charPos, __out CHAR_LOC* charLoc)
{

	int lineIndex	= 0;//= charLoc->subLine;
	int runIndex	= 0;//= getRunFromCharPos(charPos->index);
	int runX		= 0;//= getRunXInSubLine(runIndex,lineIndex);
	if(m_CharCount == 0)
	{
		if(charLoc != NULL)
		{
			charLoc->subLine	= 0;
			charLoc->x			= 0;
			charLoc->cp			= 0;
		}
		return TRUE;
	}
	CharPosToInfo(
		 charPos->index /*+ charPos->trailing*/
		,&lineIndex
		,&runIndex
		,&runX
	);
	//assert(runX >= 0);
	if(runIndex<0)
	{
		int i=0;
	}
	charLoc->subLine	= getLineFromCharPos(charPos->index);
	charLoc->cp			= (charPos->index + charPos->trailing) - m_pSubLineList[charLoc->subLine].charPos;
	int charPosInRun	= charPos->index - m_pRunList[runIndex].charPos ;	
	
	//WCHAR * text = this->m_pText + charPos->index;

	int xInRun;
		ScriptCPtoX(
			charPosInRun,
			charPos->trailing,
			m_pRunList[runIndex].charCount,
			m_pRunList[runIndex].glyphCount,
			m_pClusterList	+ m_pRunList[runIndex].charPos,
			m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
			m_pWidthList	+ m_pRunList[runIndex].glyphPos,
			&m_pRunList[runIndex].scriptAnalyze,
			&xInRun
		);
	charLoc->x		= runX + xInRun;
	return TRUE;
}
BOOL GlyfData::getCharLocation(const CHAR_POS &charPos, __out CHAR_LOC* charLoc)
{

	int lineIndex	= 0;//= charLoc->subLine;
	int runIndex	= 0;//= getRunFromCharPos(charPos->index);
	int runX		= 0;//= getRunXInSubLine(runIndex,lineIndex);
	if(m_CharCount == 0)
	{
		if(charLoc != NULL)
		{
			charLoc->subLine	= 0;
			charLoc->x			= 0;
			charLoc->cp			= 0;
		}
		return TRUE;
	}
	CharPosToInfo(
		 charPos.index /*+ charPos->trailing*/
		,&lineIndex
		,&runIndex
		,&runX
	);
	//assert(runX >= 0);
	if(runIndex<0)
	{
		int i=0;
	}
	charLoc->subLine	= getLineFromCharPos(charPos.index);
	charLoc->cp			= (charPos.index + charPos.trailing) - m_pSubLineList[charLoc->subLine].charPos;
	int charPosInRun	= charPos.index - m_pRunList[runIndex].charPos ;	
	
	//WCHAR * text = this->m_pText + charPos->index;

	int xInRun;
		ScriptCPtoX(
			charPosInRun,
			charPos.trailing,
			m_pRunList[runIndex].charCount,
			m_pRunList[runIndex].glyphCount,
			m_pClusterList	+ m_pRunList[runIndex].charPos,
			m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
			m_pWidthList	+ m_pRunList[runIndex].glyphPos,
			&m_pRunList[runIndex].scriptAnalyze,
			&xInRun
		);
	charLoc->x		= runX + xInRun;
	return TRUE;
}
CHAR_LOC& GlyfData::getCharLocation(CHAR_POS *charPos)
{
	CHAR_LOC	tmp;
	tmp.subLine		= getLineFromCharPos(charPos->index);
	int lineIndex	= tmp.subLine;
	int runIndex	= getRunFromCharPos(charPos->index);
	int runX		= getRunXInSubLine(runIndex,lineIndex);
	int charPosInRun= charPos->index - m_pRunList[runIndex].charPos ;	
	
	//WCHAR * text = this->m_pText + charPos->index;

	int xInRun;
		ScriptCPtoX(
			charPosInRun,
			charPos->trailing,
			m_pRunList[runIndex].charCount,
			m_pRunList[runIndex].glyphCount,
			m_pClusterList	+ m_pRunList[runIndex].charPos,
			m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
			m_pWidthList	+ m_pRunList[runIndex].glyphPos,
			&m_pRunList[runIndex].scriptAnalyze,
			&xInRun
		);
	tmp.x		= runX + xInRun;
	return tmp;
}
int GlyfData::getLineCount()
{
	return m_subLineCount?m_subLineCount:1;
}
/*
BOOL GlyfData::getLocation(const CHAR_POS *charPos, __out POINT* pPoint)
{	
	int cp = charPos->index + charPos->trailing;
	if( cp == 0 || m_CharCount == 0 )
	{
		pPoint->x = 0;
		pPoint->y = 0;
		return TRUE;
	}
	else if(cp >= m_CharCount)
	{
		pPoint->x = m_pSubLineList[m_subLineCount - 1].width;
		pPoint->y = getLineHeight() * (m_subLineCount - 1);
		return TRUE;
	}
	else{

		int lineIndex	= 0;//getLineFromCharPos(cp);
		int runIndex	= 0;//getRunFromCharPos(cp);
		int runX		= 0;//getRunXInSubLine(runIndex,lineIndex);


		CharPosToInfo(charPos->index,&lineIndex,&runIndex,&runX);
		int charPosInRun= charPos->index - m_pRunList[runIndex].charPos ;	
		
		//WCHAR * text = this->m_pText + charPos->index;

		int xInRun;
			ScriptCPtoX(
				charPosInRun,
				charPos->trailing,
				m_pRunList[runIndex].charCount,
				m_pRunList[runIndex].glyphCount,
				m_pClusterList	+ m_pRunList[runIndex].charPos,
				m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
				m_pWidthList	+ m_pRunList[runIndex].glyphPos,
				&m_pRunList[runIndex].scriptAnalyze,
				&xInRun
			);

		pPoint->y		= getLineHeight() * lineIndex;
		pPoint->x		= runX + xInRun;
		return TRUE;
	}
	return FALSE;
}
POINT GlyfData::getLocation(const CHAR_POS *charPos)
{
	POINT point;
	int cp = min(charPos->index + charPos->trailing, this->m_CharCount);
	if(m_CharCount == 0)
	{
		point.x = 0;
		point.y = 0;
		return point;
	}
	if(cp == m_CharCount)
	{
		point.x = m_pSubLineList[m_subLineCount - 1].width;
		point.y =  getLineHeight() * (m_subLineCount - 1);
		return point;
	}

	int lineIndex	= getLineFromCharPos(cp);
	int runIndex	= getRunFromCharPos(cp);
	int runX		= getRunXInSubLine(runIndex,lineIndex);
	int charPosInRun= charPos->index - m_pRunList[runIndex].charPos ;	
	
	WCHAR * text = this->m_pText + charPos->index;

	int xInRun;
		ScriptCPtoX(
			charPosInRun,
			charPos->trailing,
			m_pRunList[runIndex].charCount,
			m_pRunList[runIndex].glyphCount,
			m_pClusterList	+ m_pRunList[runIndex].charPos,
			m_pVisAttrList	+ m_pRunList[runIndex].glyphPos,
			m_pWidthList	+ m_pRunList[runIndex].glyphPos,
			&m_pRunList[runIndex].scriptAnalyze,
			&xInRun
		);

	point.y		= getLineHeight() * lineIndex;
	point.x		= runX + xInRun;
	return point;
}
*/
int GlyfData::getLineFromCharPos(int charPos)
{
	
	if(charPos <= 0)
		return 0;
	if(charPos >= m_CharCount)
		return m_subLineCount - 1;
	int line = 0;
	while( charPos >= m_pSubLineList[line + 1].charPos 
		&& line < m_subLineCount) 
		line++;
	return line;
}
int GlyfData::getRunFromCharPos(int charPos)
{
	if(charPos <= 0)
		return 0;
	if(charPos >= m_CharCount) return m_RunCount ? m_RunCount - 1 : 0;
	int run = 0;
	while( charPos >= m_pRunList[run + 1].charPos 
		&& run + 1 < m_RunCount) 
		run ++;
	return run;
}
int GlyfData::getMaxRunIndexInLine(int subLineIndex)
{
	if(subLineIndex == m_subLineCount -1)
		return m_RunCount -1;
	int rIndex = m_pSubLineList[subLineIndex + 1].runIndex;
	if(m_pSubLineList[subLineIndex + 1].charPos > m_pRunList[rIndex].charPos)
		return rIndex;
	else if(m_pSubLineList[subLineIndex + 1].charPos == m_pRunList[rIndex].charPos)
		return rIndex - 1 ;
	else
		throw UspException();
}
int GlyfData::getRunFromLineAndX(int subLineIndex, int x, int* pRunX)
{
	int runIndex		= m_pSubLineList[subLineIndex].runIndex;
	int endRunIndex		= getMaxRunIndexInLine( subLineIndex);
	int left			= getRunXInSubLine(runIndex,subLineIndex) ;
	int right			= left;
	

	//while(x > runRightBound && runIndex == endRunIndex)
	//{
	//	runIndex ++;
	//	if(runIndex == endRunIndex)return runIndex;
	//	runRightBound +=  
	//		( m_pRunList[runIndex].abc.abcA
	//		+ m_pRunList[runIndex].abc.abcB
	//		+ m_pRunList[runIndex].abc.abcC);
	//}

	if( x < left) throw MnException();
	int r = runIndex;
	for( ; r < endRunIndex ; r++)
	{
		
		right	+=	m_pRunList[r].abc.abcA
				+	m_pRunList[r].abc.abcB
				+	m_pRunList[r].abc.abcC;
		if(left <= x && x < right)
		{
			break;
		}
		left	= right;
	}

	if(pRunX)
	{
		*pRunX = left;
	}
	return r;
}
/*
int GlyfData::getRunFromXy(int x,int y,int* pXInRun)
{
	 
	int subLineNo	= min(this->m_subLineCount -1, y / getLineHeight());
	int runIndex	= m_pSubLineList[subLineNo].runIndex;
	int width		= 0 ;
	int dx			= x ;
	int tmpRunWidth;
	if(m_pSubLineList[subLineNo].charPos!=m_pRunList[runIndex].charPos)
	{
		int 
			stGlyphPos	= m_pSubLineList[subLineNo].glyphPos;//getGlyphPos(.charPos,&runIndex);
		width		= getGlyphsWidth(stGlyphPos,m_pRunList[runIndex+1].glyphPos);
		if(dx <= width)
		{
			*pXInRun = -dx ;
			return runIndex;
		}
		runIndex ++ ;
	}

	while( dx > width && runIndex < m_RunCount)
	{
		dx			= dx - width ;
		*pXInRun	= dx;
		width		= m_pRunList[runIndex].abc.abcB + m_pRunList[runIndex].abc.abcC + m_pRunList[runIndex].abc.abcA;
		tmpRunWidth = getGlyphsWidth(m_pRunList[runIndex].glyphPos,m_pRunList[runIndex+1].glyphPos);
		runIndex++;
	}
	
	if(runIndex == m_RunCount )
		*pXInRun = width ;
	runIndex--;
	return runIndex;

	

	//m_pSubLineList[subLineNo].runIndex 
	
}
*/

int	GlyfData::getWordStartPos(int charPos, __out CHAR_POS*)
{
	charPos -- ;
	while(charPos > 0)
	{
		if(m_pLogAttrList[charPos].fWordStop == 1)
		{
			break;
		}
		charPos --;
	}
	return charPos;
}
int	GlyfData::getWordEndPos(int charPos, __out CHAR_POS*)
{
	charPos ++ ;
	while(charPos < m_CharCount)
	{
		if(m_pLogAttrList[charPos].fWordStop == 1)
		{
			break;
		}
		charPos ++;
	}
	return charPos;
}
int	GlyfData::getNextBreakPos(int charPos)
{
	//sint pos=charPos+1;
	if(charPos >= m_CharCount)
		throw UspException();
	while(charPos < m_CharCount&&m_pLogAttrList[++charPos].fSoftBreak ==0 );
	return charPos;
}

ABC GlyfData::getClusterABCWidth(HDC* pDC,SCRIPT_CACHE *pCache,int clGlyphPos,int length)
{
	
	ABC abc		= {0};	
	
	
	HRESULT
	hr = ScriptGetGlyphABCWidth(
		*pDC,
		pCache,
		m_pGlyphList[clGlyphPos],
		&abc
	);
	if(hr!= S_OK) throw UspException();

	if(length > 1)
	{
		ABC tmpAbc;
		hr = ScriptGetGlyphABCWidth(
			*pDC,
			pCache,
			m_pGlyphList[clGlyphPos + length -1],
			&tmpAbc
		);
		if(hr!=S_OK) throw UspException();
		int width	= 0;
		for(int i = clGlyphPos; i < length ;i++)
			width += m_pWidthList[i];
		abc.abcC	= tmpAbc.abcC;
		abc.abcB	= width;
	}
	
	return abc;
}


HRESULT GlyfData::drawGaligs(HDC *pDC, int dx, int dy, int stCharPos, int enCharPos, int rIndex, int stGlyphPos)
{
	int runIndex		= rIndex;
	int x				= dx;
	int y				= dy;
	int clustPos		= stCharPos;
	int clGlyphPos		= stGlyphPos;

	int runIndex0 = runIndex;
	if(stGlyphPos < 0) 
		clGlyphPos = getGlyphPos(stCharPos,&runIndex0);
	//int nextClustPos	= clustPos + run->charCount;
	int clWidth			= 0;
	int clCharCount,clGlyphCount;

	//COLORREF	col;
	//RECT		rect;
	RUN			*run	= &m_pRunList[runIndex];
	MNFont*		pFont	= &m_pFontManager->m_fontList[run->fontIndex];
	//TEXTMETRIC	tm;
	//HRESULT hr;

	HFONT hfont			= m_pFontManager->getPhoneticFont();
	SetBkMode(*pDC,TRANSPARENT);
	SelectObject(*pDC, hfont);
	SetTextColor(*pDC, RGB(0,0,255));
	

	
	while( clustPos < enCharPos && runIndex < m_RunCount) 
	{
		clCharCount	= 1;
		clGlyphCount= 1;
		clWidth		= 0;

		if(clustPos >= m_pRunList[runIndex + 1].charPos && runIndex < m_RunCount)
		{
			runIndex++;
			run		= &m_pRunList[runIndex];
			//pFont	= &m_pFontManager->m_fontList[run->fontIndex];
			//if(pFont->m_hFont == 0 )
			//	if(!pFont->createFont()) throw UspException();
			//SelectObject(*pDC, pFont->m_hFont);
		}
		//WCHAR* t = m_pText + clustPos;
		while( clustPos + clCharCount < m_pRunList[runIndex + 1].charPos
			&& m_pClusterList[clustPos + clCharCount] == m_pClusterList[clustPos + clCharCount - 1] 
			&& clustPos + clCharCount < enCharPos)
		{
			clCharCount ++;
		}

		while( m_pVisAttrList[clGlyphPos + clGlyphCount].fClusterStart == 0 
			&& clGlyphPos + clGlyphCount < m_GlyphCount)
			clGlyphCount ++;
		
		for(int i =0 ; i< clGlyphCount; i++)
			clWidth += m_pWidthList[clGlyphPos + i];
		//ABC abc = getClusterABCWidth(
		//	pDC,
		//	&run->font.m_cache,
		//	clGlyphPos,
		//	clGlyphCount
		//);
//clWidth =0 ;
		//if(clWidth != abc.abcA + abc.abcB + abc.abcC)
		//{
		//	throw UspException();
		//}
		//if()


		//RECT rect	= {x + abc.abcA, y , x + abc.abcB , y + m_maxAscent + m_maxDescent};
		
		//col			= textAttr->getFgColor(clustPos);
		//HGDIOBJ obj = SelectObject(*pDC,CreateSolidPen(RGB(0,0,255)));
		//WCHAR* text = m_pText + clustPos;
		//char * cltext = clustStart + clustPos;
	
		int dy = 0;
		int dx = 0;
		if(run->scriptAnalyze.eScript == 17)
		{
			dy =  pFont->tm.tmAscent;
			dx =  -pFont->tm.tmDescent;
		}

		//hr = ScriptTextOut(
		//	*pDC ,
		//	&pFont->m_cache,
		//	x ,
		//	y + m_pFontManager->m_maxAscent - pFont->tm.tmAscent  ,
		//	0,//ETO_CLIPPED,//ETO_OPAQUE ,
		//	NULL ,
		//	&run->scriptAnalyze,
		//	NULL,
		//	0,
		//	m_pGlyphList + clGlyphPos,//,run->glyphPos,
		//	clGlyphCount,//run->glyphCount,
		//	this->m_pWidthList + clGlyphPos,//run->glyphPos,
		//	NULL,
		//	this->m_pGoffsetList + clGlyphPos//run->glyphPos
		//);
		//
		int *glag_index = m_pGalig + clustPos;
		if(run->scriptAnalyze.eScript == m_mongolianScriptId )
		{
			if(clCharCount > 1 || GaligMap[*glag_index ].galig != '\0')
			{
				WCHAR phonecStr[200];
				phonecStr[0]='\0';
				for(int i = 0; i < clCharCount; i++)
				{
					lstrcat(phonecStr, GaligMap[*(glag_index + i)].galig);
				}
				//int align = SetTextAlign(*pDC, TA_CENTER);
				int c = lstrlen(phonecStr);
				int w = m_pFontManager->m_PhoneticFontTm.tmAveCharWidth * c;
				ExtTextOut(*pDC, x + ( clWidth - w ) / 2, y , 0, 0, phonecStr,c,NULL);
				//SetTextAlign(*pDC, align);
			}
		}

		x			+= clWidth;
		clustPos	+= clCharCount;
		clGlyphPos	+= clGlyphCount; 
	}
	return 0;
}
HRESULT GlyfData::drawVowelCheck(HDC *pDC, int dx, int dy, int stCharPos, int enCharPos, int rIndex, int stGlyphPos)
{
	int runIndex		= rIndex;
	int x				= dx;
	int y				= dy;
	int clustPos		= stCharPos;
	int clGlyphPos		= stGlyphPos;

	int runIndex0		= runIndex;
	if(stGlyphPos < 0) 
		clGlyphPos = getGlyphPos(stCharPos,&runIndex0);
	//int nextClustPos	= clustPos + run->charCount;
	int clWidth			= 0;
	int clCharCount, clGlyphCount;

	//COLORREF	col;
	//RECT		rect;
	RUN			*run	= &m_pRunList[runIndex];
	MNFont*		pFont	= &m_pFontManager->m_fontList[run->fontIndex];
	//TEXTMETRIC	tm;
	//HRESULT hr;

	HFONT hfont			= m_pFontManager->getPhoneticFont();
	
	int wordId			= 0 ;
	
	while( clustPos < enCharPos && runIndex < m_RunCount) 
	{
		clCharCount	= 1;
		clGlyphCount= 1;
		clWidth		= 0;

		if(clustPos >= m_pRunList[runIndex + 1].charPos && runIndex < m_RunCount)
		{
			runIndex++;
			run		= &m_pRunList[runIndex];
			wordId  = 0;
			//pFont	= &m_pFontManager->m_fontList[run->fontIndex];
			//if(pFont->m_hFont == 0 )
			//	if(!pFont->createFont()) throw UspException();
			//SelectObject(*pDC, pFont->m_hFont);
		}
		//WCHAR* t = m_pText + clustPos;
		while( clustPos + clCharCount < m_pRunList[runIndex + 1].charPos
			&& m_pClusterList[clustPos + clCharCount] == m_pClusterList[clustPos + clCharCount - 1] 
			&& clustPos + clCharCount < enCharPos)
		{
			clCharCount ++;
		}

		while( m_pVisAttrList[clGlyphPos + clGlyphCount].fClusterStart == 0 
			&& clGlyphPos + clGlyphCount < m_GlyphCount)
			clGlyphCount ++;
		
		for(int i =0 ; i< clGlyphCount; i++)
			clWidth += m_pWidthList[clGlyphPos + i];
		//ABC abc = getClusterABCWidth(
		//	pDC,
		//	&run->font.m_cache,
		//	clGlyphPos,
		//	clGlyphCount
		//);
//clWidth =0 ;
		//if(clWidth != abc.abcA + abc.abcB + abc.abcC)
		//{
		//	throw UspException();
		//}
		//if()




		//RECT rect	= {x + abc.abcA, y , x + abc.abcB , y + m_maxAscent + m_maxDescent};
		
		//col			= textAttr->getFgColor(clustPos);
		//HGDIOBJ obj	= SelectObject(*pDC,CreateSolidPen(RGB(0,0,255)));
		//WCHAR* text	= m_pText + clustPos;
		//char * cltext = clustStart + clustPos;
	
	

		if(run->wordlist[wordId]->nVolType == MN_VOWEL_WRONG)

		{
			HPEN pen	= CreatePen(PS_SOLID, 0, RGB(255,0,0));
			HPEN oldpen = (HPEN)SelectObject(*pDC,pen);
			MoveToEx(*pDC, x, y + m_pFontManager->m_maxAscent, 0);
			LineTo(*pDC,x + clWidth, y + m_pFontManager->m_maxAscent);
			SelectObject(*pDC,oldpen);
			DeleteObject(pen);

		}
		//hr = ScriptTextOut(
		//	*pDC ,
		//	&pFont->m_cache,
		//	x ,
		//	y + m_pFontManager->m_maxAscent - pFont->tm.tmAscent  ,
		//	0,//ETO_CLIPPED,//ETO_OPAQUE ,
		//	NULL ,
		//	&run->scriptAnalyze,
		//	NULL,
		//	0,
		//	m_pGlyphList + clGlyphPos,//,run->glyphPos,
		//	clGlyphCount,//run->glyphCount,
		//	this->m_pWidthList + clGlyphPos,//run->glyphPos,
		//	NULL,
		//	this->m_pGoffsetList + clGlyphPos//run->glyphPos
		//);
		//
		//int *glag_index = m_pGalig + clustPos;


		x			+= clWidth;
		clustPos	+= clCharCount;
		clGlyphPos	+= clGlyphCount; 
		if(run->wordlist[wordId]->nCharPos + run->wordlist[wordId]->nCharLen >= clustPos) 
		{
			wordId++;
		}
	}
	return 0;
}
HRESULT GlyfData::drawChars(HDC *pDC, int dx, int dy, int stCharPos, int enCharPos, int rIndex, int stGlyphPos, bool fDrawPhonec)
{
	int runIndex		= rIndex;
	int x				= dx;
	int y				= dy;
	int clustPos		= stCharPos;
	int clGlyphPos		= stGlyphPos;

	int runIndex0 = runIndex;
	if(stGlyphPos < 0) 
		clGlyphPos = getGlyphPos(stCharPos,&runIndex0);
	//int nextClustPos	= clustPos + run->charCount;
	int clWidth			= 0;
	int clCharCount,clGlyphCount;

	COLORREF	col;
	//RECT		rect;
	RUN			*run	= &m_pRunList[runIndex];
	MNFont*		pFont	= &m_pFontManager->m_fontList[run->fontIndex];
	if(pFont->m_hFont == 0)
		if(!pFont->createFont()) throw UspException();
	SetBkMode(*pDC,TRANSPARENT);
	SelectObject(*pDC, pFont->m_hFont);
	
	int wordId			= 0 ;
	HRESULT hr;
	while( clustPos < enCharPos && runIndex < m_RunCount) 
	{
		clCharCount	= 1;
		clGlyphCount= 1;
		clWidth		= 0;

		if(clustPos >= m_pRunList[runIndex + 1].charPos && runIndex < m_RunCount)
		{
			runIndex++;
			run		= &m_pRunList[runIndex];
			wordId	= 0 ;
			pFont	= &m_pFontManager->m_fontList[run->fontIndex];
			if(pFont->m_hFont == 0 )
				if(!pFont->createFont()) throw UspException();
			SelectObject(*pDC, pFont->m_hFont);
		}
		//WCHAR* t = m_pText + clustPos;
		//output
		while( clustPos + clCharCount < m_pRunList[runIndex + 1].charPos
			&& m_pClusterList[clustPos + clCharCount] == m_pClusterList[clustPos + clCharCount - 1] 
			&& clustPos + clCharCount < enCharPos)
		{
			clCharCount ++;
			
		}
		if(clCharCount == 2)
		{
			int stop =1;
		}
		int wordCount = run->wordlist.size();
		static COLORREF col2[2] = {RGB(255,0,0),RGB(0,0,255)};
		static BOOL cId = FALSE;
		if(/*wordId >=0 &&*/ wordId < wordCount)
		{
			int nextword = run->wordlist[wordId]->nCharPos + run->wordlist[wordId]->nCharLen;
			while(wordId < wordCount && nextword <= clustPos )
			{
				wordId++;
				cId = !cId;
				nextword = run->wordlist[wordId]->nCharPos + run->wordlist[wordId]->nCharLen;
			}
		}
		while( m_pVisAttrList[clGlyphPos + clGlyphCount].fClusterStart == 0 
			&& clGlyphPos + clGlyphCount < m_GlyphCount)
			clGlyphCount ++;
		
		for(int i =0 ; i< clGlyphCount; i++)
			clWidth += m_pWidthList[clGlyphPos + i];
		//ABC abc = getClusterABCWidth(
		//	pDC,
		//	&run->font.m_cache,
		//	clGlyphPos,
		//	clGlyphCount
		//);
//clWidth =0 ;
		//if(clWidth != abc.abcA + abc.abcB + abc.abcC)
		//{
		//	throw UspException();
		//}
		//if()


		//RECT rect	= {x + abc.abcA, y , x + abc.abcB , y + m_maxAscent + m_maxDescent};
		
		//col			= textAttr->getFgColor(clustPos);
		//HGDIOBJ obj = SelectObject(*pDC,CreateSolidPen(RGB(0,0,255)));
		//WCHAR* text = m_pText + clustPos;
		//char * cltext = clustStart + clustPos;
		


		if(m_pFontManager->isTesterMode())
		{
			if(m_textAttr[clustPos].isMonCtrlChar)
				col = RGB(255,0,0);
			//else if(clGlyphCount > 1 && clCharCount > 1)
			//	col = RGB(255, 0 , 255);
			//else if(clGlyphCount >1)
			//	col = RGB(0	 , 0 , 255);
			//else if(clCharCount > 1)
			//	col = RGB(255 , 125, 125);
			else
				col = m_textAttr[clustPos].fgColor;
		}
		else
			col = m_textAttr[clustPos].fgColor;
		SetTextColor(*pDC,col);


		hr = ScriptTextOut(
			*pDC ,
			&pFont->m_cache,
			x ,
			y + m_pFontManager->m_maxAscent - pFont->tm.tmAscent  ,
			ETO_OPAQUE,//ETO_CLIPPED,//ETO_OPAQUE ,
			NULL ,
			&run->scriptAnalyze,
			NULL,
			0,
			m_pGlyphList + clGlyphPos,//m_pGlyphList + clGlyphPos,//,run->glyphPos,
			clGlyphCount,//run->glyphCount,
			this->m_pWidthList + clGlyphPos,//run->glyphPos,
			NULL,
			this->m_pGoffsetList + clGlyphPos//run->glyphPos
		);

		if(m_textAttr[clustPos].underLine)
		{
			HPEN pen	= CreatePen(PS_SOLID, 0, col);
			HPEN oldpen = (HPEN)SelectObject(*pDC,pen);
			MoveToEx(*pDC, x, y , 0);
			LineTo(*pDC,x + clWidth, y );
			SelectObject(*pDC,oldpen);
			DeleteObject(pen);
		}
		
		if(m_pFontManager->isTesterMode() && wordId < wordCount && run->wordlist[wordId]->nVolType == MN_VOWEL_WRONG)

		{	

			
			HPEN pen	= CreatePen(PS_SOLID, 1, col2[0]);
			HPEN oldpen = (HPEN)SelectObject(*pDC,pen);
			MoveToEx(*pDC, x, y , 0);
			LineTo(*pDC,x + clWidth, y );
			SelectObject(*pDC,oldpen);
			DeleteObject(pen);
			

		}
				x	+= clWidth;

		clustPos	+= clCharCount;
		clGlyphPos	+= clGlyphCount; 
		//if(run->wordlist.size() > 0 && clustPos >= run->wordlist[wordId]->nCharPos + run->wordlist[wordId]->nCharLen ) 
		//{
		//	wordId++;cId = !cId;
		//}
	}
	return 0;
}
HRESULT GlyfData::drawSelection(HDC *pDC, int dx,int dy,int stCharPos,int enCharPos,int rIndex,int stGlyphPos)
{
	int runIndex		= rIndex;
	int x				= dx;
	int y				= dy;
	int clustPos		= stCharPos;
	int clGlyphPos		= stGlyphPos;

	int runIndex0 = runIndex;
	if(stGlyphPos < 0) 
		clGlyphPos = getGlyphPos(stCharPos,&runIndex0);
	//int nextClustPos	= clustPos + run->charCount;
	int clWidth			= 0;
	int clCharCount,clGlyphCount;

	//COLORREF	col;
	//RECT		rect;
	RUN			*run	= &m_pRunList[runIndex];
	MNFont		*pFont	= &m_pFontManager->m_fontList[run->fontIndex];
	if(pFont->m_hFont == 0) 
		if(!pFont->createFont()) throw UspException();

	SetBkMode(*pDC,TRANSPARENT);
	SelectObject(*pDC,pFont->m_hFont);
	//SetBkMode(*pDC, OPAQUE);
	//SetBkColor(*pDC, GetSysColor(COLOR_HIGHLIGHT));
	SetTextColor(*pDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
	

	HRESULT hr;
	while( clustPos < enCharPos && runIndex < m_RunCount) 
	{
		clCharCount	= 1;
		clGlyphCount= 1;
		clWidth		= 0;

		if(clustPos >= m_pRunList[runIndex + 1].charPos && runIndex < m_RunCount)
		{
			runIndex++;
			run		= &m_pRunList[runIndex];
			pFont	= &m_pFontManager->m_fontList[run->fontIndex];
			if(pFont->m_hFont == 0 )
				if(!pFont->createFont()) throw UspException();
			SelectObject(*pDC, pFont->m_hFont);
		}
		while( clustPos + clCharCount < m_pRunList[runIndex + 1].charPos
			&& m_pClusterList[clustPos + clCharCount] == m_pClusterList[clustPos + clCharCount - 1] 
			&& clustPos + clCharCount < enCharPos)
		{
			clCharCount ++;
		}

		while( m_pVisAttrList[clGlyphPos + clGlyphCount].fClusterStart == 0 
			&& clGlyphPos + clGlyphCount < m_GlyphCount)
			clGlyphCount ++;
		
		for(int i =0;i< clGlyphCount;i++)
			clWidth += m_pWidthList[clGlyphPos + i];
		//ABC abc = getClusterABCWidth(
		//	pDC,
		//	&pFont->m_cache,
		//	clGlyphPos,
		//	clGlyphCount
		//);

		//clWidth = abc.abcA + abc.abcB + abc.abcC;
		//if(abc.abcB != clWidth)
		//{
		//	int stop =1;
		//}


		RECT rect	= {x , y , x + clWidth, y + m_pFontManager->getLineHeight()};
		
		
		//HGDIOBJ obj = SelectObject(*pDC,CreateSolidPen(RGB(0,0,255)));
		//WCHAR* text = m_pText + clustPos;
		
		int dy = 0;
		int dx = 0;
		if(run->scriptAnalyze.eScript == 17)
		{
			dy =  pFont->tm.tmAscent;
			dx =  -pFont->tm.tmDescent;
		}
		//else if(run->scriptAnalyze.eScript == m_mongolianScriptId && m_pText[clustPos] == 0x202F)
		//{

		//	//int yy= y + m_pFontManager->getPhoneticFontInternalLeading() + (int)m_pFontManager->getPhoneticOffset();
		//	WCHAR u180a=(WCHAR)0x180a;
		//	ExtTextOut(*pDC, x, y  , 0,NULL, &u180a,1,NULL);
		//	
		//}
		hr = ScriptTextOut(
			*pDC ,
			&pFont->m_cache,
			x ,
			y + m_pFontManager->m_maxAscent - pFont->tm.tmAscent  ,
			0  ,
			0 ,
			&run->scriptAnalyze,
			NULL,
			0,
			m_pGlyphList + clGlyphPos,//,run->glyphPos,
			clGlyphCount,//run->glyphCount,
			this->m_pWidthList + clGlyphPos,//run->glyphPos,
			NULL,
			this->m_pGoffsetList + clGlyphPos//run->glyphPos
		);
		//
		if(m_textAttr[clustPos].underLine)
		{
			HPEN pen	= CreatePen(PS_SOLID, 0, m_textAttr[clustPos].fgColor);
			HPEN oldpen = (HPEN)SelectObject(*pDC,pen);
			MoveToEx(*pDC, x, y + m_pFontManager->m_maxAscent, 0);
			LineTo(*pDC,x + clWidth ,y + m_pFontManager->m_maxAscent);
			SelectObject(*pDC,oldpen);
			DeleteObject(pen);
		}
				x	+= clWidth;
		clustPos	+= clCharCount;
		clGlyphPos	+= clGlyphCount; 


	}
	return 0;
}
//
HRESULT GlyfData::drawBackground(HDC *pDC, int dx,int dy,int stCharPos,int enCharPos,int rIndex,int stGlyphPos,RECT* selRect)
{
	if(selRect==NULL) throw UspException();
	int runIndex		= rIndex;
	int x				= dx;
	int y				= dy;
	int clustPos		= stCharPos;
	int clGlyphPos		= stGlyphPos;

	int runIndex0 = runIndex;
	if(stGlyphPos < 0) 
		clGlyphPos = getGlyphPos(stCharPos,&runIndex0);
	//int nextClustPos	= clustPos + run->charCount;
	int clWidth			= 0;
	int clCharCount,clGlyphCount;

	HBRUSH		brush;
	COLORREF	col;
	//RECT		rect;
	RUN			*run	= &m_pRunList[runIndex];
	MNFont		*pFont	= &m_pFontManager->m_fontList[run->fontIndex];
	if(pFont->m_hFont == 0)
		if(!pFont->createFont()) throw UspException();
	SetBkMode(*pDC,TRANSPARENT);
	//SelectObject(*pDC,run->font.m_hFont);
	
	BOOL selStart		= TRUE;
	//SetBkMode(*pDC,TRANSPARENT);
	//SelectObject(*pDC,uspFont->hFont);
	

	//HRESULT hr;
	while( clustPos < enCharPos && runIndex < m_RunCount) 
	{
		clCharCount	= 1;
		clGlyphCount= 1;
		clWidth		= 0;

		if(clustPos >= m_pRunList[runIndex + 1].charPos && runIndex<this->m_RunCount)
		{
			runIndex++;
			run		= &m_pRunList[runIndex];
			pFont	= &m_pFontManager->m_fontList[run->fontIndex];
			if(pFont->m_hFont == 0)
				if(!pFont->createFont()) throw UspException();
			//SelectObject(*pDC,uspFont->hFont);
		}
		while( clustPos + clCharCount < m_pRunList[runIndex + 1].charPos
			&& m_pClusterList[clustPos + clCharCount] == m_pClusterList[clustPos + clCharCount - 1] 
			&& clustPos + clCharCount < enCharPos)
		{
			clCharCount ++;
		}

		while( m_pVisAttrList[clGlyphPos + clGlyphCount].fClusterStart == 0 
			&& clGlyphPos + clGlyphCount < m_GlyphCount)
			clGlyphCount ++;
		
		for(int i =0;i< clGlyphCount;i++)
			clWidth += m_pWidthList[clGlyphPos + i];
		if(clWidth < 0)
		{
			int haha = 0 ;
		}
		//ABC abc = getClusterABCWidth(
		//	pDC,
		//	&uspFont->fontCache,
		//	clGlyphPos,
		//	clGlyphCount
		//);

		//clWidth = abc.abcA + abc.abcB + abc.abcC;
		//if()


		//RECT rect	= {x + abc.abcA, y , x + abc.abcB , y + m_maxAscent + m_maxDescent};
		//col		= m_pTextAttr->getFgColor(clustPos);
		for(int i = 0; i < clCharCount; i++)
		{
			RECT 
			rect = {
				x + clWidth* i/clCharCount, 
				y , 
				x + clWidth*(i+1)/clCharCount , 
				y + m_pFontManager->getLineHeight()
			};
			
			int cp = clustPos + i ;
			if(cp >= m_selStart && cp < m_selStart + m_selLength)
			{
				if(selStart)
				{
					selRect->top	= rect.top;
					selRect->left	= rect.left;
					selRect->bottom	= rect.bottom;
					selStart		= FALSE;
				}

				selRect->right	= rect.right;
				
				assert(rect.right > 0);
				col	= GetSysColor(COLOR_HIGHLIGHT);
			}
			else
			{
				col	= m_textAttr[cp].bgColor;
				if(brush = CreateSolidBrush(col))
				{
					//FillRect(*pDC,&rect,brush);
					DeleteObject(brush);
				}
			}

		}
		//HGDIOBJ obj = SelectObject(*pDC,CreateSolidPen(RGB(0,0,255)));
		//WCHAR * text = m_pText + clustPos;

		//

				x	+= clWidth;
		clustPos	+= clCharCount;
		clGlyphPos	+= clGlyphCount; 


	}
	return 0;
}
void GlyfData::updataCharAttr(UINT charPos,UINT length)
{
	updataCharSel( charPos, length);
}
void GlyfData::updataCharSel(UINT charPos,UINT length)
{
	//printf("update char sel,start%d,length%d\n", m_selStart, m_selLength);
	int i /*,end*/;
	int	 selStart	= max(charPos, m_selStart);
	int	 selLenght	= (m_selLength + m_selStart) - selStart;

	i = charPos;

	while(i < selStart)
	{
		m_textAttr[i++].selcted = false;
	}

	while(i < selStart + selLenght)
	{
		m_textAttr[i++].selcted = true;
	}

	while(i < charPos + length)
	{
		m_textAttr[i++].selcted = false;
	}

}
/*
HRESULT GlyfData::drawBacground2(HDC *pDC, int dx,int dy,int stCharPos,int enCharPos,int runIndex,int stGlyphPos)
{
	int x				= dx;
	int y				= dy;
	int clustPos		= stCharPos;
	int clGlyphPos		= stGlyphPos;

	int runIndex0 = runIndex;
	if(stGlyphPos < 0) 
		clGlyphPos = getGlyphPos(stCharPos,&runIndex0);
	//int nextClustPos	= clustPos + run->charCount;
	int clWidth			= 0;
	int clCharCount,clGlyphCount;

	HBRUSH		brush;
	COLORREF	col;
	//RECT		rect;
	//RUN			*run	= &m_pRunList[runIndex];
	//USPFONT*	uspFont = m_pFontManager->getUspFont(run->fontIndex);

	//HRESULT hr;
	while( clustPos < enCharPos)
	{
		clCharCount	= 1;
		clGlyphCount= 1;
		clWidth		= 0;
		while( 
			clustPos + clCharCount < m_pRunList[runIndex + 1].charPos
			&& m_pClusterList[clustPos + clCharCount] == m_pClusterList[clustPos + clCharCount - 1] 
			&& clustPos + clCharCount < enCharPos)
		{
			clCharCount ++;
		}

		while( m_pVisAttrList[clGlyphPos + clGlyphCount].fClusterStart == 0 
			&& clGlyphPos + clGlyphCount < m_GlyphCount)
			clGlyphCount ++;
		
		for(int i =0;i< clGlyphCount;i++)
			clWidth += m_pWidthList[clGlyphPos + i];

		//RECT *pRect = new RECT[clCharCount];
		for(int i = 0; i < clCharCount; i++)
		{
			RECT rect	= {x + clWidth* i/clCharCount, y , x + clWidth*(i+1)/clCharCount , y + m_maxAscent + m_maxDescent};
			if(m_textAttr[clustPos + 1].selcted)
			{
				col	= GetSysColor(COLOR_HIGHLIGHT);
			}
			else
				col	= m_textAttr[clustPos + i].bgColor;
			if(brush = CreateSolidBrush(col))
			{
				FillRect(*pDC,&rect,brush);
				DeleteObject(brush);
			}
		}
				x	+= clWidth;
		clustPos	+= clCharCount;
		clGlyphPos	+= clGlyphCount; 


	}
	return 0;
}


HRESULT GlyfData::drawRun2(RUN *run,HDC *pDC,int x,int y)
{
	USPFONT* uspFont	= m_pFontManager->getUspFont(run->fontIndex);
	
	//HRESULT hr = m_pFontManager->getFont(run->fontIndex,uspFont);
	//if(hr!=S_OK) return hr;
	HBRUSH	brush;
	HGDIOBJ	obj			= SelectObject(*pDC,uspFont->hFont);
	
	int clustPos		= run->charPos;
	int clGlyphPos		= run->glyphPos;
	int nextClustPos	= clustPos + run->charCount;
	int clWidth			= 0;
	int clCharCout,clGlyphCount;
	
	HRESULT hr;
	while( clustPos < nextClustPos)
	{
		clCharCout	= 1;
		while(this->m_pClusterList[clustPos + clCharCout] == this->m_pClusterList[clustPos + clCharCout - 1])
		{
			clCharCout++;
		}
		clGlyphCount= 1;
		while(this->m_pVisAttrList[clGlyphPos + clGlyphCount].fClusterStart == 0 && clGlyphPos + clGlyphCount < m_GlyphCount)
			clGlyphCount ++;
		clWidth		= 0;
		for(int i =0;i< clGlyphCount;i++)
			clWidth += m_pWidthList[clGlyphPos + i];

		//if(x + clWidth>500) {x = 0 ; y += (m_maxAscent + m_maxDescent);}

		RECT rect	= {x , y , x + clWidth , y + m_maxAscent + m_maxDescent};
		COLORREF 
			col		= m_pTextAttr->getBgColor(clustPos);
		//brush		= CreateSolidBrush(col);
		if(brush = CreateSolidBrush(col))
		{
			FillRect(*pDC,&rect,brush);
			DeleteObject(brush);
		}
		
		col			= m_pTextAttr->getFgColor(clustPos);
		//HGDIOBJ obj = SelectObject(*pDC,CreateSolidPen(RGB(0,0,255)));
		SetTextColor(*pDC,col);

		hr = ScriptTextOut(
			*pDC ,
			&uspFont->fontCache ,
			x ,
			y + m_maxAscent - uspFont->tm.tmAscent ,
			ETO_CLIPPED,//ETO_OPAQUE ,
			&rect ,
			&run->scriptAnalyze,
			NULL,
			0,
			m_pGlyphList + clGlyphPos,//,run->glyphPos,
			clGlyphCount,//run->glyphCount,
			this->m_pWidthList + clGlyphPos,//run->glyphPos,
			NULL,
			this->m_pGoffsetList + clGlyphPos//run->glyphPos
		);
		
		if(m_pTextAttr->getUnderLine(clustPos))
		{
			HPEN pen	= CreatePen(PS_SOLID,0,col);
			HPEN oldpen = (HPEN)SelectObject(*pDC,pen);
			MoveToEx(*pDC,x,y + m_maxAscent + 2,0);
			LineTo(*pDC,x + clWidth ,y + m_maxAscent + 2);
			SelectObject(*pDC,oldpen);
			DeleteObject(pen);
		}
				x	+= clWidth;
		clustPos	+= clCharCout;
		clGlyphPos	+= clGlyphCount; 
	}
//LPOUTLINETEXTMETRIC
	return S_OK;

}
*/
/*
HRESULT GlyfData::drawRun(RUN *run,HDC *pDC,int x,int y)
{
	USPFONT* uspFont = m_pFontManager->getUspFont(run->fontIndex);
	//HRESULT hr = m_pFontManager->getFont(run->fontIndex,uspFont);
	//if(hr!=S_OK) return hr;
	HGDIOBJ
	//obj = SelectObject(*pDC,CreateSolidBrush(RGB(0,0,0)));
	obj = SelectObject(*pDC,uspFont->hFont);
//LPOUTLINETEXTMETRIC

	RECT rect = {x , y , x + run->abc.abcB , y + m_maxAscent + m_maxDescent};
	return ScriptTextOut(
		*pDC ,
		&uspFont->fontCache ,
		x ,
		y + m_maxAscent - uspFont->tm.tmAscent ,
		ETO_OPAQUE ,
		&rect ,
		&run->scriptAnalyze,
		NULL,
		0,
		m_pGlyphList + run->glyphPos,
		run->glyphCount,
		this->m_pWidthList + run->glyphPos,
		NULL,
		this->m_pGoffsetList + run->glyphPos
	);
}
*/
void GlyfData::replaceMonCtrlCharGlyf(MNRun* run, WCHAR *pText, int length, WORD replaceGlyphId)
{

	//int c = GetGlyphIndices(*pDC, &u180a, 1, pAltGlyph, 0);
	//int j = run->glyphPos;
	for(int i = 0; i < run->charCount; i++)
	{
		if(pText[i] == 0x202F || pText[i] == 0x180e)
		{
			m_pGlyphList[run->glyphPos + m_pClusterList[i + run->charPos]] = replaceGlyphId;
			this->m_textAttr[i + run->charPos].isMonCtrlChar = true;
		}
	}
}
void GlyfData::shapeAndPlace(HDC hdc, WCHAR* pText, int length)
{
	HDC tmpDC;
	if(hdc)
	{
		tmpDC = hdc;
	}
	else
	{
		tmpDC = GetDC(NULL);
	}
	HRESULT hr;
	this->m_GlyphCount = 0;

	for(int i = 0; i< this->m_RunCount; i++)
	{
		//hr = shapeRun(&this->m_pRunList[i],&tmpDC);
		//hr = placeRun(&this->m_pRunList[i],&tmpDC);

		hr = shapeAndPlaceRun(&this->m_pRunList[i], &tmpDC, pText + m_pRunList[i].charPos, m_pRunList[i].charCount);
		if(hr != S_OK) 
		{
			int stop =1;
			return ;
		}
		if(m_pClusterList[0] ==  52685) 
		{
			int stop =1;
		}
		hr = ScriptBreak(
			pText + m_pRunList[i].charPos,
			m_pRunList[i].charCount,
		   &m_pRunList[i].scriptAnalyze,
			this->m_pLogAttrList + m_pRunList[i].charPos
		);
		if(m_pClusterList[0] ==  52685) 
		{
			int stop =1;
		}
		if(hr != S_OK) 
		{
			int stop =1;
			return ;
		}

		if(m_pClusterList[0] ==  52685) 
		{
			int stop =1;
		}
		if(m_pRunList[i].scriptAnalyze.eScript == m_mongolianScriptId ) //Mongolian
		{
			correctMongolian(
				pText,
				m_pRunList[i].charPos,
				m_pRunList[i+1].charPos
			);
		if(m_pClusterList[0] ==  52685) 
		{
			int stop =1;
		}
			if(1)
			{
				int wordstop1 = m_pRunList[i].charPos;
				//int wordstop2 ;
				int l ;
				int cp = m_pRunList[i].charPos;
				m_pRunList[i].ClearWordList();
				for(int j = 1; j < m_pRunList[i].charCount; j++)
				{
					if(m_pLogAttrList[j + cp].fWhiteSpace == 1 )
					{
						l = j + cp + 1 - wordstop1;
						m_pRunList[i].wordlist.push_back(new MNWord(wordstop1, l, CheckVowel(pText + wordstop1, l)));
						wordstop1 = j + cp + 1;
					}
					if(m_pClusterList[0] ==  52685) 
					{
						int stop =1;
					}
				}
				l = m_pRunList[i].charCount + m_pRunList[i].charPos - wordstop1;
				m_pRunList[i].wordlist.push_back(new MNWord(wordstop1, l, CheckVowel(pText + wordstop1, l)));
			}
		}
		if(i>0 && i<m_RunCount)
		{
			m_pLogAttrList[m_pRunList[i].charPos].fSoftBreak	= 1;
			m_pLogAttrList[m_pRunList[i].charPos].fCharStop		= 1;
			m_pLogAttrList[m_pRunList[i].charPos].fWordStop		= 1;
		}

		m_GlyphCount += this->m_pRunList[i].glyphCount;
		this->m_pRunList[i+1].glyphPos = m_GlyphCount;
	}
	if(m_pClusterList[0] ==  52685) 
	{
		int stop =1;
	}
	if(!hdc)
	{
		ReleaseDC(0,tmpDC);
	}

	assert(m_CharCount > 0 ? m_GlyphCount != 0 : 1);
}
HRESULT GlyfData::shapeAndPlaceRun(RUN *run, HDC *pDC, WCHAR* pText, LONG length)
{
	HRESULT hr;
	int changefont	= 0;
	int fontCount	= m_pFontManager->m_count;
	MNFont*	pFont	= &m_pFontManager->m_fontList[run->fontIndex];
	if(pFont->m_hFont == 0)
		if(!pFont->createFont()) throw UspException();
	HFONT oldFont	= (HFONT)SelectObject(*pDC, pFont->m_hFont);
	bool fHandle202F= false;
	//if(oldFont==NULL) return S_FALSE;
	//SCRIPT_CACHE sc ={0};
	int tmpCount	= 0;
	if(m_GlyphBufferLen	== m_GlyphCount)
		reAllocate();

	do
	{
		//if(m_GlyphBufferLen >= 2000){}
		SCRIPT_FONTPROPERTIES FontProperty = {0};
		FontProperty.cBytes = sizeof(SCRIPT_FONTPROPERTIES);
		HRESULT			hr2	= ScriptGetFontProperties(*pDC, &pFont->m_cache, &FontProperty);
	
		int realsize = this->m_GlyphBufferLen	- m_GlyphCount;
		int needsize = (int)run->charCount *1.5 + 16 + 20; // in document fit size is char_count * 1.5 + 16
		int fit_size = realsize > needsize ? needsize : realsize;

		hr = ScriptShape(
			*pDC,
			&pFont->m_cache,
			pText,
			run->charCount,
			fit_size, //can not handle big buffer sometime
			&run->scriptAnalyze,
			this->m_pGlyphList		+ run->glyphPos,
			this->m_pClusterList	+ run->charPos,
			this->m_pVisAttrList	+ run->glyphPos,
			&run->glyphCount
		);

		tmpCount++;
		
		if(hr == S_OK && changefont == 0)
		{
			
			for(int i = 0; i < run->glyphCount; i++)
			{
				if(m_pGlyphList[run->glyphPos + i] == FontProperty.wgDefault)
				{
					hr = USP_E_SCRIPT_NOT_IN_FONT;
					break;
				}
			}
			
		}
		if(hr == E_OUTOFMEMORY  )
		{
			reAllocate();
		}else if(realsize < needsize && hr==E_FAIL)
		{
			reAllocate();
		}
		else if(hr == E_INVALIDARG)
		{
			return hr;
		}
		else if(hr == USP_E_SCRIPT_NOT_IN_FONT) 
		{
			if(changefont == 0)
			{
				WCHAR fontname[50];
				if(!s_fallbackList.getFallbackFont(run->scriptAnalyze.eScript, fontname, 50))
				{
					int langid = PRIMARYLANGID(getScriptProperty(run->scriptAnalyze.eScript).langid);
					
					run->scriptAnalyze.eScript = SCRIPT_UNDEFINED;
					if(!s_fallbackList.getFallbackFont(run->scriptAnalyze.eScript, fontname, 50))
					{
						throw MnException();
					}
				}
				MNText mnfontName(fontname);
				LOGFONT lf;
				GetObject(pFont->m_hFont, sizeof(lf), &lf);
				bool ratate =false;
				if(run->scriptAnalyze.eScript == 17)
				{
					ratate = true;
				}
				run->fontIndex	= m_pFontManager->getFontIndex(
					mnfontName, 
					lf.lfHeight,
					lf.lfWeight ,
					lf.lfItalic,
					lf.lfUnderline,
					ratate
				);
				pFont = &m_pFontManager->m_fontList[run->fontIndex];

				if(pFont->m_hFont == 0)
				{
					if(!pFont->createFont()) throw UspException();
				}
				oldFont = (HFONT)SelectObject(*pDC, pFont->m_hFont);
				changefont ++;
			}
			else if(changefont == 1)
				run->scriptAnalyze.eScript = SCRIPT_UNDEFINED;
			else
			{
				throw UspException();
			}
		}
	}while(hr != S_OK);

	if(hr == E_OUTOFMEMORY)
	{
		int stop =1;
	}

	if(run->glyphCount == 0)
	{
		int stop =1;
	}

	if(m_pClusterList[0] == 52685)
	{
		int stop =1;
	}

	if(hr != S_OK) 
		return hr;
	//run->abc.abcB = 0;
	if(pText[0] == 'h')
	{
		int stop =1;
	}
	bool fTest = m_pFontManager->isTesterMode();
	if( fTest && run->scriptAnalyze.eScript == m_mongolianScriptId)
	{
		WORD AltGlyph;
		WORD *pAltGlyph = &AltGlyph;
		WCHAR u180a		= 0x180a;
		GetGlyphIndices(*pDC,&u180a,1,pAltGlyph, GGI_MARK_NONEXISTING_GLYPHS);
		replaceMonCtrlCharGlyf(run, pText, length, AltGlyph);
	}
	hr = ScriptPlace(
		*pDC,
		&pFont->m_cache ,
		this->m_pGlyphList		+ run->glyphPos ,
		run->glyphCount ,
		this->m_pVisAttrList	+ run->glyphPos ,
		&run->scriptAnalyze ,
		this->m_pWidthList		+ run->glyphPos ,
		this->m_pGoffsetList	+ run->glyphPos ,
		&run->abc
	);

	//if(fHandle202F)
	//{
	//	for(int i = 0; i < run->charCount; i++)
	//	{
	//		if(pText[i] == 0x202F)
	//		{
	//			 //m_pWidthList[run->glyphPos + m_pClusterList[i + run->charPos]] *=1.5; 
	//		}
	//	}
	//}
	if(*pText == '\t')
	{
		m_pWidthList[run->glyphPos] = pFont->tm.tmAveCharWidth * 4;
		run->abc.abcB += pFont->tm.tmAveCharWidth * 4;
	}
	if(m_pClusterList[0] == 52685)
	{
		int stop =1;
	}
	return hr;

}
/*
HRESULT GlyfData::shapeRun(RUN *run,HDC *pDC)
{
	USPFONT* uspFont	= m_pFontManager->getUspFont(run->fontIndex);
	HFONT oldFont		= (HFONT)SelectObject(*pDC,uspFont->hFont);
	//if(oldFont==NULL) return S_FALSE;
	//SCRIPT_CACHE sc ={0};
	return ScriptShape(
		*pDC,
		&uspFont->fontCache,
		this->m_pText + run->charPos,
		run->charCount,
		this->m_GlyphBufferLen - run->glyphPos, //error
		&run->scriptAnalyze,
		this->m_pGlyphList + run->glyphPos,
		this->m_pClusterList + run->charPos,
		this->m_pVisAttrList + run->glyphPos,
		&run->glyphCount
	);
}
*/
//HRESULT GlyfData::placeRun(RUN *run,HDC *pDC)
//{
//	USPFONT* uspFont = m_pFontManager->getUspFont(run->fontIndex);
//	SelectObject(*pDC,uspFont->hFont);
//
//	return ScriptPlace(
//		*pDC,
//		&uspFont->fontCache ,
//		this->m_pGlyphList		+ run->glyphPos ,
//		run->glyphCount ,
//		this->m_pVisAttrList	+ run->glyphPos ,
//		&run->scriptAnalyze ,
//		this->m_pWidthList		+ run->glyphPos ,
//		this->m_pGoffsetList	+ run->glyphPos ,
//		&run->abc
//	);
//}
void	GlyfData::freeRunBuffer()
{
	//free(m_pRunList		);	m_pRunList		= NULL;
}
void	GlyfData::freeGlyfBuffer()
{
	free(m_pVisAttrList);	m_pVisAttrList 	= NULL;//	= 
	free(m_pGlyphList);		m_pGlyphList 	= NULL;//		
	free(m_pWidthList);		m_pWidthList 	= NULL;//
	free(m_pGoffsetList);	m_pGoffsetList 	= NULL;//	= (G
}
void	GlyfData::freeCharBuffer()
{
	free(m_pClusterList);	m_pClusterList  = NULL;//
	free(m_pLogAttrList);	m_pLogAttrList  = NULL;//
}
void	GlyfData::freeItemBuffer()
{
	free(m_pItemList);
	m_pItemList = NULL;
}
void	GlyfData::freeSlineBuffer()
{
	free(m_pSubLineList);
	m_pSubLineList = NULL;
}
void	GlyfData::freeMemory()
{
	
	free(m_pGalig		);	m_pGalig		= NULL;
	free(m_pVisAttrList	);	m_pVisAttrList	= NULL;
	free(m_pLogAttrList	);	m_pLogAttrList	= NULL;
	free(m_pClusterList	);	m_pClusterList	= NULL;
	free(m_pGlyphList	);	m_pGlyphList	= NULL;
	free(m_pWidthList	);	m_pWidthList	= NULL;
	free(m_pGoffsetList	);	m_pGoffsetList	= NULL;
	free(m_pItemList	);	m_pItemList		= NULL;
	//free(m_pRunList		);	m_pRunList		= NULL;
	free(m_pSubLineList	);	m_pSubLineList	= NULL;
/*
	delete fSoftBreak  	;		fSoftBreak	= NULL;
	delete fWhiteSpace 	;		fWhiteSpace	= NULL;
	delete fCharStop   	;		fCharStop	= NULL;
	delete fWordStop   	;		fWordStop	= NULL;
	delete fInvalid    	;		fInvalid	= NULL;
	delete clustStart  	;		clustStart	= NULL;
	delete itemStart   	;		itemStart	= NULL;
	delete runStart    	;		runStart	= NULL;
*/
}
GlyfData::~GlyfData(void)
{
	//_CrtDumpMemoryLeaks();
	freeMemory();
	//_CrtDumpMemoryLeaks();
}
void GlyfData::preAllocate()
{
	//char base list
	//BOOL isNULL = FALSE ;
	this->m_pClusterList	= (WORD*)		malloc(sizeof(WORD)		* (this->m_CharCount + 1));
	this->m_pLogAttrList	= (LOGATTR*)	malloc(sizeof(LOGATTR)	* (this->m_CharCount + 1));
	this->m_pGalig			= (int*)		malloc(sizeof(int)	* (this->m_CharCount + 1));
	//this->m_pCharAttribute	= (ATTR*)		malloc(sizeof(ATTR)	* (this->m_CharCount + 1));
	//isNULL= isNULL & m_pClusterList;
	//initialize
	//ZeroMemory(m_pCharAttribute,	sizeof(ATTR) * (this->m_CharCount + 1));
	
	//glyph base list
	this->m_GlyphBufferLen	= 100;
	this->m_pVisAttrList	= (VISATTR*)	malloc(sizeof(WORD)		* m_GlyphBufferLen);
	this->m_pGlyphList		= (WORD*)		malloc(sizeof(WORD)		* m_GlyphBufferLen);
	this->m_pWidthList		= (int*)		malloc(sizeof(int)		* m_GlyphBufferLen);
	this->m_pGoffsetList	= (GOFFSET*)	malloc(sizeof(GOFFSET)	* m_GlyphBufferLen);
	
	//item base list
	this->m_ItemBufferLength= 20;
	this->m_pItemList		= (ITEM*)		malloc(sizeof(ITEM)		* m_ItemBufferLength);

	//run base list
	//this->m_RunBufferlen	= m_ItemBufferLength * 2;
	//this->m_pRunList		= (RUN*)		malloc(sizeof(RUN)		* m_RunBufferlen);

	this->m_subLineBufferLength = 10;
	//this->m_pSubLineList	= (SUBLINE*)	malloc(sizeof(SUBLINE)	* m_subLineBufferLength);
			

	if( m_pClusterList	== NULL|| 
		m_pVisAttrList	== NULL||
		m_pGlyphList	== NULL||
		m_pWidthList	== NULL||
		m_pGoffsetList	== NULL|| 
		m_pItemList		== NULL/*|| 
		m_pRunList		== NULL*/
	)
		throw UspAllocateMemFaildException();
}
void	GlyfData::reallocGlyfBuffer(UINT newSize)
{
	m_pVisAttrList		= (VISATTR*)	realloc(m_pVisAttrList,	sizeof(WORD)		* newSize);
	m_pGlyphList		= (WORD*)		realloc(m_pGlyphList,	sizeof(WORD)		* newSize);
	m_pWidthList		= (int*)		realloc(m_pWidthList,	sizeof(int)			* newSize);
	m_pGoffsetList		= (GOFFSET*)	realloc(m_pGoffsetList,	sizeof(GOFFSET)		* newSize);
	m_GlyphBufferLen	= newSize;
}
void	GlyfData::reallocCharBuffer(UINT newSize)
{
	m_pGalig			= (int*)		realloc(m_pGalig,		sizeof(int)			* newSize);
	m_pClusterList		= (WORD*)		realloc(m_pClusterList,	sizeof(WORD)		* newSize);
	m_pLogAttrList		= (LOGATTR*)	realloc(m_pLogAttrList,	sizeof(LOGATTR)		* newSize);
	m_textAttr.allocate(newSize);
	m_charBufferLength	= newSize;
}
void	GlyfData::reallocItemBuffer(UINT newSize)
{
	m_pItemList			= (ITEM*)		realloc(m_pItemList,	sizeof(ITEM)		* newSize);
	m_ItemBufferLength	= newSize;
}
void	GlyfData::reallocSlineBuffer(UINT newSize)
{
	m_pSubLineList		= (SUBLINE*)	realloc(m_pSubLineList,	sizeof(SUBLINE)		* newSize);
	m_subLineBufferLength= newSize;
}
void	GlyfData::reallocRunBuffer(UINT newSize)
{

	m_pRunList.resize(newSize,MNRun());
	//m_pRunList			= (RUN*)		realloc(m_pRunList,		sizeof(RUN)			* newSize);
	m_RunBufferlen		= newSize;
}	
void GlyfData::reAllocate()
{
	this->m_GlyphBufferLen += 100;
	this->m_pVisAttrList	= (VISATTR*)	realloc(m_pVisAttrList ,		sizeof(WORD)		* m_GlyphBufferLen);
	this->m_pGlyphList		= (WORD*)		realloc(m_pGlyphList ,			sizeof(WORD)		* m_GlyphBufferLen);
	this->m_pWidthList		= (int*)		realloc(m_pWidthList ,			sizeof(int)			* m_GlyphBufferLen);
	this->m_pGoffsetList	= (GOFFSET*)	realloc(m_pGoffsetList ,		sizeof(GOFFSET)		* m_GlyphBufferLen);
	if( m_pClusterList	== NULL|| 
		m_pVisAttrList	== NULL||
		m_pGlyphList	== NULL||
		m_pWidthList	== NULL||
		m_pGoffsetList	== NULL|| 
		m_pItemList		== NULL/*|| 
		m_pRunList		== NULL*/
	)
		throw UspAllocateMemFaildException ();
}
SCRIPT_PROPERTIES  GlyfData::getScriptProperty(int index)
{
	const SCRIPT_PROPERTIES ** ppScriptProperties;
	SCRIPT_PROPERTIES * ret = NULL;
	int ScriptCount;
	ScriptGetProperties(&ppScriptProperties,&ScriptCount);
	return *ppScriptProperties[index];
}
//void GlyfData::invertSelection(UINT charPos, UINT len)
//{
//	UINT endI = min(charPos + len , m_CharCount - 1);
//	for(UINT i = charPos; i < endI; i++)
//	{
//		m_textAttr[i].selcted = !m_textAttr[i].selcted;
//	}
//}
//void GlyfData::invertSelection(CHAR_POS& cp1, CHAR_POS& cp2)
//{
//	if(cp1.index > cp2.index) throw MnException();
//	UINT staI = max(cp1.index + cp1.trailing, 0);
//	UINT endI = min(cp2.index + cp1.trailing, m_CharCount - 1);
//	for(UINT i = staI; i <= endI; i++)
//	{
//		m_textAttr[i].selcted = !m_textAttr[i].selcted;
//	}
//}
int GlyfData::setSelect(int charPos, int len)
{
/*	int chgStart = m
		, chgEnd
	
	for(UINT i = 0 ; i <= m_subLineCount ; i++)
	{
		m_pSubLineList[i].isUpdata = false;
	}*/

	if(charPos > m_CharCount) 
	{
		m_selStart	= 0;
		m_selLength = 0;
		return 0;
	}

	if(charPos < 0)
	{
		m_selStart	= 0;
		m_selLength = max(0,len + charPos);
	}
	else
	{
		m_selStart	= charPos;
		m_selLength = len ;
	}
	if(m_selStart + m_selLength > m_CharCount)
	{
		m_selLength = m_CharCount - m_selStart;
	}

	
	//printf("select start:%d,length%d\n",m_selStart,m_selLength);
	return 0;
}

void GlyfData::setFgColor(UINT charPos, UINT len, COLORREF& col)
{
	m_textAttr.setFgColor(charPos,len,col);
}
void GlyfData::setBgColor(UINT charPos, UINT len, COLORREF& col)
{
	m_textAttr.setBgColor(charPos,len,col);
}

MNText& GlyfData::getFontName(UINT charPos)
{
	return m_textAttr.getFontName(charPos);
}
COLORREF& GlyfData::getFgColor(UINT charPos)
{
	return m_textAttr.getFgColor(charPos);
}
COLORREF& GlyfData::getBgColor(UINT charPos)
{
	return m_textAttr.getBgColor(charPos);
}


int GlyfData::getNextWordStop(int charPos)
{
	int i = charPos + 1;
	for(; i < m_CharCount; i++)
	{
		if(m_pLogAttrList[i].fWhiteSpace == 1 )
			break;
	}
	return i;
}
int GlyfData::getPrevWordStop(int charPos)
{
	int i = charPos;
	for(; i > 0; i--)
	{
		if(m_pLogAttrList[i].fWhiteSpace == 1 )
		{
			i++;
			break;
		}
	}
	return i;
}
BOOL GlyfData::getSlineStartPos(const CHAR_POS& charPos, __out CHAR_POS* pOutCharPos)
{
	CHAR_LOC cl;
	BOOL ret = getCharLocation(charPos ,&cl);
	if(m_pSubLineList == NULL)
		pOutCharPos->set(0,0,0);
	else
		pOutCharPos->set(charPos.logLine,m_pSubLineList[cl.subLine].charPos,0);
	return ret; 
}
BOOL GlyfData::getSlineEndPos(const CHAR_POS& charPos, __out CHAR_POS* pOutCharPos)
{
	CHAR_LOC cl;
	BOOL ret = getCharLocation(charPos ,&cl);
	if(cl.subLine < m_subLineCount - 2)
	{
		pOutCharPos->set(charPos.logLine,m_pSubLineList[cl.subLine + 1].charPos - 1 ,1);
	}
	else
	{
		pOutCharPos->set(charPos.logLine, m_CharCount, 0);
	}
	return ret; 
}