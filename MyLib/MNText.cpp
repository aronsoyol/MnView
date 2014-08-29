#include "StdAfx.h"
#include "MNText.h"
#include <stdlib.h>
#include <crtdbg.h>
MNText::MNText(const WCHAR* text):
	m_refCount(0)
{
	//_CrtDumpMemoryLeaks();
	m_len = wcslen(text);
	m_text = new WCHAR[m_len + 1];
	wcscpy_s(m_text,m_len + 1,text);
	m_text[m_len]='\0';
	//_CrtDumpMemoryLeaks();
}
MNText::MNText(const MNText& src):
	m_len(src.m_len),
	m_refCount(src.m_refCount)
{
	m_text = new WCHAR[m_len + 1];
	wcscpy_s(m_text,m_len + 1,src.m_text);
	m_text[m_len]='\0';
	//_CrtDumpMemoryLeaks();
}
MNText::~MNText(void)
{
	print();
	delete[] m_text;
	//wprintf(L"terminate\n");
	//_CrtDumpMemoryLeaks();
}
	
bool MNText::operator ==(const MNText&src)
{
	if(m_len != src.m_len) return false;

	if(m_len > 0)
	{
		int ret = wcscmp(src.m_text,m_text);
		if(ret == 0)return true;

	}
	return false;
}
bool MNText::operator !=(const MNText&src)
{
	if(m_len != src.m_len) return true;

	if(m_len > 0)
	{
		int ret = wcscmp(src.m_text,m_text);
		if(ret != 0)return true;

	}
	return false;
}
MNText& MNText::operator = (const MNText& src)
{
	delete[] m_text;
	m_len	= src.m_len;
	m_text	= new WCHAR[m_len + 1];
	m_refCount = src.m_refCount;
	wcscpy_s(m_text,m_len + 1,src.m_text);
	m_text[m_len]='\0';
	return *this;
}
void  MNText::print()
{
	//wprintf(L"%s,ref:%d\n",m_text,m_refCount);
}
void  MNText::refup()
{
	m_refCount ++;
	print();
}
void  MNText::refdown()
{
	m_refCount --;
	if(m_refCount == 0)
	{
		int i=0;
	}
	print();
}
UINT MNText::getText(WCHAR* buff,UINT buflen)
{
	if(buflen <= m_len) return 0;
	wcscpy_s(buff,m_len + 1, m_text);
	buff[m_len] ='\0';
	return m_len;
}
UINT MNText::getLength()
{
	return m_len;
}