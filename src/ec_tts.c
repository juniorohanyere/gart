#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <ecraft.h>

/**
 * ec_tts - sets the tts flag to true
 *
 * Description: text to speech is disabled by default
 *
 * Return: return nothing
*/

void ec_tts(void)
{
	__ec->tts = EC_INIT;
}

/**
 * ec_ntts - sets the tts flag to false
 *
 * Description: default text to speech mode
 *
 * Return: return nothing
*/

void ec_ntts(void)
{
	__ec->tts = EC_NONE;
}

/**
 * __ec_tts - enables text to speech mode if tts flag is set to true
 *
 * @tts_msg: the text to convert to speech
 *
 * Description: tts flag (__ec->tts) is disabled by default
 *
 * Return: return nothing
*/

void __ec_tts(char *tts_msg)
{
	char *command = malloc(sizeof(char) * 1024);

	strcpy(command, _TTSPATH);
	strcat(command, " \"");
	strcat(command, tts_msg);
	strcat(command, "\"");

	system(command);

	free(command);
}
