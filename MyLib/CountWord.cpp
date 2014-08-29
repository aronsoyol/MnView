#include "CountWord.h"
int my_strcmp1(const WCHAR* str1, int len1, const WCHAR* str2, int len2)
{
    int i;
	int end = min(len1, len2);
    for(i = 0; str1[i] == str2[i]; i++)
    {
        if(i == end - 1)
            return 0;
    }
    return str1[i] - str2[i];
}
int CountWord(WCHAR* buffer, int length, const WCHAR* separator)
{
	int i		= 0;
	int count	= 0;
	int separator_len = lstrlen(separator);
	while(i < length)
	{
		int cmp=0;
		int word_len =0;
		while(i < length && (cmp = my_strcmp1(&buffer[i], min(separator_len, length - i), separator, separator_len)) == 0)
		{
			i++;
		}
		while(i < length && (cmp = my_strcmp1(&buffer[i], min(separator_len, length - i), separator, separator_len)) != 0)
		{
			i++;word_len++;
		}
		if(word_len > 0)
			count ++;
	}
	return count;
}
