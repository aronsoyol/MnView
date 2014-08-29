#include "StdAfx.h"
#include "FontNameList.h"

CFontNameList::CFontNameList(void)
{
	int I=0;
	//_CrtDumpMemoryLeaks();
}

CFontNameList::~CFontNameList(void)
{
	int i=0;
}
UINT CFontNameList::getIndex(MNText& fontName)
{
	int index = find(fontName);
	if(index<0)
		return add(fontName);
	else return (UINT)index;
}
UINT CFontNameList::add(MNText& fontName)
{
	//fontName.refup();
	if(m_list.size() > 5 )
	{
		for(UINT i = 0;i<m_list.size();i++)
		{
			if( m_list[i].getRefCount() <= 0)
			{
				m_list[i] = fontName;
				return i;
			}
		}
	}
	m_list.push_back(fontName);
	//m_len++;
	return m_list.size() - 1;
}
void	CFontNameList::refup(UINT index)
{
	if(index >= m_list.size() || index < 0) throw MnException();
	m_list[index].refup();
}
void    CFontNameList::refdown(UINT index)
{
	if(index >= m_list.size() || index < 0) throw MnException();
	m_list[index].refdown();
}
int CFontNameList::find(MNText&  fontName)
{
	for(UINT i =0;i<m_list.size();i++)
	{
		if( m_list[i] == fontName)
			return i;
	}
	return -1;
}
void CFontNameList::print()
{
	for(UINT i =0;i<m_list.size();i++)
	{
		m_list[i].print();
		printf("|");
	}
}
MNText&	CFontNameList::getText(UINT index)
{
	return m_list[index];
}