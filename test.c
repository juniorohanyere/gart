#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ecraft.h"

/**
 * main - entry point
 *
 * Description: test the library
 *
 * Return: always return 0
*/

int main(void)
{
	cast_t *cast;
	craft_t *letter, *lette, *new, *nw;
	ecraft_t *ecraft = NULL;

	letter = initcraft("welcome", "chat-story", EC_CLI);
	lette = initcraft("letter to my mother", "chat-story", EC_CLI);
	new = initcraft("HOME", "letter", EC_CLI);
	nw = initcraft("nEW", "letter", EC_CLI);

	while (__ecraft != NULL)
	{
		printf("%s\n", __ecraft->craft->__title);
		__ecraft = __ecraft->next;
	}

	cast = newcast("Junior Ohanyere", "Junior", "Ohanyere", "TJ");

	printf("%s\n", cast->__dname);
	/* pushcraft(letter, cast, "Welcome to the Test", "smile:angry"); */

	return (0);
}
