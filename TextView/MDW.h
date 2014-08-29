///
/// Muu Dll Wrapper (MDW)
///
#pragma once
typedef void * HelperBuffer;
//#define DATA_FILE_PATH (L"D:\\workspace\\fontproject\\")
#define DB_FILE_FOLDER		TEXT("Almas\\Dictionary\\")
#define DB_FILE_NAME		TEXT("ToUnicodeMongolian.dat")
#define DB_FILE_PATH		(DB_FILE_FOLDER DB_FILE_NAME)
typedef struct 
{
	WCHAR		zsDescript[256];
	int			nCommand;
} mdw_convert_type;

void GetDefaultDataPath(WCHAR* filePath);


typedef BOOL (*fnConvertMongolian)(
	UINT					nConvertType, 
	const	void*			pSrc, 
	__inout ULONG *			pSrcLength, 
	__out	HelperBuffer	hBuffer);

typedef BOOL (*fnCorrectMongolian)(
	const WCHAR*			pSrc, 
	__inout ULONG *			pSrcLength, 
	__out	HelperBuffer	hBuffer);

typedef void 		(*fnHBDeleteBuffer) (HelperBuffer HBuffer); 
typedef HelperBuffer(*fnHBCreateBuffer) (); 
typedef LONG 		(*fnHBGetBufferSize)(HelperBuffer HBuffer);
typedef BOOL 		(*fnHBGetBufferDate)(HelperBuffer HBuffer, BYTE* buffer, long length);
typedef BOOL 		(*fnHBSetBufferDate)(HelperBuffer HBuffer, BYTE* buffer, long length);
typedef ULONG		(*fnGetConvertLookup)(mdw_convert_type *pConvertTypeLookup);

typedef BOOL		(*fnOpenCorrectionData)(const wchar_t* filePath);
typedef BOOL		(*fnCloseCorrectionData)(void);
class CHelperBuffer
{
	friend class MDW;
private:
	HelperBuffer m_buffer;
	fnHBCreateBuffer   HBCreateBuffer ;
	fnHBDeleteBuffer   HBDeleteBuffer ;
	fnHBGetBufferSize  HBGetBufferSize;
	fnHBGetBufferDate  HBGetBufferDate;
	fnHBSetBufferDate  HBSetBufferDate;

public:
	CHelperBuffer(const MDW *pUmu);
	~CHelperBuffer();
	LONG GetBufferSize();
	LONG GetBufferDate(BYTE *pBuffer, long length);
};
class MDW
{
	friend class CHelperBuffer;
private:
	HMODULE m_hMuu;
	fnConvertMongolian m_fnConvertMongolian;
	fnCorrectMongolian m_fnCorrectMongolian;
	fnGetConvertLookup m_fnGetConvertLookup;
	fnOpenCorrectionData	m_fnOpenCorrectionData;
	fnCloseCorrectionData	m_fnCloseCorrectionData;
	bool m_fDataLoaded;
public:
	MDW(bool fLoadData = false);
	MDW(const WCHAR* szDatapath);
	bool IsReady();
	bool ConvertMongolian(
		UINT					nConvertType, 
		const	void*			pSrc, 
		__inout ULONG *			pSrcLength, 
		__out	CHelperBuffer *	pHBuffer);

	bool CorrectMongolian(
		const WCHAR*			pSrc, 
		__inout ULONG *			pSrcLength, 
		__out	CHelperBuffer*	hBuffer);
	long GetConvertLookup(
		mdw_convert_type *pConvertTypeLookup
		);
	virtual ~MDW(void);
};

