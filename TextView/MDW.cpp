#include <windows.h>
#include <Shlobj.h>
#include "mdw.h"

MDW::MDW(const WCHAR *szDataPath):
	m_hMuu(0),
	m_fnConvertMongolian(0),
	m_fnCorrectMongolian(0),
	m_fnGetConvertLookup(0),
	m_fDataLoaded(0)
{
	m_hMuu = LoadLibrary(L"muu.dll");
	if(m_hMuu)
	{
		m_fnConvertMongolian	= (fnConvertMongolian)		GetProcAddress(m_hMuu, "ConvertMongolian");
		m_fnCorrectMongolian	= (fnCorrectMongolian)		GetProcAddress(m_hMuu, "CorrectMongolian");
		m_fnGetConvertLookup	= (fnGetConvertLookup)		GetProcAddress(m_hMuu, "GetConvertLookup");
		m_fnOpenCorrectionData	= (fnOpenCorrectionData)	GetProcAddress(m_hMuu, "OpenCorrectionData");
		m_fnCloseCorrectionData	= (fnCloseCorrectionData)	GetProcAddress(m_hMuu, "CloseCorrectionData");
	}
	if(szDataPath[0] != '\0')
	{
		m_fDataLoaded = m_fnOpenCorrectionData(szDataPath);
	}
}
MDW::MDW(bool fLoadData):
	m_hMuu(0),
	m_fnConvertMongolian(0),
	m_fnCorrectMongolian(0),
	m_fnGetConvertLookup(0),
	m_fDataLoaded(0)
{
	m_hMuu = LoadLibrary(L"muu.dll");
	if(m_hMuu)
	{
		m_fnConvertMongolian	= (fnConvertMongolian)		GetProcAddress(m_hMuu, "ConvertMongolian");
		m_fnCorrectMongolian	= (fnCorrectMongolian)		GetProcAddress(m_hMuu, "CorrectMongolian");
		m_fnGetConvertLookup	= (fnGetConvertLookup)		GetProcAddress(m_hMuu, "GetConvertLookup");
		m_fnOpenCorrectionData	= (fnOpenCorrectionData)	GetProcAddress(m_hMuu, "OpenCorrectionData");
		m_fnCloseCorrectionData	= (fnCloseCorrectionData)	GetProcAddress(m_hMuu, "CloseCorrectionData");
	}

	if(m_hMuu && fLoadData)
	{
		WCHAR path [MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, path);
		int len = lstrlen(path);
		if(path[len - 1] != '\\')
		{
			path[len ] = '\\';
			path[len + 1] = '\0';
		}
		lstrcat(path, DB_FILE_PATH);
		m_fDataLoaded = m_fnOpenCorrectionData(path);
	}
}


MDW::~MDW(void)
{
	if(m_fDataLoaded)
		m_fnCloseCorrectionData();
	if(m_hMuu)
		FreeLibrary(m_hMuu);
	
}
bool MDW::IsReady()
{
	return (m_hMuu) ? true: false;
}
bool MDW::ConvertMongolian(
		UINT					nConvertType, 
		const	void*			pSrc, 
		__inout ULONG *			pSrcLength, 
		__out	CHelperBuffer  *pHBuffer)
{
	return (bool)m_fnConvertMongolian(nConvertType, pSrc, pSrcLength, pHBuffer->m_buffer);
}
long MDW::GetConvertLookup(mdw_convert_type *pConvertTypeLookup)
{
	long ret = 0;
	if(m_fnGetConvertLookup && (ret = m_fnGetConvertLookup(pConvertTypeLookup)) >= 0 ) 
		return ret;
	else
		return -1;
}
bool MDW::CorrectMongolian(
		const WCHAR*			pSrc, 
		__inout ULONG *			pSrcLength, 
		__out	CHelperBuffer*	hBuffer)
{
	return (bool)m_fnCorrectMongolian(pSrc, pSrcLength, hBuffer->m_buffer);
}
CHelperBuffer::CHelperBuffer(const MDW *pMuu)
{
	HBCreateBuffer		= (fnHBCreateBuffer)	GetProcAddress(pMuu->m_hMuu, "HBCreateBuffer");
	HBDeleteBuffer 		= (fnHBDeleteBuffer)	GetProcAddress(pMuu->m_hMuu, "HBDeleteBuffer");
	HBGetBufferSize		= (fnHBGetBufferSize)	GetProcAddress(pMuu->m_hMuu, "HBGetBufferSize");
	HBGetBufferDate		= (fnHBGetBufferDate)	GetProcAddress(pMuu->m_hMuu, "HBGetBufferDate");
	HBSetBufferDate		= (fnHBSetBufferDate)	GetProcAddress(pMuu->m_hMuu, "HBSetBufferDate");
	m_buffer			= HBCreateBuffer();
}
CHelperBuffer::~CHelperBuffer()
{
	HBDeleteBuffer(m_buffer);
}
LONG CHelperBuffer::GetBufferSize()
{
	return HBGetBufferSize(m_buffer);
}
LONG CHelperBuffer::GetBufferDate(BYTE *pBuffer, long length)
{
	return HBGetBufferDate(m_buffer, pBuffer, length);
}
