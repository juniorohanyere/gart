#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <espeak/speak_lib.h>

#include "ecraft.h"

/**
 * ec_tts - sets the tts flag to true
 *
 * Return: return nothing
*/

void ec_tts(void)
{
	__tts = __EC_INIT;
}

/**
 * ec_ntts - sets the tts flag to false
 *
 * Return: return nothing
*/

void ec_ntts(void)
{
	__tts = EC_NONE;
}

/**
 * __ec_tts - enable text to speech mode
 *
 * @buffer: the text to convert to speech
 *
 * Description: tts is disabled by default
 *
 * Return: return nothing
*/

void __ec_tts(char *buffer)
{
	/* initialise espeak */
	assert(espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, strlen(buffer) + 1,
		NULL, 0) >= 0);

	/* synthesize the speech */
	espeak_Synth(buffer, strlen(buffer) + 1, 0, POS_CHARACTER, 0,
		espeakCHARS_AUTO, NULL, NULL);

	/* synchronize the speech */
	espeak_Synchronize();

	/* clean up espeak */
	espeak_Terminate();
}
