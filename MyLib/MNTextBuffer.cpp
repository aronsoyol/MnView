#include "StdAfx.h"
#include "MNTextBuffer.h"

MNTextBuffer::MNTextBuffer(void)
{
}

MNTextBuffer::~MNTextBuffer(void)
{

}
UINT MNTextBuffer::copyIn(WCHAR * buffer,UINT len)
{
	len = min(len,m_nSize);
	int l = findEol(buffer,len);
	memcpy(m_buffer, buffer, l * sizeof(WCHAR));

	
	return len;
}
UINT MNTextBuffer::copyOut(WCHAR * buffer,UINT len)
{
	if(len < m_nSize) return -1;
	memcpy(m_buffer, buffer, m_charCount * sizeof(WCHAR));
}
int MNTextBuffer::findEol(WCHAR * buffer,UINT len)
{
	for(int i = 0; i < m_nSize; i++)
	{
		if(m_buffer[i++]==0x0D)
		{
			if(m_buffer[i] ==0x0A)
			{
				m_eol = i - 1;
			}
		}

	}
	return 0;
}