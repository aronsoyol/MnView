#pragma once
#include <assert.h>
#include<windows.h>
#include "MNFont.h"
//#include <usp10.h>
#include "MNFont.h"
#include "MNRun.h"


//#pragma comment(lib, "usp10.lib")
typedef struct _CHAR_POS
{
	int logLine;
	int index;
	int trailing;
	//_CHAR_POS():logLine(0),index(0),trailing(0){}
	_CHAR_POS(UINT l = 0, UINT i = 0, UINT t = 0):logLine(l),index(i),trailing(t){}
	UINT get() const {return index + trailing;}
	void set(UINT l = 0, UINT i = 0, UINT t = 0)
	{
		logLine = l;
		index	= i;
		trailing= t;
	}
	operator UINT(){return (UINT)(index + trailing);}
	friend bool operator >(const _CHAR_POS& cp1,const _CHAR_POS& cp2);
	friend bool operator <(const _CHAR_POS& cp1,const _CHAR_POS& cp2);
	friend bool operator ==(const _CHAR_POS& cp1,const _CHAR_POS& cp2);
	friend bool operator !=(const _CHAR_POS& cp1,const _CHAR_POS& cp2);
	void print() const{printf("logline:%d,index:%d,trailing:%d\n",logLine,index,trailing);}
}CHAR_POS;
typedef struct _CHAR_LOC
{
	int subLine;
	int x;
	int cp;
}CHAR_LOC;
typedef struct _SUBLINE
{
	int		runIndex	;
	int		glyphPos	;
	int		charPos		;
	int		width		;
	bool	isUpdata	;
}SUBLINE;
//typedef struct _RUN
//{
//	int charPos;
//	int charCount;
//	int glyphPos;
//	int glyphCount;
//	SCRIPT_ANALYSIS scriptAnalyze;
//	ABC abc ;
//	MNFont font;
//	_RUN():charPos(0),charCount(0),glyphPos(0),glyphCount(0),scriptAnalyze(),abc(),font()
//	{
//		
//	}
//}RUN;
typedef  MNRun RUN;
typedef  int MDS_ALIGN ;
#define MDS_ALIGN_CENTER	0
#define MDS_ALIGN_LEFT		1
#define MDS_ALIGN_RIGHT		2
void MnDrawString(HDC hDc, HFONT hFont, int x ,int y, WCHAR *pText, int length, RECT *pRect =NULL, MDS_ALIGN nAlign = MDS_ALIGN_LEFT, COLORREF *pCol = NULL);
bool MnMesureString(HDC hDc, HFONT hFont, WCHAR *pText, int length, __out SIZE *pSize);