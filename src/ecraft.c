#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <term.h>
#include <termbox.h>
#include <espeak/speak_lib.h>

#include <ecraft.h>

__ECRAFT;
__PMTSCR;
__EC_CLI;
__EC_GUI;
__EC_TTS;

void ec_init(void)
{
	int cli_init;

	/* initialise espeak */
	if (__cli == EC_NONE && __gui == EC_NONE)
	{
		cli_init = espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 500, NULL, 0);

		assert(cli_init != -1);
	}

	/* initialise termbox and ncurses */
	if (__cli == EC_NONE)
	{
		cli_init = tb_init();
		assert(cli_init == 0);

		initscr();

		cbreak();
		/* enable special key input */
		keypad(stdscr, TRUE);

		refresh();

		__cli = __EC_INIT;
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

	if (__ecraft == NULL)
		return;

	while (__ecraft[i] != NULL)
	{
		interface = __ecraft[i]->__interface;

		__c_del_cstory(__ecraft[i]->__cast);
		__m_del_cstory(__ecraft[i]->__meta);
		if (interface == EC_CLI)
			delscreen(__ecraft[i]->__interf.cli);
		else if (interface == EC_GUI)
		{
			/* delete gui window */
		}
		__free_craft(__ecraft[i]);
		i++;
	}
	free(__ecraft);
	if (__cli == __EC_INIT)
		__scr_cleanup();
	if (__gui == __EC_INIT)
	{
		/* end gui */
	}
	__cli = EC_NONE, __gui = EC_NONE;
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
	endwin();

	del_curterm(cur_term);

	/* delwin(__pmtscr); why segmentation fault */
	delwin(stdscr);
	delwin(curscr);

	tb_shutdown();
}
