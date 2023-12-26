#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/ecraft.h"

/**
 * main - entry point
 *
 * Description: test the library
 *
 * Return: always return 0
*/

int main(void)
{
	char *str, *emoji = "s-s-f:u-d-f:s-s-f", *em = "c-f:f-b-a-k:c-f";
	elem_t *jun, *sam, *vic;

	ec_init(EC_CLI);
	ec_emoji("u");	/* enable unicode emoji */

	/* ec_tts(); */

	str = malloc(sizeof(char) * 1024);

	jun = ec_elem("Junior Ohanyere", "Junior", "Ohanyere");
	sam = ec_elem("Samson Sam", "Samson", "John");
	vic = ec_elem("Jimmy Victor", "Jim", "Victor");

	strcpy(str,
		"A dialogue on ecraft library usage for creating chat stories"
	);
	ec_create("Electronic Craft", "Chat Story", str);

	ec_load(&jun, &emoji, "Do you know?", 1);
	ec_load(&sam, &em, "Know what?", 1);

	strcpy(str, "Do you know that everything going on here\n");
	strcat(str, "is a programmed chat story?");
	ec_load(&jun, &emoji, str, 1);

	emoji = "s-s-f:u-d-f";
	ec_load(&vic, &emoji, "What do you mean?", 1);

	em = "f-w-p-e";
	ec_load(&sam, &em, NULL, 1);

	emoji = "s-f-w-o-h:b-f-w-s-e";
	ec_load(&jun, &emoji, "Don't worry, I can explain.", 1);

	em = "";
	ec_load(&sam, &em, "Please do, because I'm curious and nervous.", 1);

	strcpy(str, "Everything here is programmed ");
	strcat(str, "from a programming library called ecraft.");
	emoji = "s-f-w-o-h";
	ec_load(&jun, &emoji, str, 1);

	emoji = "f-w-o-e-a-h-o-m";
	ec_load(&sam, &emoji, "ecraft???", 1);

	emoji = "t-f:t-f:t-f";
	ec_load(&vic, &emoji, "What's ecraft?", 1);

	ec_final();

	free(str);

	return (0);
}
