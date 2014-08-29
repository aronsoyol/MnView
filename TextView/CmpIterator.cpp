//#include <windows.h>
#include "CmpIterator.h"
#include "Textdocument.h"
CharCmpIterator::CharCmpIterator()
	: text_doc(0), offset(0)
{
}
CharCmpIterator::CharCmpIterator(TextDocument *doc,ULONG offset)
	: text_doc(doc), offset(offset)
{

}
	// default copy-constructor
CharCmpIterator::CharCmpIterator(const CharCmpIterator &src) 
	: text_doc(src.text_doc), offset(src.offset)
{
}
	// assignment operator
CharCmpIterator& CharCmpIterator::operator = (const CharCmpIterator &src)
{
	text_doc	= src.text_doc;
	offset		= src.offset;
	return *this;
}
CharCmpIterator& CharCmpIterator::operator++()
{
	offset ++;
	//if(offset == text_doc->charCount())
	return *this;
}
TCHAR CharCmpIterator::operator *()
{
	if(offset < text_doc->charCount())
	{
		TCHAR buf;
		ULONG buflen = sizeof(TCHAR) ;
		ULONG off_b  =text_doc->charoffset_to_byteoffset(offset);
		ULONG len	 = text_doc->m_seq.render(off_b, (seqchar*)&buf, sizeof(TCHAR) / sizeof(seqchar));
		return buf;
	}
	else
		return (TCHAR)0x0;
}
ULONG CharCmpIterator::Offset()
{
	return this->offset;
}
bool CharCmpIterator::operator == (const CharCmpIterator &src)
{
	return(!(*this != src));
}
bool CharCmpIterator::operator != (const CharCmpIterator &src)
{
	return(text_doc != src.text_doc  || src.offset != offset);
}
