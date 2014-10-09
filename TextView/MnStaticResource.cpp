#include <Windows.h>
#include "MnStaticResource.h"

MnStaticResource::MnStaticResource():
	m_hCursor(0)
{
	PutMnWhiteToMemory();
	m_hCursor = CreateMnCursor(GetModuleHandle(0));
}

MnStaticResource::~MnStaticResource()
{
	DestroyCursor(m_hCursor);
}

HCURSOR MnStaticResource::GetCurosr()
{
	return m_hCursor;
}