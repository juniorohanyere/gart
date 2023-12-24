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
	elem_t *jun = malloc(sizeof(elem_t));
	elem_t *sam = malloc(sizeof(elem_t));
	elem_t *vic = malloc(sizeof(elem_t));

	ec_init(EC_CLI);
	ec_emoji("w");	/* enable unicode emoji */

	ec_tts();

	str = malloc(sizeof(char) * 1024);

	ec_create(jun, "Junior Ohanyere", "Junior", "Ohanyere");
	ec_create(sam, "Samson Sam", "Samson", "John");
	ec_create(vic, "Jimmy Victor", "Jim", "Victor");

	strcpy(str,
		"An overview on ecraft library usage for create chat stories");
	ec_start("Electronic Craft", "Chat Story", str);

	ec_echo(&jun, &emoji, "Hi, welcome to ecraft", 1);

	ec_echo(&sam, &em, "Hi, friends", 1);
	ec_echo(&vic, &emoji, "Hi, Junior", 1);
	ec_echo(&jun, &emoji, "Hi", 1);

	ec_echo(&sam, &em, "who are u", 1);
	ec_echo(&vic, &emoji, "I am a man", 1);
	ec_echo(&jun, &emoji, "I am a boy", 1);

	ec_echo(&sam, &em, "Hi, friends", 1);
	ec_echo(&vic, &emoji, "Hi, Junior", 1);
	ec_echo(&jun, &emoji, "Hi, who", 1);

	ec_free();

	return (0);
}
