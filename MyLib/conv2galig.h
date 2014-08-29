
typedef struct Galig_
{
	WCHAR	letter;
	WCHAR	galig[3];
	int		width;
} GALIG;

extern GALIG GaligMap[];
//extern btree::btree_map<WCHAR,GALIG>  GaligMap;
void Convert(WCHAR* srcString, int* destString, int length);