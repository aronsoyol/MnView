#pragma once
//#include "MnCursor.h"
BOOL PutMnWhiteToMemory();
HCURSOR CreateMyCursor(HMODULE module);
class MnStaticResource
{
	HCURSOR m_hCursor;
public:
	MnStaticResource();
	virtual ~MnStaticResource();
	HCURSOR GetCurosr();
};

