#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <term.h>
#include <espeak/speak_lib.h>
#include <termbox.h>

#include <ecraft.h>

void ec_start(char *title, char *subtitle, char *description)
{
	if (__ec == NULL)
	{
		dprintf(STDERR_FILENO,
			"invalid start: ecraft not initialized\n");
		abort();
	}
	__ec->title = strdup(title);
	__ec->subtitle = strdup(subtitle);
	__ec->desc = strdup(description);

	if (__ec->title == NULL || __ec->subtitle == NULL ||
		__ec->desc == NULL)
	{
		dprintf(STDERR_FILENO,
			"insufficient memory: coundn't start ecraft");
	}
	/* update screen with heading */
}

void ec_end(void)
{
	__ec->status = EC_END;
}

/**
 * ec_free - clean-up
 *	     this function must be called at the end of the user's program
 *	     in order to clean up or free all allocated blocks of memory
 *
 * Return: return nothing
*/

void ec_free(void)
{
	if (__ec == NULL)
		return;

	if (__ec->title != NULL)
		free(__ec->title);
	if (__ec->subtitle != NULL)
		free(__ec->subtitle);
	if (__ec->desc != NULL)
		free(__ec->desc);

	if (__ec->interf == EC_CLI)
	{
		delscreen(__ec->screen.cli);
		__cs_delem();	/* delete elements of the chat story */
		__cs_decraft();

		__ec_final();	/* final cleanup */
	}
}

/**
 * __ec_final - clean up ncurses and termbox
 *
 *		this is by far the best clean up for ncurses I know of
 *		any help on improving or making the ncurses clean up perfect is
 *		highly appreciated
 *
 * Return: return nothing
*/

void __ec_final(void)
{
	espeak_Terminate();
	endwin();

	del_curterm(cur_term);

	/* delwin(__pmtscr); why segmentation fault */
	delwin(stdscr);
	delwin(curscr);

	tb_shutdown();

	free(__ec);
}

void __cs_decraft(void)
{
	int64_t i, j;

	ecraft_t **ecraft = __ec->ecraft;

	for (i = 0; ecraft[i] != NULL; i++)
	{
		if (ecraft[i]->string != NULL)
			free(ecraft[i]->string);

		for (j = 0; j < ecraft[i]->nmemb; j++)
		{
			if (ecraft[i]->emoji[j] != NULL)
				free(ecraft[i]->emoji[j]);
		}

		free(ecraft[i]->emoji);
		free(ecraft[i]);
	}
	free(ecraft);
}
