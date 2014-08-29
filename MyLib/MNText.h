#pragma once
//#include "stdafx.h"
//using namespace std;
#include <windows.h>

class MNText
{
	WCHAR* m_text;
	size_t m_len;

	int	m_refCount;

public:

	MNText(const WCHAR* text);
	MNText(const MNText& src);
	~MNText(void);
	

public:
	bool operator ==(const MNText&);
	bool operator !=(const MNText&);
	operator  WCHAR* (){return m_text;}
	MNText& operator =  (const MNText&);
	virtual UINT getText(WCHAR* buff,UINT buflen);
	UINT getLength();
	int getRefCount(){return m_refCount;}
	void print();
	void refup();
	void refdown();
};
