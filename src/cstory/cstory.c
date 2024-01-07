#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <term.h>
#include <espeak/speak_lib.h>
#include <termbox.h>

#include <ecraft.h>

/**
 * ec_start - begins new page for the craft, setting up headers base on
 *	      parameters passed to the function
 *
 * @title: the title of the craft
 * @subtitle: subtitle of the craft
 * @description: the description of the craft (can be a very short sentence)
 *
 * Description: setting all parameters to NULL discards header set up
 *
 * Return: return nothing
*/

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

	erase();
	/* update screen with heading */
	__ec_head();
}

/**
 * ec_final - clean-up
 *	     this function must be called at the end of the user's program
 *	     in order to clean up or free all allocated blocks of memory
 *
 * Return: return nothing
*/

void ec_final(void)
{
	if (__ec == NULL)
		return;

	if (__ec->title != NULL)
		free(__ec->title);
	if (__ec->subtitle != NULL)
		free(__ec->subtitle);
	if (__ec->desc != NULL)
		free(__ec->desc);

	espeak_Terminate();

	if (__ec->interf == EC_CLI)
	{
		__delem();	/* delete elements of the chat story */
		__decraft();

		__ec_final();	/* final cleanup */
	}
	free(__ec);
	__ec = NULL;
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
	set_term(NULL);
	endwin();

	del_curterm(cur_term);

	delwin(__ec->pmtscr);
	delwin(stdscr);
	delwin(curscr);

	tb_shutdown();
}

/**
 * __decraft - frees memory associtated with an ecarft
 *
 * Return: return nothing
*/

void __decraft(void)
{
	int64_t i, j;

	ecraft_t **ecraft = __ec->ecraft;

	for (i = 0; i < __ec->ec_size; i++)
	{
		if (ecraft[i]->string != NULL)
			free(ecraft[i]->string);

		for (j = 0; ecraft[i]->unicode != NULL &&
			ecraft[i]->unicode[j] != NULL; j++)
			free(ecraft[i]->unicode[j]);

		free(ecraft[i]->unicode);
		free(ecraft[i]);
	}
	free(ecraft);
}
