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
	strcat((*__art)->dbuf, str);

	return ((*__art)->dbuf);
}
