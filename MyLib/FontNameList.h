#pragma once

#include <vector>
#include <windows.h>
#include "MNText.h"
#include "MNException.h"
#include <string>
using namespace std;
class CFontNameList
{
public:
	vector<MNText>	m_list;
	vector<wstring> m_strList;
private :
	CFontNameList(CFontNameList&){};
public:
	void	refup(UINT index);
	void    refdown(UINT index);
	UINT	add(MNText& fontName);
	int		find(MNText&  fontName);
	UINT	getIndex(MNText& fontName);
	void	print();
	MNText&	getText(UINT index);
	CFontNameList(void);
	~CFontNameList(void);
};
