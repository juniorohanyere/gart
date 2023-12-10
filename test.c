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
	craft_t *letter = newcraft("welcome", "chat-story", 0);
	craft_t *lette = newcraft("letter to my mother", "chat-story", 0);
	ecraft_t *ecraft = NULL;

	initcraft();

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
