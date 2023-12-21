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
	char *str, *emoji = "s-s-f:u-d-f";
	char **emojis = malloc(sizeof(char *) * 1024);
	cast_t *jun, *vic, *mic;
	cast_t **casts = malloc(sizeof(cast_t *) * 1024);
	ecraft_t *cstory;

	str = malloc(sizeof(char) * 1024);

	ec_init();

	/* ec_tts(); */
	ec_emoji("u");
	/* ec_scroll(0, 0, 0);	dur.dir.step. */

	strcpy(str,
		"An overview on ecraft library usage for create chat stories");

	cstory = ec_cstory("Electronic Craft", "Chat Story", str, EC_CLI);

	jun = c_cstory(cstory, "Junior Ohanyere", "Junior", "Ohanyere",
		"Twin J");
	vic = c_cstory(cstory, "Victory Micheal", "Victiory", "Daivid",
		"Davido");
	mic = c_cstory(cstory, "Mic James", "Micheal", "Dominion", "No name");

	casts[0] = vic;
	casts[1] = mic;
	casts[2] = NULL;

	emojis[0] = NULL;
	emojis[1] = "s-s-f:u-d-f";

	i = s_cstory(cstory, &jun, &emoji,
		"Do you know?", 1);
	j = s_cstory(cstory, casts, emojis,
		"Know what?", 2);

	strcpy(str, "Do you know that everything going on here\n");
	strcat(str, "is a programmed chat story?");

	s_cstory(cstory, &jun, &emoji, str, 1);

	s_cstory(cstory, &vic, &emoji, "What do you mean?", 1);

	emoji = "f-w-p-e";
	s_cstory(cstory, &mic, &emoji, NULL, 1);

	emoji = "s-f-w-o-h";
	s_cstory(cstory, &jun, &emoji, "Don't worry, I can explain.", 1);

	emoji = "";
	s_cstory(cstory, &mic, &emoji,
		"Please do, because I'm curious and nervous.", 1);

	strcpy(str, "Everything here is programmed ");
	strcat(str, "from a programming library called ecraft.");
	emoji = "s-f-w-o-h";
	s_cstory(cstory, &jun, &emoji, str, 1);

	casts[0] = mic;
	emojis[0] = "f-w-o-e-a-h-o-m";

	casts[1] = vic;
	emojis[1] = "t-f";

	s_cstory(cstory, casts, emojis, "ecraft???", 2);
	s_cstory(cstory, &vic, &emojis[1], "What's ecraft?", 1);

	free(str);
	free(emojis);
	free(casts);

	ec_free();

	return (0);
}
