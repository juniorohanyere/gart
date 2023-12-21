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

void ec_init(void)
{
	int tts_init, cli_init;

	/* initialise ecraft */
	if (__ec == NULL)
	{
		__ec = calloc(sizeof(ec_t), 1);

		/* initialise text to speach (espeak) */
		tts_init = espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 500, NULL, 0);
		assert(tts_init != -1);

		/* disable tts and emoji by default */
		__ec->tts = EC_NONE;
		__ec->emoji = EC_NONE;
	}

	/* initialise termbox and ncurses */
	if (__ec->cli == EC_NONE)
	{
		cli_init = tb_init();
		assert(cli_init == 0);

		initscr();

		cbreak();
		/* enable special key input */
		keypad(stdscr, TRUE);

		refresh();

		__ec->cli = __EC_INIT;
	}
}

/**
 * ec_free - clean-up
 *	       this function must be called at the end of the user's program
 *	       in order to clean up or free all allocated blocks of  memory
 *
 * Return: return nothing
*/

void ec_free(void)
{
	int i = 0, interface;

	if (__ec->ecraft == NULL)
		return;

	while (__ec->ecraft[i] != NULL)
	{
		interface = __ec->ecraft[i]->__interface;

		__c_del_cstory(__ec->ecraft[i]->__cast);
		__m_del_cstory(__ec->ecraft[i]->__meta);
		if (interface == EC_CLI)
			delscreen(__ec->ecraft[i]->__interf.cli);
		else if (interface == EC_GUI)
		{
			/* delete gui window */
		}
		__free_craft(__ec->ecraft[i]);
		i++;
	}
	free(__ec->ecraft);
	if (__ec->cli == __EC_INIT)
		__scr_cleanup();
	if (__ec->gui == __EC_INIT)
	{
		/* end gui */
	}
	__ec->cli = EC_NONE, __ec->gui = EC_NONE;

	free(__ec);
}

/**
 * __free_craft - frees memory associated with a given craft
 *
 * @craft: pointer to the given craft
 *
 * Return: return nothing
*/

void __free_craft(ecraft_t *craft)
{
	if (craft == NULL)
		return;

	__free_cstory(craft);
}

/**
 * __scr_cleanup - clean up ncurses and termbox
 *		   this is by far the best clean up for ncurses I know of
 *		   any help on improving or making the ncurses clean up perfect
 *		   is highly appreciated
 *
 * Return: return nothing
*/

void __scr_cleanup(void)
{
	espeak_Terminate();
	endwin();

	del_curterm(cur_term);

	/* delwin(__pmtscr); why segmentation fault */
	delwin(stdscr);
	delwin(curscr);

	tb_shutdown();
}
