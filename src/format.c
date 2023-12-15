#include "ecraft.h"

/**
 * __craftfmt - list of valid formats for initcraft function
 *
 * Return: return a pointer to the a list of valid formats
*/

char **__craftfmt(void)
{
	char *format[] = {
		"chat-story", "story", "comic", "letter", "essay", NULL
	};

	return (
