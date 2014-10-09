#pragma once
//#include "MnCursor.h"
BOOL	PutMnWhiteToMemory();
HCURSOR CreateMnCursor(HMODULE module);
class MnStaticResource
{
	HCURSOR m_hCursor;
public:
	MnStaticResource();
	virtual ~MnStaticResource();
	HCURSOR GetCurosr();
};

