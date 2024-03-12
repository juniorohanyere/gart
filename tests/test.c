#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/gart.h"

/**
 * main - entry point
 *
 * Description: test the gart library (libgart.so + libgcstory.so)
 *
 * Return: always return 0
*/

int main(void)
{
	char *str, *emoji = "s-s-f:u-d-f:s-s-f", *em = "c-f:f-b-a-k:c-f";
	elem_t *jun, *sam, *vic;

	ginit(GCLI);
	gemoji("u");	/* enable pictorial emoji */
	gtts();

	str = malloc(sizeof(char) * 1024);

	jun = gcreate("Junior Ohanyere", "Junior", "Ohanyere");
	sam = gcreate("Samson Sam", "Samson", "Samuel");
	vic = gcreate("Jimmy Victor", "Jim", "Victor");

	strcpy(str,
		"A dialogue on gart library usage for creating chat stories");
	gstart("Generative Art", "Chat Story", str);

	gload(jun, emoji, "Do you know?");
	gload(sam, em, "Know what?");

	strcpy(str, "Do you know that everything going on here ");
	strcat(str, "is a programmed chat story?");
	gload(jun, emoji, str);

	emoji = "s-s-f:u-d-f";
	gload(vic, emoji, "What do you mean?");

	em = "f-w-p-e";
	gload(sam, em, " ");

	gfinal();

	free(str);

	return (0);
}
