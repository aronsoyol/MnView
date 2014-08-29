#pragma once
#include "GlyfData.h"

class MNLineGlyfCache: public GlyfData
{
	int		m_usage;
	int		m_lineIndex;
	int		m_length_CRLF;
	ULONG	m_fileOffset;
public:
	MNLineGlyfCache(void);
	virtual ~MNLineGlyfCache(void);

	int getUsage(){
		return m_usage;
	}
	void use()
	{
		m_usage ++;
	}

	void initialize(int line , ULONG fileOffset, WCHAR* text, int len, MNFontManager* pFm)
	{
		m_usage			= 1;
		m_lineIndex		= line;
		m_fileOffset	= fileOffset;
		m_length_CRLF	= len;
		//len				= m_length_CRLF - CRLF_size(text, len);
		m_pFontManager	= pFm;
		GlyfData::initialize(text, len);
	}
	UINT getLineIndex()
	{
		return m_lineIndex;
	}
	void invalidate()
	{
		m_usage = 0;
	}

	//int getCharCount_WithCRLF()
	//{	
	//	return m_length_CRLF;
	//}
	int getCharCount_WithoutCRLF()
	{	
		return m_CharCount;
	}
	UINT	getCharCount(){return m_length_CRLF;}
	//ULONG	getFileOffset()
	//{
	//	return m_fileOffset;
	//}

};
