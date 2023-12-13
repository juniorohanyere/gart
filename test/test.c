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

	stage(cstory, "Hi, Vic\nWelcome to the Test", "grinning-face:crying-face", jun);
	stage(cstory, "What's good about the test? Uhn", "crying-face", vic);

	freecraft();

	return (0);
}
