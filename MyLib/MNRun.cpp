#include "StdAfx.h"
#include "MNRun.h"

MNRun::MNRun(void):
	charPos(0),charCount(0),glyphPos(0),glyphCount(0),scriptAnalyze(),abc()
{

}
void MNRun::ClearWordList()
{
	std::vector<MNWord*>::iterator itor;
	for(itor = wordlist.begin(); itor != wordlist.end(); ++itor) 
	{
		delete (*itor);
		(*itor) = NULL;
	}
}

MNRun::~MNRun(void)
{
	ClearWordList();
}
