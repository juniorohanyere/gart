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
	cast_t *jun, *vic, *mic;
	craft_t *cstory;

	cstory = initcraft("welcome", "chat-story", EC_CLI);

	jun = newcast("Junior Ohanyere", "Junior", "Ohanyere", "Twin J");
	vic = newcast("Victory Micheal", "Victiory", "Daivid", "Davido");
	mic = newcast("Mic", "Micheal", "Dominion", "No name");

	stage(cstory, "Hi, Vic\nWelcome to the Test", "grinning-face ", jun);
	stage(cstory, "What's good about the test? Uhn", "crying-face", vic);

	stage(cstory, "We just performed a new test, and the test definitely looks good", "grinning-face", jun);
	stage(cstory, "Why don't you give it a try?", "grinning-face", jun);

	stage(cstory, "Ok, I'll give it a try later", "grinning-face", vic);

	stage(cstory, "Alright, buddy", "grinning-face", jun);

	stage(cstory, "Hey guys, what's popping! I just got news about ecraft",
		"grinning-face ", mic);

	freecraft();

	return (0);
}
