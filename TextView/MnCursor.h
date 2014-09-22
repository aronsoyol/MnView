#pragma once
class MnCursor
{
private:
	HCURSOR m_hCursor;
public :
	MnCursor();
	~MnCursor();
	HCURSOR GetCurosr();
};