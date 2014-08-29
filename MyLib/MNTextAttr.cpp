#include "StdAfx.h"
#include "MNTextAttr.h"

MNTextAttr::MNTextAttr(void):
	m_Length	( 0		)
{
	m_fontNameList.add(MNText(L"arongsuyila"));
	m_fontNameList.add(MNText(L"arongsuyila"));
	//_CrtDumpMemoryLeaks();
}
MNTextAttr::MNTextAttr(UINT len):
	m_Length(len)
{
	m_charAttr.resize(len);
	m_fontNameList.add(MNText(L"arongsuyila"));
	m_fontNameList.add(MNText(L"arongsuyila"));
}
MNCharAttr& MNTextAttr::operator[](UINT index)
{
	return m_charAttr[index];
}
MNTextAttr::~MNTextAttr(void)
{

}
void MNTextAttr::reset()
{
	MNCharAttr attr;
	std::fill(m_charAttr.begin(),m_charAttr.end(),attr);
}
void MNTextAttr::allocate(UINT len)
{
	m_charAttr.resize(len);
	m_Length = len;
}
bool MNTextAttr::canBreakRun(UINT i0,UINT i1)
{
	MNCharAttr* attr0 = &m_charAttr[i0];
	MNCharAttr* attr1 = &m_charAttr[i1];
	if(
		  attr0->bold		!= attr1->bold
		||attr0->italic		!= attr1->italic
		||attr0->size		!= attr1->size
		||attr0->fontIndex	!= attr1->fontIndex
	)
		return true;
	else
		return false;
}
int MNTextAttr::setFont(MNText& fontName, UINT charPos, UINT len)
{
	UINT index = m_fontNameList.getIndex(fontName);
	int
	end = charPos + len;
	end = (end < m_Length)?end:m_Length;
	for(int i = charPos; i< end  ;i++)
		this->m_charAttr[i].fontIndex = index;
	return end - charPos;
}
int MNTextAttr::setTextSize(UINT size, UINT charPos, UINT len) {
	int 
	end = charPos + len;
	end = (end < m_Length)?end:m_Length;
	for(int i= charPos; i< end  ;i++)
		m_charAttr[i].size = size;
	return end - charPos;
}
int MNTextAttr::setSelect(UINT charPos, UINT len) {
	UINT 
	end = charPos + len;
	end = (end < m_Length)?end:m_Length;
	UINT i;
	for(i = 0;i < charPos; i++)
	{
		m_charAttr[i].selcted = 0;
	}
	for(i = charPos;i < end; i++)
	{
		m_charAttr[i].selcted = 1;
	}
	for(i = end;i < m_Length; i++)
	{
		m_charAttr[i].selcted = 0;
	}
	return end - charPos;
}
void MNTextAttr::setBgColor(UINT charPos, UINT len, COLORREF& col)
{
	UINT 
	end = charPos + len;
	end = (end < m_Length)?end:m_Length;
	UINT i;

	for(i = charPos;i < end; i++)
	{
		m_charAttr[i].bgColor = col;
	}

}
void MNTextAttr::setFgColor(UINT charPos, UINT len, COLORREF& col)
{
	UINT 
	end = charPos + len;
	end = (end < m_Length)?end:m_Length;
	UINT i;

	for(i = charPos;i < end; i++)
	{
		m_charAttr[i].fgColor = col;
	}

}
MNText& MNTextAttr::getFontName(UINT index)
{
	return  m_fontNameList.getText(index);
}
COLORREF& MNTextAttr::getFgColor(UINT charPos)
{
	return m_charAttr[charPos].fgColor;
}
COLORREF& MNTextAttr::getBgColor(UINT charPos)
{
	return m_charAttr[charPos].bgColor;
}
