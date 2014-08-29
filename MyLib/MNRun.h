#pragma once
#include <usp10.h>
#include <vector>
#include "mngramcheck.h"
#include "MNFont.h"
//#pragma comment(lib, "usp10.lib")
typedef struct MNWord_
{
	MNWord_(LONG charPos ,LONG charLen, LONG volType ):
		nCharPos(	charPos	),
		nCharLen(	charLen	),
		nVolType(	volType	)
	{
	}
	LONG			nCharPos;
	LONG			nCharLen;
	MN_VOWEL_TYPE	nVolType;
	BOOL			fInvalid;
} MNWord;
class MNRun
{
public:
	int		charPos;
	int		charCount;
	int		glyphPos;
	int		glyphCount;
	ABC		abc ;
	//MNFont	font;
	int		fontIndex;
	SCRIPT_ANALYSIS			scriptAnalyze;
	std::vector<MNWord*>	wordlist;
public:
	MNRun(void);
	void ClearWordList();


	~MNRun(void);
};
