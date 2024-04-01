#include <stdlib.h>
#include <string.h>

#include <gart.h>

/**
 * gdump  - dumps/adds a string to a dump/string buffer, to be later loaded by
 * 	    the gload function
 *
 * @string: the string to dump
 *
 * Return: return a char pointer
*/

char *gdump(const char *str)
{
	int64_t length = strlen(str);

	if ((*__art)->dbuf == NULL)
	{
		(*__art)->dbuf = malloc(sizeof(char) * (length + 1));

		strcpy((*__art)->dbuf, str);
	}
	else
	{
		(*__art)->dbuf = realloc((*__art)->dbuf,
			sizeof(char) * (strlen((*__art)->dbuf) + length + 1));
		strcat((*__art)->dbuf, str);
	}

	return ((*__art)->dbuf);
}
