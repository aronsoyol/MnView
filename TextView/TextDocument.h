#ifndef TEXTDOC_INCLUDED
#define TEXTDOC_INCLUDED

#define MAX_LINE_LENGTH  102400

//#include "codepages.h"
#include "sequence.h"
#include <algorithm>
#include <windows.h>
#include <string.h>
//#include  <wchar.h>
#include "textview.h"
#include "mdw.h"
 //#include "textviewbase.h"
//#include "mntextview.h"
//#include "textviewinternal.h"
#include "CmpIterator.h"
typedef struct _BOM
{
	MN_ULong	bom;
	MN_ULong	len;
	int			type;
} BOM;


int my_strcmp(const wchar_t* str1, int len1, const wchar_t* str2, int len2);

class FindIterator	;
class TextIterator	;
class TextViewBase	;
class TextView		;
class MnTextView	;

class TextDocument
{
	friend class TextIterator	;
	friend class TextViewBase	;
	friend class TextView		;
	friend class MnTextView		;
	friend class FindIterator	;
	friend class CharCmpIterator ;
	typedef CharCmpIterator Iterator;

public:
	TextDocument();
	~TextDocument();
	Iterator GetIterator(ULONG offset)
	{
		return Iterator(this,offset);
	}
	//Iterator& GetEnd()
	//{
	//	return Iterator(charCount());
	//}

	bool	init(TCHAR *filename, int ConvertEncodingType = -1);
	bool	init(HANDLE hFile);
	bool	init(BYTE*  pFileDate, long fileLength, int format = NCP_UNKNOWN);
	bool	init_from_utf16(WCHAR*buffer, ULONG length);
	bool	init(HANDLE hFile, int ConvertEncodingType);
	

	bool	save(TCHAR *filename,	int ConvertEncodingType = -1, int utf_type = -1);
	bool	save(HANDLE hFile,		int ConvertEncodingType, int utf_type);
	bool	save(HANDLE hFile);
	bool	clear();
	bool	EmptyDoc();

	bool	Undo(ULONG *offset_start, ULONG *offset_end);
	bool	Redo(ULONG *offset_start, ULONG *offset_end);

	// UTF-16 text-editing interface
	ULONG	insert_text(ULONG offset_chars, const TCHAR *text, ULONG length);
	ULONG	replace_text(ULONG offset_chars, const TCHAR *text, ULONG length, ULONG erase_len);
	ULONG	replace_text(const TCHAR *find_text, ULONG find_length, const TCHAR *text, ULONG length);
	ULONG	erase_text(ULONG offset_chars, ULONG length);

	bool	find(ULONG start_offset_chars, const TCHAR *text, ULONG length, ULONG *find_offset);
	int		strcmp(const TCHAR *text, ULONG length, Iterator itor);

	ULONG	lineno_from_offset(ULONG offset);
	ULONG	offset_from_lineno(ULONG lineno);

	bool	lineinfo_from_offset(ULONG offset_chars, ULONG *lineno, ULONG *lineoff_chars,  ULONG *linelen_chars, ULONG *lineoff_bytes, ULONG *linelen_bytes);
	bool	lineinfo_from_lineno(ULONG lineno,                      ULONG *lineoff_chars,  ULONG *linelen_chars, ULONG *lineoff_bytes, ULONG *linelen_bytes);	

	TextIterator iterate(ULONG offset);
	TextIterator iterate_line(ULONG lineno, ULONG *linestart = 0, ULONG *linelen = 0);
	TextIterator iterate_line_offset(ULONG offset_chars, ULONG *lineno, ULONG *linestart = 0);

	ULONG	getdata(ULONG offset, BYTE *buf, size_t len);
	ULONG	getline(ULONG nLineNo, TCHAR *buf, ULONG buflen, ULONG *off_chars, bool fIncludeLineBreaker = false);

	

	int		getformat();
	int		setformat(int format);
	ULONG	linecount();
	ULONG	longestline(int tabwidth);
	ULONG	size_bytes();
	ULONG	charCount();

	bool	getStatistic(STATISTIC *pStat);
	bool	fillheader(int format, DWORD* pHeader, int * pHeader_length);

	void	getfilename(__out WCHAR* bufFullPath, __out WCHAR* bufTitle);

	static bool	WriteFileConvertUtf(HANDLE hFile, WCHAR* buffer16, int length16, int dest_format, __out ULONG *written_bytes);
	static int	Convert2Utf8(
								   __in  int		format, 
								   __in  BYTE*		buffer, 
								   __in  size_t		buffer_length, 
								   __out BYTE *		utf8str, 
								   __out size_t *	utf8len
							   );
	long GetConvertLookupTable(convert_type* convert_looup);
private:
	
	bool	init_linebuffer();
	void	update_linebuffer();
	ULONG	charoffset_to_byteoffset(ULONG offset_chars);
	ULONG	byteoffset_to_charoffset(ULONG offset_bytes);

	ULONG	count_chars(ULONG offset_bytes, ULONG length_chars);

	size_t	utf16_to_rawdata(const TCHAR *utf16str, size_t utf16len, BYTE *rawdata, size_t *rawlen);
	size_t	rawdata_to_utf16(const BYTE *rawdata, size_t rawlen, TCHAR *utf16str, size_t *utf16len);

	int		file_to_utf16(int format, BYTE* buffer, size_t buffer_length, __out TCHAR *utf16str, __out size_t *utf16len);

	//int		Convert2Utf8(int format, BYTE* buffer, size_t buffer_length, __out BYTE *utf8str, __out size_t *utf8len);
	//int		ConvertEncoding(int srcFormat, BYTE* buffer, size_t buffer_length, int destFormat, void *pBuffer, __out int *pByteCount, __out int * pCharCount);

	int		detect_file_format(int *headersize);
	int		detect_file_format(const BYTE* buffer, int buffer_length, __out int *headersize);
	ULONG	gettext(ULONG offsetbyte, ULONG lenbytes, TCHAR *buf, ULONG *len);
	int		getchar(ULONG offsetbyte, ULONG lenbytes, ULONG *pch32);

	// UTF-16 text-editing interface
	ULONG	insert_raw(ULONG offset_bytes, const TCHAR *text, ULONG length);
	ULONG	replace_raw(ULONG offset_bytes, const TCHAR *text, ULONG length, ULONG erase_len);
	ULONG	erase_raw(ULONG offset_bytes, ULONG length);

	int		CRLF_size(TCHAR *szText, int nLength);

	
	sequence m_seq;

	ULONG	m_nDocLength_chars;  //include header size
	ULONG	m_nDocLength_bytes;  //include header size

	ULONG *	m_pLineBuf_byte;
	ULONG *	m_pLineBuf_char;
	ULONG	m_nNumLines;
	
	int		m_nFileFormat;
	int		m_nHeaderSize;

	WCHAR	m_docTitle[MAX_PATH] ;
	WCHAR	m_docPath[MAX_PATH] ;

	long	m_nModifyLineIndex;
	long	m_nModifyLineChange;
	MDW		m_MuuDllWrapper;
};

class TextIterator
{
	
public:
	// default constructor sets all members to zero
	TextIterator()
		: text_doc(0), off_bytes(0), len_bytes(0)
	{
	}

	TextIterator(ULONG off, ULONG len, TextDocument *td)
		: text_doc(td), off_bytes(off), len_bytes(len)
	{
	
	}

	// default copy-constructor
	TextIterator(const TextIterator &ti) 
		: text_doc(ti.text_doc), off_bytes(ti.off_bytes), len_bytes(ti.len_bytes)
	{
	}

	// assignment operator
	TextIterator & operator= (TextIterator &ti)
	{
		text_doc  = ti.text_doc;
		off_bytes = ti.off_bytes;
		len_bytes = ti.len_bytes;
		return *this;
	}
	TCHAR operator *()
	{
		TCHAR buf;
		ULONG buflen = sizeof(TCHAR) ;
		//text_doc->gettext(off_bytes, len_bytes, &buf, &buflen);
		ULONG len	 = text_doc->m_seq.render(off_bytes, (seqchar*)&buf, sizeof(TCHAR) / sizeof(seqchar));;
		
		return (len == sizeof(seqchar)) ? buf : '\0';
	}
	
	//TextIterator &operator++()
	//{

	//}
	ULONG gettext(TCHAR *buf, ULONG buflen)
	{
		if(text_doc)
		{
			// get text from the TextDocument at the specified byte-offset
			ULONG len = text_doc->gettext(off_bytes, len_bytes, buf, &buflen);

			// adjust the iterator's internal position
			off_bytes += len;
			len_bytes -= len;

			return buflen;
		}
		else
		{
			return 0;
		}
	}

	//TCHAR operator *()
	//{
	//	TCHAR buf;
	//	ULONG buflen = sizeof(TCHAR) ;
	//	//text_doc->gettext(off_bytes, len_bytes, &buf, &buflen);
	//	ULONG len	 = text_doc->m_seq.render(off_bytes, (seqchar*)&buf, sizeof(TCHAR) / sizeof(seqchar));;
	//	
	//	return (len == 2) ? buf : '\0';
	//}

	/*int insert_text(TCHAR *buf, int buflen)
	{
		if(text_doc)
		{
			// get text from the TextDocument at the specified byte-offset
			int len = text_doc->insert(off_bytes, buf, buflen);

			// adjust the iterator's internal position
			off_bytes += len;
			return buflen;
		}
		else
		{
			return 0;
		}
	}

	int replace_text(TCHAR *buf, int buflen)
	{
		if(text_doc)
		{
			// get text from the TextDocument at the specified byte-offset
			int len = text_doc->replace(off_bytes, buf, buflen);

			// adjust the iterator's internal position
			off_bytes += len;
			return buflen;
		}
		else
		{
			return 0;
		}
	}

	int erase_text(int length)
	{
		if(text_doc)
		{
			// get text from the TextDocument at the specified byte-offset
			int len = text_doc->erase(off_bytes, length);

			// adjust the iterator's internal position
			off_bytes += len;
			return len;
		}
		else
		{
			return 0;
		}
	}*/


	operator bool()
	{
		return text_doc ? true : false;
	}

private:

	TextDocument *text_doc;
	
	ULONG off_bytes;
	ULONG len_bytes;
};

class LineIterator
{
public:
	LineIterator();

private:
	TextDocument *m_pTextDoc;
};

class FindIterator
{
private:
	TextDocument *m_pText_doc;
	
	LONG	m_off_char;
	LONG	m_len_char;
	LONG	m_next_offset;
	WCHAR*	m_pFind_text;
	LONG	m_find_text_len;
	WCHAR	m_buffer[MAX_LINE_LENGTH];
public:
	//FindIterator():
	//	m_pText_doc		(NULL	),
	//	m_off_char		(0		),
	//	m_len_char		(0		),
	//	m_next_offset	(NULL	),
	//	m_find_text_len	(0		),
	//	m_pFind_text	(0		)

	//{

	//}
	FindIterator(TextDocument *pText_doc):
		m_pText_doc		(pText_doc),
		m_off_char		(0		),
		m_len_char		(0		),
		m_next_offset	(NULL	),
		m_find_text_len	(0		),
		m_pFind_text	(0		)

	{

	}
	virtual	~FindIterator()
	{
		if(m_pFind_text)
			delete[] m_pFind_text;
	}
	WCHAR* find_text()
	{
		return m_pFind_text;
	}
	int getTextLength()
	{
		return m_find_text_len;
	}
	//bool find_init(TextDocument *text_doc, const WCHAR* find_text)
	//{
	//	if( m_pFind_text != NULL)
	//	{
	//		delete[]m_pFind_text;
	//		m_pFind_text = NULL;
	//	}
	//	
	//	m_pText_doc			= text_doc;
	//	m_find_text_len		= lstrlen(find_text); 
	//	m_pFind_text		= new WCHAR[m_find_text_len + 1];
	//	//m_next_offset		= start_offset;

	//	lstrcpy(m_pFind_text, find_text);
	//	m_pFind_text[m_find_text_len] = '\0';

	//	return true;
	//}
	bool find_init(const WCHAR* find_text)
	{
		if( m_pFind_text != NULL)
		{
			delete[]m_pFind_text;
			m_pFind_text = NULL;
		}
		
		m_find_text_len		= lstrlen(find_text); 
		m_pFind_text		= new WCHAR[m_find_text_len + 1];
		//m_next_offset		= start_offset;

		lstrcpy(m_pFind_text, find_text);
		m_pFind_text[m_find_text_len] = '\0';

		return true;
	}
	/*
	LONG find_forward(LONG start_offset, bool mach_case = false)
	{
		long i				= start_offset;//(start_offset >= 0) ? start_offset : m_next_offset;
		long offset_buf		= i - m_off_char;
		long end			= m_pText_doc->charCount() - m_find_text_len;

		for(; i <= end; i++)
		{
			if(i + m_find_text_len > m_off_char + m_len_char || i < m_off_char)
			{
				fill_buffer(i);
			}
			offset_buf = i - m_off_char;
			int cmplen = min(m_len_char - offset_buf, m_find_text_len);
			if(!mach_case)
			{
				if(wcsnicmp (m_pFind_text, m_buffer + offset_buf, cmplen) == 0)
				{
					m_next_offset = i + 1;
					return i;
				}
			}
			else
			{
				if(wcsncmp (m_pFind_text, m_buffer + offset_buf, cmplen) == 0)
				{
					m_next_offset = i + 1;
					return i;
				}
			}
		}
		return -1;
	}
	LONG find_backward(LONG start_offset, bool mach_case = false)
	{
		long i				= start_offset;//(start_offset >= 0) ? start_offset : m_next_offset;
		long offset_buf		= i - m_off_char;
		long end			= m_pText_doc->charCount() - m_find_text_len;

		for(; i >= 0; i--)
		{
			if(i + m_find_text_len > m_off_char + m_len_char || i < m_off_char)
			{
				fill_buffer(max(i - (MAX_LINE_LENGTH - m_find_text_len), 0 ));
			}
			offset_buf = i - m_off_char;
			int cmplen = min(m_len_char - offset_buf, m_find_text_len);
			if(!mach_case)
			{
				if(m_len_char - offset_buf >= m_find_text_len && wcsnicmp (m_pFind_text, m_buffer + offset_buf, m_find_text_len) == 0 )
				{
					m_next_offset = i - 1;
					return i;
				}
			}
			else
			{
				if(m_len_char - offset_buf >= m_find_text_len && wcsncmp (m_pFind_text, m_buffer + offset_buf, m_find_text_len) == 0)
				{
					m_next_offset = i - 1;
					return i;
				}
			}
		}
		return -1;
	}*/
	LONG find_forward2(LONG start_offset, bool mach_case = false)
	{
		long offset_buf = 0;
		m_off_char		= start_offset;
		m_len_char		= 0;
		for( int i = start_offset; i < m_pText_doc->charCount(); i++,offset_buf++)
		{
			if(offset_buf >= MAX_LINE_LENGTH - m_find_text_len)
			{
				offset_buf	= 0;
				m_off_char	= m_off_char + MAX_LINE_LENGTH;
				m_len_char	= 0;
			}

			if(m_len_char - offset_buf < m_find_text_len)
			{
				fill_buffer(m_off_char + m_len_char, m_len_char, false);
			}
			
			if(!mach_case)
			{
				if(m_len_char - offset_buf >= m_find_text_len && _wcsnicmp (m_pFind_text, m_buffer + offset_buf, m_find_text_len) == 0 )
				{
					m_next_offset = i - 1;
					return i;
				}
			}
			else
			{
				if(m_len_char - offset_buf >= m_find_text_len && wcsncmp (m_pFind_text, m_buffer + offset_buf, m_find_text_len) == 0)
				{
					m_next_offset = i - 1;
					return i;
				}
			}
		}
		return -1;
	}
	LONG find_backward2(LONG start_offset, bool mach_case = false)
	{
		///
		///?????
		///
		long offset_buf = MAX_LINE_LENGTH ;
		m_off_char		= start_offset ;
		m_len_char		= 0;
		for( int i = start_offset; i >= 0; i--,offset_buf--)
		{
			if(offset_buf < 0)
			{
				offset_buf	= MAX_LINE_LENGTH ;
				m_off_char	= start_offset - MAX_LINE_LENGTH;
				m_len_char	= 0;
			}
				
			if(offset_buf < MAX_LINE_LENGTH - m_len_char || m_len_char < m_find_text_len)
			{
				fill_buffer(m_off_char, MAX_LINE_LENGTH - m_len_char, true);
			}
			WCHAR* tmpPtr = m_buffer + offset_buf;
			if(!mach_case)
			{
				
				if(MAX_LINE_LENGTH - offset_buf >= m_find_text_len && _wcsnicmp (m_pFind_text, tmpPtr, m_find_text_len) == 0 )
				{
					m_next_offset = i - 1;
					return i;
				}
			}
			else
			{
				if(MAX_LINE_LENGTH - offset_buf >= m_find_text_len && wcsncmp (m_pFind_text, tmpPtr, m_find_text_len) == 0)
				{
					m_next_offset = i - 1;
					return i;
				}
			}
		}
		return -1;
	}
	//void fill_buffer(ULONG offset_char,bool fBack = false)
	//{
	//	m_off_char				= offset_char;
	//	m_len_char				= MAX_LINE_LENGTH;
	//	ULONG offset_bytes		= m_pText_doc->charoffset_to_byteoffset(offset_char);
	//	ULONG length_bytes_in	= min(sizeof(WCHAR) * MAX_LINE_LENGTH, m_pText_doc->m_nDocLength_bytes - offset_bytes);
	//	ULONG length_bytes_out	= m_pText_doc->gettext(offset_bytes, length_bytes_in, m_buffer, (ULONG*)&m_len_char);
	//}

	void fill_buffer(LONG offset_doc,LONG offset_buf, bool fBack = false)
	{
		LONG remain_length		= MAX_LINE_LENGTH - m_len_char;
		LONG request_length		= max(0, min(m_find_text_len, remain_length)) ;
		

		if(fBack)
		{
			request_length		= min(request_length, offset_doc);
			offset_doc			= offset_doc - request_length;
			offset_buf			= offset_buf - request_length;
		}

		ULONG offset_bytes		= m_pText_doc->charoffset_to_byteoffset(offset_doc);
		ULONG length_bytes_in	= sizeof(WCHAR) * request_length;
		ULONG length_bytes_out	= m_pText_doc->gettext(offset_bytes, length_bytes_in, m_buffer + offset_buf, (ULONG*)&request_length);
		m_len_char				+= request_length;

		if(fBack) m_off_char -= request_length;
	}
	long find_text_length()
	{
		return m_find_text_len;
	}
};

#endif