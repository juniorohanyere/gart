#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ecraft.h"

/**
 * main - entry point
 *
 * Description: test the library
 *
 * Return: always return 0
*/

int main(void)
{
	int i, j;
	cast_t *jun, *vic;
	craft_t *cstory;

	cstory = initcraft("welcome", "chat-story", EC_CLI);

	jun = newcast("Junior Ohanyere", "Junior", "Ohanyere", "Twin J");
	vic = newcast("Victory Micheal", "Victiory", "Daivid", "Davido");

	echo(cstory, "Hi, Vic\nWelcome to the Test", "smile:angry:crying-face", jun);
	echo(cstory, "What's good about the test? Uhn", "angry:crying-cat:loudly-crying-face", vic);

	freecraft();

	return (0);
}
