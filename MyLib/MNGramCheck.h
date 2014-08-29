#define MN_VOWEL_WRONG	0
#define MN_VOWEL_QANGA	1
#define MN_VOWEL_HUNDI	2
#define MN_VOWEL_SARMAG	3

typedef int MN_VOWEL_TYPE;
MN_VOWEL_TYPE CheckVowel(WCHAR *word, int length);
