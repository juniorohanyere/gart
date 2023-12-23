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
 * Description: subsequent call to ec_init() is useless unless ec_free() has
 *		being called, initialisation only occur once
 *		hence, it's not an error to call ec_init() multiple times
 *		without a call to ec_free()
 *
 * Return: return nothing
*/

void ec_init(const int interface)
{
	int tts_init;

	/* initialise ecraft, do not reinitialise */
	if (__ec == NULL)
	{
		__ec = calloc(sizeof(ec_t), 1);

		/* initialise text to speach (espeak) */
		tts_init = espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 500, NULL,
			0);
		assert(tts_init != -1);

		/* disable tts and emoji by default */
		__ec->tts = EC_NONE;
		__ec->emoji = EC_NONE;
		__ec->interf = interface;

		__ec_interf();

		__ec->status = EC_INIT;
	}
}

/**
 * ec_free - clean-up
 *	     this function must be called at the end of the user's program
 *	     in order to clean up or free all allocated blocks of memory
 *
 * Description: under construction TODO
 * Return: return nothing
*/

void ec_free(void)
{
}

/**
 * __ec_cleanup - clean up ncurses and termbox
 *		   this is by far the best clean up for ncurses I know of
 *		   any help on improving or making the ncurses clean up perfect
 *		   is highly appreciated
 *
 * Return: return nothing
*/

void __ec_cleanup(void)
{
	espeak_Terminate();
	endwin();

	del_curterm(cur_term);

	/* delwin(__pmtscr); why segmentation fault */
	delwin(stdscr);
	delwin(curscr);

	tb_shutdown();
}
