#include "UspData.h"

UspData::UspData(HWND hwnd,UspFontManager* fontManager,WCHAR *text,int length,TextAttribute *textAttr)
:m_Hwnd(hwnd),m_pFontManager(fontManager) ,m_pText(text),m_CharCount(length),
	m_pTextAttr(textAttr),m_maxAscent(0),m_maxDescent(0),m_GlyphCount(0),m_subLineCount(0)
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
}
//void UspData::init()
//{
//	p
//}


BOOL UspData::itemize(WCHAR* text,int length)
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
BOOL UspData::eqaul(ATTR* attr0,ATTR* attr1)
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

void UspData::createRunList()
{
	int run			= 0;
	int item		= 0;
	int charCount	= 1;
	this->m_pRunList[0].charPos   = 0;
	this->m_pRunList[0].fontIndex = this->m_pFontManager->getFontIndex( &m_pTextAttr->GetAttr(0));

	USPFONT* uspFont= m_pFontManager->getUspFont(m_pRunList[0].fontIndex);
	this->m_maxDescent = m_pFontManager->getUspFont(m_pRunList[0].fontIndex)->tm.tmDescent;
	this->m_maxAscent  = m_pFontManager->getUspFont(m_pRunList[0].fontIndex)->tm.tmAscent;
	for(int i=1 ;i<=this->m_CharCount;i++)
	{
		BOOL b = m_pTextAttr->canBreakRun(i-1,i);
		if(b || m_pItemList[item+1 ].iCharPos == i)
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
			this->m_pRunList[run].charPos   = i ;
			this->m_pRunList[run].fontIndex = 
				this->m_pFontManager->getFontIndex( &m_pTextAttr->GetAttr(i));
			if(this->m_pItemList[item + 1].iCharPos == i)item ++;
		}
		charCount++;
	}
	m_RunCount = run;
}

void UspData::mergeSimpleScripts()
{
	// global script-table, used for merging non-complex runs together :)
	const SCRIPT_PROPERTIES **propList;
	int					propCount;
	int					i =0;;

	// get pointer to the global script table
	ScriptGetProperties(&propList, &propCount);
	while(i<m_ItemCount-1)
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
//void UspData::drawEx(HDC *pDc,int x,int y,int lineWidth)
//{	int padding		= x ;
//	int tmpWidth	= 0;
//	int tmp			= 0;
//	for(int i= 0; i<m_RunCount; i++ )
//	{
//		//int runWidth = getRunWidth();
//		if( x + m_pRunList[i].abc.abcB > lineWidth + padding)
//		{
//			int charPos  = m_pRunList[i].charPos;
//			int remained = lineWidth + padding - x;// + m_pRunList[i].abc.abcB);
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
//			x = padding;
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
int UspData::breakLine(int lineWidth)
{
	int dx				= 0;
	//int dy				= 0;
	//int	dY				= (y < 0)? -getLineHeight() : getLineHeight();

	int lineCount		= 0;

	int wordWidth		= 0;

	int	runIndex0		= 0;
	int	runIndex1		= 0;

	int glyphPos0		= 0;
	int	glyphPos1		= 0;

	int charPos0		= 0;
	int charPos1		= 0;
	//int charPos2		= 0;
	//USPFONT *uspFont	= NULL;

	m_subLineCount		= 0;
	//UspFont

	charPos1	= getNextBreakPos(0);
	glyphPos1	= getGlyphPos(
								charPos1
								,&runIndex1
				);

	wordWidth	= getGlyphsWidth(glyphPos0,glyphPos1);
	dx			= wordWidth;

	m_pSubLineList[0].runIndex	= 0;
	m_pSubLineList[0].glyphPos	= 0;
	m_pSubLineList[0].charPos	= 0;
	m_pSubLineList[0].width		= dx;


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

		wordWidth	= getGlyphsWidth(glyphPos0,glyphPos1);
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
			if(lineCount +1 >= m_subLineBufferLength - 1)
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

			lineCount ++;

			if(charPos0<0||charPos0>m_CharCount
			||glyphPos0<0||glyphPos0>m_GlyphCount
			||runIndex0<0||runIndex0>=m_RunCount)
			throw UspException();

			m_pSubLineList[lineCount].runIndex	= runIndex0;
			m_pSubLineList[lineCount].glyphPos	= glyphPos0;
			m_pSubLineList[lineCount].charPos	= charPos0;
			WCHAR *line = m_pText + charPos0;
			if(charPos0<0)throw UspException();
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
				dx += (m_pRunList[runIndex0 + i].abc.abcB + m_pRunList[runIndex0 + i].abc.abcA +m_pRunList[runIndex0 + i].abc.abcC);
			}

			//dx -= m_pRunList[runIndex1].abc.abcA;
		}

		m_pSubLineList[lineCount].width = dx;

		

	}
	lineCount ++;
	m_pSubLineList[lineCount].charPos	= m_CharCount;
	m_subLineCount = lineCount;
	if(m_subLineCount>20)
	{
		int I=0;
	}
	return m_subLineCount;
}
void UspData::drawSubLine(HDC *pDC,int lineIndex,int x,int y)
{
	if(lineIndex >= m_subLineCount)throw UspException();
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

	/*int isRgn = */
	//int ret = GetClipRgn(*pDC,oldRgn);
	//if(ret == -1)
	//	throw UspException();

	drawBacground(pDC,x,y,stCharPos,enCharPos,runIndex,glyphPos,&selRect);
	if(selRect.right<selRect.left) throw UspException();
	selRgn = CreateRectRgnIndirect(&selRect);
	drawChars(pDC,x,y,stCharPos,enCharPos,runIndex,glyphPos);
	SelectClipRgn(*pDC,selRgn);
	drawSelection(pDC,x,y,stCharPos,enCharPos,runIndex,glyphPos);

	SelectClipRgn(*pDC,NULL);
	DeleteObject(selRgn);
}


int UspData::drawEx(HDC *pDC,int x ,int y,int lineWidth)
{
	//int totalWidth		= 0;
	int dx				= x;
	int dy				= (y < 0)? -y -getLineHeight() : y;
	int	dY				= (y < 0)? -getLineHeight() : getLineHeight();

	int lineCount		= 0;

	int wordWidth		= 0;

	int	runIndex0		= 0;
	int	runIndex1		= 0;

	int glyphPos0		= 0;
	int	glyphPos1		= 0;

	int charPos0		= 0;
	int charPos1		= 0;
	//int charPos2		= 0;
	USPFONT *uspFont	= NULL;


	//UspFont
	m_pSubLineList[lineCount].runIndex	= 0;
	m_pSubLineList[lineCount].glyphPos	= 0;
	m_pSubLineList[lineCount].charPos	= 0;


	//step 1: draw background
	while( runIndex0 < m_RunCount && charPos0 < m_CharCount)
	{
		
		//nextWordCharPos = getNextBreakPos(*pCharPos);
		//glyphPos1	= getGlyphPos(charPos,&runIndex0);
		charPos1	= getNextBreakPos(charPos0);
		glyphPos1	= getGlyphPos(
									charPos1
									,&runIndex1
					);

		wordWidth	= getGlyphsWidth(glyphPos0,glyphPos1);

		uspFont		= m_pFontManager->getUspFont(m_pRunList[runIndex0].fontIndex);
		
		//int clustPos	= charPos0;

		
		//SelectObject(*pDC,uspFont->hFont);
		if(dx + wordWidth > lineWidth + x)
		{
			// new line
			if(lineCount  >= m_subLineBufferLength - 1)
			{
				m_subLineBufferLength += 10;
				m_pSubLineList = (SUB_LINE*)realloc(m_pSubLineList,m_subLineBufferLength);
			}
			


			dx =	x ;
			dy +=	dY;	

			lineCount ++;
			m_pSubLineList[lineCount].runIndex	= runIndex0;
			m_pSubLineList[lineCount].glyphPos	= glyphPos0;
			m_pSubLineList[lineCount].charPos	= charPos0;
		}

		RECT selRect;
		drawBacground(
			pDC,
			dx,
			dy,
			charPos0,
			charPos1,
			runIndex0,
			glyphPos0,
			&selRect
		);

		dx += wordWidth;
		if(runIndex1 != runIndex0)//if run count >2
		{
			dx -= m_pRunList[runIndex0].abc.abcC;
			for(int i= 1;i<runIndex1-runIndex0;i++)
			{
				dx += m_pRunList[runIndex0 + i].abc.abcB;
			}

			dx -= m_pRunList[runIndex1].abc.abcA;
		}
		m_pSubLineList[lineCount].width = dx;
		
		

		
		runIndex0	= runIndex1;
		glyphPos0	= glyphPos1;
		charPos0	= charPos1;

	}
	//step 2. draw word
	dx				= x;
	dy				= y>=0?y:-y-getLineHeight();

	lineCount		= 0;

	wordWidth		= 0;

	runIndex0		= 0;
	runIndex1		= 0;

	glyphPos0		= 0;
	glyphPos1		= 0;

	charPos0		= 0;
	charPos1		= 0;
	while( runIndex0 < m_RunCount && charPos0 < m_CharCount)
	{
		
		//nextWordCharPos = getNextBreakPos(*pCharPos);
		
		
		//glyphPos1	= getGlyphPos(charPos,&runIndex0);
		charPos1	= getNextBreakPos(charPos0);
		glyphPos1	= getGlyphPos(
									charPos1
									,&runIndex1);



		wordWidth	= getGlyphsWidth(glyphPos0,glyphPos1);


		

		uspFont		= m_pFontManager->getUspFont(m_pRunList[runIndex0].fontIndex);
		
		//int clustPos	= charPos0;

		
		/*SelectObject(*pDC,uspFont->hFont);*/
		

		if(dx + wordWidth > lineWidth + x)
		{
			// new line
			dx =	x ;
			dy +=	dY;	
			lineCount++;
		}


		drawChars(
			pDC,
			dx,
			dy,
			charPos0,
			charPos1,
			runIndex0,
			glyphPos0
		);

		dx += wordWidth;
		if(runIndex1 != runIndex0)
		{
			dx -= (m_pRunList[runIndex0].abc.abcC + m_pRunList[runIndex1].abc.abcA);
		}

		runIndex0	= runIndex1;
		glyphPos0	= glyphPos1;
		charPos0	= charPos1;

	}

	
	return lineCount + 1;

}

//int UspData::drawEx(HDC *pDC,int x ,int y,int lineWidth)
//{
//	//int totalWidth		= 0;
//	int dx				= x;
//	int dy				= (y < 0)? -y -getLineHeight() : y;
//	int	dY				= (y < 0)? -getLineHeight() : getLineHeight();
//
//	int lineCount		= 0;
//
//	int wordWidth		= 0;
//
//	int	runIndex0		= 0;
//	int	runIndex1		= 0;
//
//	int glyphPos0		= 0;
//	int	glyphPos1		= 0;
//
//	int charPos0		= 0;
//	int charPos1		= 0;
//	//int charPos2		= 0;
//	USPFONT *uspFont	= NULL;
//	//UspFont
//
//
//	//step 1: draw background
//	while( runIndex0 < m_RunCount && charPos0 < m_CharCount)
//	{
//		
//		//nextWordCharPos = getNextBreakPos(*pCharPos);
//		//glyphPos1	= getGlyphPos(charPos,&runIndex0);
//		charPos1	= getNextBreakPos(charPos0);
//		glyphPos1	= getGlyphPos(
//									charPos1
//									,&runIndex1
//					);
//
//		wordWidth	= getGlyphsWidth(glyphPos0,glyphPos1);
//
//
//		
//
//		uspFont		= m_pFontManager->getUspFont(m_pRunList[runIndex0].fontIndex);
//		
//		//int clustPos	= charPos0;
//
//		
//		//SelectObject(*pDC,uspFont->hFont);
//		if(dx + wordWidth > lineWidth + x)
//		{
//			// new line
//			dx =	x ;
//			dy +=	dY;	
//
//			lineCount++;
//		}
//
//
//		//drawBacground(
//		//	pDC,
//		//	dx,
//		//	dy,
//		//	charPos0,
//		//	charPos1,
//		//	runIndex0,
//		//	glyphPos0
//		//);
//
//		dx += wordWidth;
//		if(runIndex1 != runIndex0)//if run count >2
//		{
//			dx -= m_pRunList[runIndex0].abc.abcC;
//			for(int i= 1;i<runIndex1-runIndex0;i++)
//			{
//				dx += m_pRunList[runIndex0 + i].abc.abcB;
//			}
//
//			dx -= m_pRunList[runIndex1].abc.abcA;
//		}
//		
//		
//
//		
//		runIndex0	= runIndex1;
//		glyphPos0	= glyphPos1;
//		charPos0	= charPos1;
//
//	}
//
//	return lineCount;
//
//}
void UspData::draw(HDC *pDc,int x,int y)
{
	int tmpWidth = 30;
	int charPos ;
	for(int i=0;i<this->m_RunCount ;i++)
	{
		drawRun2(&m_pRunList[i],pDc,x,y);
		charPos = m_pRunList[i].charPos;
		drawClusts(
			pDc,
			m_pFontManager->getFontCache(m_pRunList[i].fontIndex),
			m_pFontManager->getUspFont(m_pRunList[i].fontIndex),
			x,
			y+50,
			&charPos,
			i,
			&tmpWidth
		);
		int haha = 200;
		if(charPos < m_pRunList[i+1].charPos)
		{
			drawClusts(
				pDc,
				m_pFontManager->getFontCache(m_pRunList[i].fontIndex),
				m_pFontManager->getUspFont(m_pRunList[i].fontIndex),
				x + tmpWidth,
				y+55,
				&charPos,
				i,
				&haha
			);
		}
		tmpWidth = 30;

		x += m_pRunList[i].abc.abcB;
	}
}
int UspData::correctMongolian(int start,int end)
{
	for(int i = start; i < end; i++)
	{
		if((int)m_pText[i] == 0x180e)//
		{

			m_pLogAttrList[i].fCharStop		= 0;
			m_pLogAttrList[i].fWhiteSpace	= 0;
			if(i<end-1)
				m_pLogAttrList[i+1].fSoftBreak=0;
		}
	}
	return 0;
}
int	UspData::getMongolianScriptID()
{
	WCHAR tmp[]={0x1800,'\0'};
	ITEM  item[2];
	int count;
	HRESULT hr = ScriptItemize(tmp,1,2,NULL,NULL,item,&count);
	return item[0].a.eScript;
}
inline int UspData::getLineHeight()
{
	return m_maxAscent + m_maxDescent;
}

//HRESULT drawClust(int clustPos,HDC *pDC,int x,int y)
//{
//	HGDIOBJ
//	obj = SelectObject(*pDC,CreateSolidBrush(RGB(0,0,0)));
//}
int UspData::getGlyphsWidth(int stGlyphPos,int enGlyphPos)
{
	if(stGlyphPos >= enGlyphPos) throw UspException();
	if(enGlyphPos >  m_GlyphCount)throw UspException();
	int width = 0;
	while(stGlyphPos<enGlyphPos)
		width += m_pWidthList[stGlyphPos++];
	return width;
}


int	UspData::getGlyphPos(int charPos ,int *pRunIndex)
{
	if(*pRunIndex > m_RunCount || charPos> m_CharCount) 
		throw UspException();

	if(charPos == m_CharCount) return m_GlyphCount;
	while(charPos >= m_pRunList[*pRunIndex + 1].charPos && *pRunIndex< m_RunCount) (*pRunIndex)++;
	return m_pRunList[*pRunIndex].glyphPos + m_pClusterList[charPos];
}

//POINT UspData::getXyFromCharPos(int charPos)
//{
//
//	return ;
//}
BOOL UspData::getCharPosFromSubLine(int subLineNo,int X,CHAR_POS* pCharPos)
{
	CHAR_POS		&ret = *pCharPos;
	ret.index = 0;
	ret.trailing =0;
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
		return TRUE;
	}
	else
		throw UspException();
	return FALSE;
}

CHAR_POS& UspData::getCharPosFromSubLine(int subLineNo,int X)
{
	CHAR_POS		ret = {0};
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
CHAR_POS& UspData::getCharPos(int X,int Y)
{
	int subLineNo	= min(Y/getLineHeight(),m_subLineCount -1);
	return getCharPosFromSubLine(subLineNo,X);
}
BOOL UspData::getCharPos(int X, int Y, __out CHAR_POS* pCharPos)
{
	int subLineNo	= min(Y/getLineHeight(),m_subLineCount -1);
	return getCharPosFromSubLine(subLineNo,X,pCharPos);
}

int UspData::getRunXInSubLine(int runIndex,int lineIndex)
{
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
	return x;
}
BOOL UspData::getCharLocation(CHAR_POS *charPos, __out CHAR_LOC* charLoc)
{

	charLoc->subLine= getLineFromCharPos(charPos->index);
	int lineIndex	= charLoc->subLine;
	int runIndex	= getRunFromCharPos(charPos->index);
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
	charLoc->x		= runX + xInRun;
	return TRUE;
}
CHAR_LOC& UspData::getCharLocation(CHAR_POS *charPos)
{
	CHAR_LOC	tmp;
	tmp.subLine		= getLineFromCharPos(charPos->index);
	int lineIndex	= tmp.subLine;
	int runIndex	= getRunFromCharPos(charPos->index);
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
	tmp.x		= runX + xInRun;
	return tmp;
}
POINT UspData::getLocation(CHAR_POS *charPos)
{
	POINT point;
	int lineIndex	= getLineFromCharPos(charPos->index);
	int runIndex	= getRunFromCharPos(charPos->index);
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
int UspData::getLineFromCharPos(int charPos)
{
	int line = 0;
	if(charPos>m_CharCount) throw UspException();
	if(charPos==m_CharCount)return m_subLineCount-1;
	while(charPos >= m_pSubLineList[line + 1].charPos && line < m_subLineCount) line++;
	return line;
}
int UspData::getRunFromCharPos(int charPos)
{
	if(charPos >m_CharCount) throw UspException();
	int run = 0;
	while(charPos >= m_pRunList[run + 1].charPos && run + 1< this->m_RunCount) run ++;
	return run;
}
int UspData::getMaxRunIndexInLine(int subLineIndex)
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
int UspData::getRunFromLineAndX(int subLineIndex,int x)
{
	int runIndex		= m_pSubLineList[subLineIndex].runIndex;
	int endRunIndex		= getMaxRunIndexInLine( subLineIndex);
	int runRightBound	= getRunXInSubLine(runIndex,subLineIndex) 
		+ m_pRunList[runIndex].abc.abcA
		+ m_pRunList[runIndex].abc.abcB
		+ m_pRunList[runIndex].abc.abcC;
	

	while(x > runRightBound)
	{
		runIndex ++;
		if(runIndex == endRunIndex)return runIndex;
		runRightBound +=  
			( m_pRunList[runIndex].abc.abcA
			+ m_pRunList[runIndex].abc.abcB
			+ m_pRunList[runIndex].abc.abcC);
	}
	return runIndex;

}
//int UspData::getRunFromLineAndX(int subLineIndex,int x,int *pXInRun)//maybe return -1 when x=0 and subline=0
//{
//
//	int runIndex	= m_pSubLineList[subLineIndex].runIndex ;
//	int width		= 0 ;
//	int dx			= 0 ;
//	int tmpRunWidth	= 0 ;
//
//	if(pXInRun == NULL) 
//		pXInRun = &dx;
//	
//	
//	if(m_pSubLineList[subLineIndex].charPos > m_pRunList[runIndex].charPos)
//	{
//		int 
//		stGlyphPos	= m_pSubLineList[subLineIndex].glyphPos;//getGlyphPos(.charPos,&runIndex);
//		width		= getGlyphsWidth(stGlyphPos,m_pRunList[runIndex+1].glyphPos);
//		if(x <= width)
//		{
//			
//			*pXInRun = -x ;
//			return runIndex;
//		}
//		
//		runIndex ++ ;
//	}
//
//	*pXInRun = x;
//
//	while( *pXInRun > width && runIndex < m_RunCount)
//	{
//		*pXInRun	= *pXInRun - width ;
//		*pXInRun	= *pXInRun;
//		width		= m_pRunList[runIndex].abc.abcB + m_pRunList[runIndex].abc.abcC + m_pRunList[runIndex].abc.abcA;
//		tmpRunWidth = getGlyphsWidth(m_pRunList[runIndex].glyphPos,m_pRunList[runIndex+1].glyphPos);
//		runIndex++;
//	}
//	
//	if(runIndex == m_RunCount )
//		*pXInRun = width ;
//	runIndex--;
//	return runIndex;
//}
int UspData::getRunFromXy(int x,int y,int* pXInRun)
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
//int	UspData::getGlyphPos(int charPos,RUN *pRun)
//{
//	if(charPos > pRun->charCount + pRun->charPos) 
//		throw UspException();
//
//	return pRun->glyphPos + m_pClusterList[charPos];
//}
int	UspData::getNextBreakPos(int charPos)
{
	//sint pos=charPos+1;
	if(charPos >= m_CharCount)
		throw UspException();
	while(charPos < m_CharCount&&m_pLogAttrList[++charPos].fSoftBreak ==0 );
	return charPos;
}
HRESULT UspData::drawClust (
							HDC *pDC,
							SCRIPT_CACHE* cache, 
							USPFONT* uspFont,
							int x,int y,
							RECT* rect,
							int *pCharPos,
							int *pGlyphCount,
							int run,
							int *pWidth
		)
{
	//RECT rect	= {x , y , x + clWidth , y + m_maxAscent + m_maxDescent};
	//COLORREF 
	//	col		= m_pTextAttr->getBgColor(*pCharPos);
	//return ScriptTextOut(
	//	*pDC ,
	//	cache ,
	//	x ,
	//	y ,
	//	ETO_CLIPPED,//ETO_OPAQUE ,
	//	&rect ,
	//	&m_pRunList[run].scriptAnalyze,
	//	NULL,
	//	0,
	//	m_pGlyphList + clGlyphPos,//,run->glyphPos,
	//	clGlyphCount,//run->glyphCount,
	//	this->m_pWidthList		+ clGlyphPos,//run->glyphPos,
	//	NULL,
	//	this->m_pGoffsetList	+ clGlyphPos//run->glyphPos
	//);
	return 0;
}
//HRESULT UspData::drawChars()
HRESULT UspData::drawClusts(HDC *pDC,SCRIPT_CACHE* cache, USPFONT* uspFont,int x,int y,int *pCharPos,int run,int *pWidth)
{
	int tmpClustWidth	= 0;
	
	int clCharPos		= *pCharPos;
	int clGlyphPos		= m_pClusterList[clCharPos] + m_pRunList[run].glyphPos ;

	int clCharCount		= 1;
	int clGlyphCount	= 1;
	int clWidth	= 1;

	HRESULT hr;
	while(clCharPos<m_pRunList[run+1].charPos)
	{
		clCharCount	= 1;
		while(this->m_pClusterList[clCharPos + clCharCount] == this->m_pClusterList[clCharPos + clCharCount - 1])
			clCharCount++;

		clGlyphCount= 1;
		while(this->m_pVisAttrList[clGlyphPos + clGlyphCount].fClusterStart == 0
				&& clGlyphPos + clGlyphCount < m_GlyphCount )
			clGlyphCount ++;
		
		clWidth		= 0;
		for(int i =0;i< clGlyphCount;i++)
			clWidth += m_pWidthList[clGlyphPos + i];

		if(tmpClustWidth + clWidth > *pWidth )
			break;
		
		RECT rect	= {x , y , x + clWidth , y + m_maxAscent + m_maxDescent};
		COLORREF 
			col		= m_pTextAttr->getBgColor(clCharPos);
		hr = ScriptTextOut(
			*pDC ,
			cache ,
			x ,
			y + m_maxAscent - uspFont->tm.tmAscent ,
			ETO_CLIPPED,//ETO_OPAQUE ,
			&rect ,
			&m_pRunList[run].scriptAnalyze,
			NULL,
			0,
			m_pGlyphList + clGlyphPos,//,run->glyphPos,
			clGlyphCount,//run->glyphCount,
			this->m_pWidthList		+ clGlyphPos,//run->glyphPos,
			NULL,
			this->m_pGoffsetList	+ clGlyphPos//run->glyphPos
		);
				x		+= clWidth;
		clCharPos		+= clCharCount;
		clGlyphPos		+= clGlyphCount; 
		tmpClustWidth	+= clWidth;
	}
	*pCharPos	= clCharPos;
	*pWidth		= tmpClustWidth;
	return S_OK;
}
//HRESULT	UspData::drawEx(HDC *pDc,int x,int y,int *pCharPos,int width)
//{
//	int clustPos		= *pCharPos;
//	int run				= 0;
//
//	while(m_pRunList[run+1].charPos <= clustPos) run ++;
//
//	hr = ScriptTextOut(
//			*pDC ,
//			&uspFont->fontCache ,//
//			x ,
//			y + m_maxAscent - uspFont->tm.tmAscent ,
//			ETO_CLIPPED,//ETO_OPAQUE ,
//			&rect ,
//			&run->scriptAnalyze,
//			NULL,
//			0,
//			m_pGlyphList + clGlyphPos,//,run->glyphPos,
//			clGlyphCount,//run->glyphCount,
//			this->m_pWidthList + clGlyphPos,//run->glyphPos,
//			NULL,
//			this->m_pGoffsetList + clGlyphPos//run->glyphPos
//		);
//
//}
ABC UspData::getClusterABCWidth(HDC* pDC,SCRIPT_CACHE *pCache,int clGlyphPos,int length)
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
HRESULT UspData::drawChars(HDC *pDC,int dx,int dy,int stCharPos,int enCharPos,int rIndex,int stGlyphPos)
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
	USPFONT*	uspFont = m_pFontManager->getUspFont(run->fontIndex);

	SetBkMode(*pDC,TRANSPARENT);
	SelectObject(*pDC,uspFont->hFont);
	

	HRESULT hr;
	while( clustPos < enCharPos && runIndex < m_RunCount) 
	{
		clCharCount	= 1;
		clGlyphCount= 1;
		clWidth		= 0;

		if(clustPos >= m_pRunList[runIndex + 1].charPos && runIndex<this->m_RunCount)
		{
			runIndex++;
			run		= &m_pRunList[runIndex];
			uspFont = m_pFontManager->getUspFont(run->fontIndex);
			SelectObject(*pDC,uspFont->hFont);
		}
		WCHAR* t = m_pText + clustPos;
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
		ABC abc = getClusterABCWidth(
			pDC,
			&uspFont->fontCache,
			clGlyphPos,
			clGlyphCount
		);
//clWidth =0 ;
		//if(clWidth != abc.abcA + abc.abcB + abc.abcC)
		//{
		//	throw UspException();
		//}
		//if()


		RECT rect	= {x + abc.abcA, y , x + abc.abcB , y + m_maxAscent + m_maxDescent};
		
		col			= m_pTextAttr->getFgColor(clustPos);
		//HGDIOBJ obj = SelectObject(*pDC,CreateSolidPen(RGB(0,0,255)));
		WCHAR* text = m_pText + clustPos;
		//char * cltext = clustStart + clustPos;
		SetTextColor(*pDC,col);
		
		hr = ScriptTextOut(
			*pDC ,
			&uspFont->fontCache ,
			x ,
			y + m_maxAscent - uspFont->tm.tmAscent ,
			0,//ETO_CLIPPED,//ETO_OPAQUE ,
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
		//
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
		clustPos	+= clCharCount;
		clGlyphPos	+= clGlyphCount; 


	}
	return 0;
}
HRESULT UspData::drawSelection(HDC *pDC,int dx,int dy,int stCharPos,int enCharPos,int rIndex,int stGlyphPos)
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
	USPFONT*	uspFont = m_pFontManager->getUspFont(run->fontIndex);

	//SetBkMode(*pDC,TRANSPARENT);
	SelectObject(*pDC,uspFont->hFont);
	

	HRESULT hr;
	while( clustPos < enCharPos && runIndex < m_RunCount) 
	{
		clCharCount	= 1;
		clGlyphCount= 1;
		clWidth		= 0;

		if(clustPos >= m_pRunList[runIndex + 1].charPos && runIndex<this->m_RunCount)
		{
			runIndex++;
			run		= &m_pRunList[runIndex];
			uspFont = m_pFontManager->getUspFont(run->fontIndex);
			SelectObject(*pDC,uspFont->hFont);
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
		ABC abc = getClusterABCWidth(
			pDC,
			&uspFont->fontCache,
			clGlyphPos,
			clGlyphCount
		);

		//clWidth = abc.abcA + abc.abcB + abc.abcC;
		//if()


		//RECT rect	= {x + abc.abcA, y , x + abc.abcB , y + m_maxAscent + m_maxDescent};
		
		col			= RGB(255,255,255);
		//HGDIOBJ obj = SelectObject(*pDC,CreateSolidPen(RGB(0,0,255)));
		WCHAR* text = m_pText + clustPos;
		SetTextColor(*pDC,col);
		
		hr = ScriptTextOut(
			*pDC ,
			&uspFont->fontCache ,
			x ,
			y + m_maxAscent - uspFont->tm.tmAscent ,
			0,//ETO_CLIPPED,//ETO_OPAQUE ,
			NULL ,
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
		clustPos	+= clCharCount;
		clGlyphPos	+= clGlyphCount; 


	}
	return 0;
}
HRESULT UspData::drawBacground(HDC *pDC,int dx,int dy,int stCharPos,int enCharPos,int rIndex,int stGlyphPos,RECT* selRect)
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
	USPFONT*	uspFont = m_pFontManager->getUspFont(run->fontIndex);
	
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
			uspFont = m_pFontManager->getUspFont(run->fontIndex);
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
		ABC abc = getClusterABCWidth(
			pDC,
			&uspFont->fontCache,
			clGlyphPos,
			clGlyphCount
		);

		//clWidth = abc.abcA + abc.abcB + abc.abcC;
		//if()


		//RECT rect	= {x + abc.abcA, y , x + abc.abcB , y + m_maxAscent + m_maxDescent};
		//col		= m_pTextAttr->getFgColor(clustPos);
		for(int i=0;i<clCharCount;i++)
		{
			RECT 
			rect = {
				x + clWidth* i/clCharCount, 
				y , 
				x + clWidth*(i+1)/clCharCount , 
				y + m_maxAscent + m_maxDescent
			};
			
			if(m_pTextAttr->getSelected(clustPos + i))
			{
				if(selStart)
				{
					selRect->top	= rect.top;
					selRect->left	= rect.left;
					selRect->bottom	= rect.bottom;
					selStart		= FALSE;
				}

				selRect->right	= rect.right;
				

				col	= GetSysColor(COLOR_HIGHLIGHT);
			}
			else
				col	= m_pTextAttr->getBgColor(clustPos+i);
			if(brush = CreateSolidBrush(col))
			{
				FillRect(*pDC,&rect,brush);
				DeleteObject(brush);
			}
		}
		//HGDIOBJ obj = SelectObject(*pDC,CreateSolidPen(RGB(0,0,255)));
		WCHAR * text = m_pText + clustPos;

		//

				x	+= clWidth;
		clustPos	+= clCharCount;
		clGlyphPos	+= clGlyphCount; 


	}
	return 0;
}
HRESULT UspData::drawBacground2(HDC *pDC,int dx,int dy,int stCharPos,int enCharPos,int runIndex,int stGlyphPos)
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
		for(int i=0;i<clCharCount;i++)
		{
			RECT rect	= {x + clWidth* i/clCharCount, y , x + clWidth*(i+1)/clCharCount , y + m_maxAscent + m_maxDescent};
			if(m_pTextAttr->getSelected(clustPos + 1))
			{
				col	= GetSysColor(COLOR_HIGHLIGHT);
			}
			else
				col	= m_pTextAttr->getBgColor(clustPos+i);
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

HRESULT UspData::drawRun2(RUN *run,HDC *pDC,int x,int y)
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
		while(this->m_pVisAttrList[clGlyphPos/*run->glyphPos*/ + clGlyphCount].fClusterStart == 0 && clGlyphPos/*run->glyphPos*/ + clGlyphCount < m_GlyphCount)
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
HRESULT UspData::drawRun(RUN *run,HDC *pDC,int x,int y)
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

void UspData::shapeAndPlace()
{
	HDC tmpDC = GetDC(m_Hwnd);
	HRESULT hr;
	this->m_GlyphCount = 0;

	int sId = getMongolianScriptID();

	for(int i=0;i< this->m_RunCount;i++)
	{
		//hr = shapeRun(&this->m_pRunList[i],&tmpDC);
		//hr = placeRun(&this->m_pRunList[i],&tmpDC);

		hr = shapeAndPlaceRun(&this->m_pRunList[i],&tmpDC);
		hr = ScriptBreak(
			m_pText + m_pRunList[i].charPos,
			m_pRunList[i+1].charPos - m_pRunList[i].charPos,
		   &m_pRunList[i+0].scriptAnalyze,
			this->m_pLogAttrList + m_pRunList[i].charPos
		);

		if(hr!=S_OK) throw UspBreakRunException();

		if(m_pRunList[i].scriptAnalyze.eScript == sId) //Mongolian
		{
			correctMongolian(
				m_pRunList[i].charPos,
				m_pRunList[i+1].charPos
			);
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
}
HRESULT UspData::shapeAndPlaceRun(RUN *run,HDC *pDC)
{
	HRESULT hr;
	USPFONT* uspFont	= m_pFontManager->getUspFont(run->fontIndex);
	HFONT oldFont		= (HFONT)SelectObject(*pDC,uspFont->hFont);
	//if(oldFont==NULL) return S_FALSE;
	//SCRIPT_CACHE sc ={0};
	int tmpCount = 0;
	do
	{
		if(tmpCount >= 10)break;
		hr = ScriptShape(
			*pDC,
			&uspFont->fontCache,
			this->m_pText + run->charPos,
			run->charCount,
			this->m_GlyphBufferLen	- m_GlyphCount, //error
			&run->scriptAnalyze,
			this->m_pGlyphList		+ run->glyphPos,
			this->m_pClusterList	+ run->charPos,
			this->m_pVisAttrList	+ run->glyphPos,
			&run->glyphCount
		);
		tmpCount++;
		if(hr == E_OUTOFMEMORY)
		{
			reAllocate();
		}
		else if(hr == USP_E_SCRIPT_NOT_IN_FONT) 
		{
			run->scriptAnalyze.eScript = SCRIPT_UNDEFINED;
		}
	}while(hr != S_OK);

	

	if(hr != S_OK) throw UspException();
	hr = ScriptPlace(
		*pDC,
		&uspFont->fontCache ,
		this->m_pGlyphList		+ run->glyphPos ,
		run->glyphCount ,
		this->m_pVisAttrList	+ run->glyphPos ,
		&run->scriptAnalyze ,
		this->m_pWidthList		+ run->glyphPos ,
		this->m_pGoffsetList	+ run->glyphPos ,
		&run->abc
	);
	if(hr != S_OK) throw UspShapeRunException();

	return hr;

}
HRESULT UspData::shapeRun(RUN *run,HDC *pDC)
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

HRESULT UspData::placeRun(RUN *run,HDC *pDC)
{
	USPFONT* uspFont = m_pFontManager->getUspFont(run->fontIndex);
	SelectObject(*pDC,uspFont->hFont);

	return ScriptPlace(
		*pDC,
		&uspFont->fontCache ,
		this->m_pGlyphList		+ run->glyphPos ,
		run->glyphCount ,
		this->m_pVisAttrList	+ run->glyphPos ,
		&run->scriptAnalyze ,
		this->m_pWidthList		+ run->glyphPos ,
		this->m_pGoffsetList	+ run->glyphPos ,
		&run->abc
	);
}
UspData::~UspData(void)
{
	free(m_pVisAttrList);
	free(m_pLogAttrList);
	free(m_pClusterList);
	free(m_pGlyphList);
	free(m_pWidthList);
	free(m_pGoffsetList);
	free(m_pItemList);
	free(m_pRunList);
	free(m_pSubLineList);
	delete fSoftBreak  ;
	delete fWhiteSpace ;
	delete fCharStop   ;
	delete fWordStop   ;
	delete fInvalid    ;
	delete clustStart  ;
	delete itemStart   ;
	delete runStart    ;
}
void UspData::preAllocate()
{
	//char base list
	//BOOL isNULL = FALSE ;
	this->m_pClusterList	= (WORD*)		malloc(sizeof(WORD)		* (this->m_CharCount + 1));
	this->m_pLogAttrList	= (LOGATTR*)	malloc(sizeof(LOGATTR)	* (this->m_CharCount + 1));
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
	this->m_RunBufferlen	= m_ItemBufferLength * 2;
	this->m_pRunList		= (RUN*)		malloc(sizeof(RUN)		* m_RunBufferlen);

	this->m_subLineBufferLength = 10;
	this->m_pSubLineList	= (SUBLINE*)	malloc(sizeof(SUBLINE)	* m_subLineBufferLength);
			

	if( m_pClusterList	== NULL|| 
		m_pVisAttrList	== NULL||
		m_pGlyphList	== NULL||
		m_pWidthList	== NULL||
		m_pGoffsetList	== NULL|| 
		m_pItemList		== NULL|| 
		m_pRunList		== NULL
	)
		throw UspAllocateMemFaildException();
}
void UspData::reAllocate()
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
		m_pItemList		== NULL|| 
		m_pRunList		== NULL
	)
		throw UspAllocateMemFaildException ();
}
SCRIPT_PROPERTIES  UspData::getScriptProperty(int index)
{
	const SCRIPT_PROPERTIES ** ppScriptProperties;
	SCRIPT_PROPERTIES * ret = NULL;
	int ScriptCount;
	ScriptGetProperties(&ppScriptProperties,&ScriptCount);
	return *ppScriptProperties[index];
}
int UspData::aaaaaaaaaaaaaaaaaaaaaaaaaa(void)
{
	return 0;
}

int UspData::ffffffffffffffffffffffff(void)
{
	return 0;
}
