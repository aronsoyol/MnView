#pragma once
#include <list>
#include "MNLineBuffer.h"
#define BUFF_SIZE 200
class MNTextBuffer
{
	std::list<MNLineBuffer> m_lines;
	WCHAR	m_buffer[BUFF_SIZE];
	int		m_charCount;
	int		m_nSize ;
	int		m_nBytes;
	int		m_eol;

	int		findEol(WCHAR * buffer,UINT len);//end of line
public:
	MNTextBuffer(void);
	~MNTextBuffer(void);
	UINT	copyIn(WCHAR * buffer,UINT len);
	UINT	copyOut(WCHAR * buffer,UINT len);
	int		getSize();
	int		getCharCount();
	

	
};
