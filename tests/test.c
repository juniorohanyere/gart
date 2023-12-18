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
	char *str = malloc(sizeof(char) * 1024);
	cast_t *jun, *vic, *mic;
	ecraft_t *cstory;

	cstory = ec_cstory("Demo", "Subdemo", "Try the demo", EC_CLI);
	jun = c_cstory(cstory, "Junior Ohanyere", "Junior", "Ohanyere",
		"Twin J");
	vic = c_cstory(cstory, "Victory Micheal", "Victiory", "Daivid",
		"Davido");
	mic = c_cstory(cstory, "Mic", "Micheal", "Dominion", "No name");

	i = s_cstory(cstory, &jun, (char **)"g-f:f-s-f",
		"Hi, Vic\nWelcome to the Test", 1);
	j = s_cstory(cstory, &vic, (char **)"c-f",
		"What's good about the test? Uhn", 1);

	strcpy(str, "We just performed a new test, ");
	strcat(str, "and the test definitely looks good.\n");
	strcat(str, "Betty, Valgrind... Just give the new update a try!");

	s_cstory(cstory, &jun, (char **)"g-f:b-f-w-s-e", str, 1);
	s_cstory(cstory, &jun, (char **)"u-d-f:s-f-w-o-h",
		"Why don't you give it a try?", 1);

	s_cstory(cstory, &vic, (char **)"g-f", "Ok, I'll give it a try later",
		1);

	s_cstory(cstory, &jun, (char **)"b-f-w-s-e", "Alright, buddy", 1);

	s_cstory(cstory, &mic, (char **)"s-s-f:s-s-f:s-f",
		"Hey guys, what's popping! I just got news about ecraft", 1);

	free(str);

	ec_free();

	return (0);
}
