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

	stage(cstory, "Hi, Vic\nWelcome to the Test", "g-f ", jun);
	stage(cstory, "What's good about the test? Uhn", "c-f", vic);

	stage(cstory, "We just performed a new test, and the test definitely \
looks good.\nBetty, Valgrind... Just give the new update a try!", "g-f", jun);
	stage(cstory, "Why don't you give it a try?", "u-d-f", jun);

	stage(cstory, "Ok, I'll give it a try later", "g-f", vic);

	stage(cstory, "Alright, buddy", "b-f-w-s-e", jun);

	stage(cstory, "Hey guys, what's popping! I just got news about ecraft",
		"s-s-f", mic);

	freecraft();

	return (0);
}
