#include "MnTextBoxBase.h"


MnTextBoxBase::MnTextBoxBase(HWND hWnd) :
	MnTextView(hWnd)
{

}


MnTextBoxBase::~MnTextBoxBase()
{
}
//
//	Retrieve the specified range of text and copy it to supplied buffer
//	szDest must be big enough to hold nLength characters
//	nLength includes the terminating NULL
//
ULONG MnTextBoxBase::ApiGetText(wchar_t *szDest, ULONG nStartOffset, ULONG nLength)
{
	ULONG copied = 0;

	if (nLength > 1)
	{
		TextIterator itor = m_pTextDoc->iterate(nStartOffset);
		copied = itor.gettext(szDest, nLength - 1);

		// null-terminate
		szDest[copied] = 0;
	}

	return copied;
}