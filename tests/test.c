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
	int i, j;
	cast_t *jun, *vic, *mic;
	ecraft_t *cstory;

	cstory = ec_cstory("welcome", "chat-story", EC_CLI);
	jun = c_cstory(cstory, "Junior Ohanyere", "Junior", "Ohanyere", "Twin J");
	vic = c_cstory(cstory, "Victory Micheal", "Victiory", "Daivid", "Davido");
	mic = c_cstory(cstory, "Mic", "Micheal", "Dominion", "No name");

	i = s_cstory(cstory, jun, "Hi, Vic\nWelcome to the Test", "g-f");
	j = s_cstory(cstory, vic, "What's good about the test? Uhn", "c-f");

	s_cstory(cstory, jun, "We just performed a new test, and the test \
definitely looks good.\n\
Betty, Valgrind... Just give the new update a try!", "g-f:b-f-w-s-e");
	s_cstory(cstory, jun, "Why don't you give it a try?", "u-d-f");

	s_cstory(cstory, vic, "Ok, I'll give it a try later", "g-f");

	s_cstory(cstory, jun, "Alright, buddy", "b-f-w-s-e");

	s_cstory(cstory, mic,
		"Hey guys, what's popping! I just got news about ecraft",
		"s-s-f");

	ec_free();

	return (0);
}
