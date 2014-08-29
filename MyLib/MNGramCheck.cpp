#include "StdAfx.h"
#include "mngramcheck.h"
WCHAR QANGA_VOWELS[] = {0x1820, 0x1823, 0x1824};
WCHAR HUNDI_VOWELS[] = {0x1821, 0x1825, 0x1826};
//WCHAR SARMAG_VOWELS[] = {0x1821, 0x1825, 0x1826};
MN_VOWEL_TYPE CheckVowel(WCHAR ch);
MN_VOWEL_TYPE CheckVowel(WCHAR *word, int length)
{
	MN_VOWEL_TYPE wordVowelType = MN_VOWEL_WRONG;
	MN_VOWEL_TYPE charVowelType = MN_VOWEL_WRONG;
	int i = 0;
	int fMaybeSarmag =false;
	for(int i=0; i < length; i++)
	{
		charVowelType = CheckVowel(word[i]);
		if(charVowelType == MN_VOWEL_SARMAG )
		{
			fMaybeSarmag = true;
			continue;
		}
		if(charVowelType == MN_VOWEL_WRONG)
			continue;
		else {
			wordVowelType = charVowelType;
			break;
		}
	}
	for( ; i < length; i++)
	{
		charVowelType = CheckVowel(word[i]);
		if(charVowelType == MN_VOWEL_WRONG || charVowelType == MN_VOWEL_SARMAG)continue;
		else {
			if(wordVowelType != charVowelType)
				return MN_VOWEL_WRONG;
		}
	}
	if(wordVowelType == MN_VOWEL_WRONG && fMaybeSarmag) return MN_VOWEL_SARMAG;
	return wordVowelType;
}

MN_VOWEL_TYPE CheckVowel(WCHAR ch)
{
	for(int i = 0 ;i < sizeof(QANGA_VOWELS)/sizeof(WCHAR); i++)
	{
		if(ch == QANGA_VOWELS[i])return MN_VOWEL_QANGA;
		if(ch == HUNDI_VOWELS[i])return MN_VOWEL_HUNDI;
	}
	if(ch = 0x1822)	return MN_VOWEL_SARMAG;
	return MN_VOWEL_WRONG;
}