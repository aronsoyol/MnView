#pragma once
#include "mndatatype.h"
class TextDocument;
class CharCmpIterator
{
private:

	TextDocument *	text_doc;
	
	MN_ULong		offset;

public:
	CharCmpIterator();
	CharCmpIterator(TextDocument* doc,	MN_ULong offset);
		// default copy-constructor
	CharCmpIterator(const CharCmpIterator &src) ;
		// assignment operator
	CharCmpIterator & operator = (const CharCmpIterator &src);
	CharCmpIterator & operator++();
	wchar_t operator *();
	MN_ULong Offset();
	bool operator == (const CharCmpIterator &src);
	bool operator != (const CharCmpIterator &src);
};