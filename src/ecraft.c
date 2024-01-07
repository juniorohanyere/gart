#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <term.h>
#include <termbox.h>
#include <espeak/speak_lib.h>

#include <ecraft.h>

__EC;	/* bypass betty warining for use of global variables */

/**
 * ec_init - initialise ecraft
 *
 * @interface: EC_NONE, EC_CLI, or EC_GUI
 *
 * Description: subsequent call to ec_init() is useless unless ec_free() has
 *		being called, initialisation only occur once
 *		hence, it's not an error to call ec_init() multiple times
 *		without a call to ec_free()
 *
 * Return: return nothing
*/

void ec_init(int interface)
{
	int tts_init, buffer_size = 500, opts = 0;
	char *path = NULL;
	espeak_AUDIO_OUTPUT audio = AUDIO_OUTPUT_PLAYBACK;

	/* initialise ecraft, do not reinitialise */
	if (__ec == NULL)
	{
		__ec = calloc(sizeof(ec_t), 1);

		/* initialise text to speach (espeak) */
		tts_init = espeak_Initialize(audio, buffer_size, path, opts);
		assert(tts_init != -1);

		/* disable tts and emoji by default */
		__ec->tts = EC_NONE;
		__ec->emoji = EC_NONE;
		__ec->interf = interface;

		__ec_interf();

		__ec->status = EC_INIT;

		__ec->ec_size = 0;
		__ec->top = -1;
		__ec->bottom = 0;
		__ec->ref = 0;
	}
}
