#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <gart.h>

/**
 * gtts - sets the tts flag to true
 *
 * Description: text to speech is disabled by default
 *
 * Return: return nothing
*/

void gtts(void)
{
	(*__art)->tts = GINIT;
}

/**
 * gntts - sets the tts flag to false
 *
 * Description: default text to speech mode
 *
 * Return: return nothing
*/

void gntts(void)
{
	(*__art)->tts = GNONE;
}

/**
 * __gtts - enables text to speech mode if tts flag is set to true
 *
 * @str: the text to convert to speech
 *
 * Description: tts flag (__art->tts) is disabled by default
 *
 * Return: return nothing
*/

void __gtts(char *str)
{
	char *command;

	if ((*__art)->tts == GNONE)
		return;

	command = malloc(sizeof(char) * 1024);

	strcpy(command, _TTSPATH);
	strcat(command, " \"");
	strcat(command, str);
	strcat(command, "\"");

	system(command);

	free(command);
}
