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

int64_t ec_start(char *title, char *subtitle, char *description)
{
	int64_t i = ++(*__ec)->size;

	__ec[i] = calloc(sizeof(ec_t), 1);

	if (__ec[i] == NULL)
		return (-1);

	__ec[i]->status = EC_INIT;	/* EC_START */

	__ec[i]->ec_size = 0;
	__ec[i]->top = -1;
	__ec[i]->bottom = 0;
	__ec[i]->ref = 0;

	__ec[i]->title = strdup(title);
	__ec[i]->subtitle = strdup(subtitle);
	__ec[i]->desc = strdup(description);

	if (__ec[i]->title == NULL || __ec[i]->subtitle == NULL ||
		__ec[i]->desc == NULL)
	{
		dprintf(STDERR_FILENO,
			"insufficient memory: coundn't start ecraft");
	}

	(*__ec)->index = i;

	erase();
	/* update screen with heading */
	__ec_head();

	return (i);
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
	int64_t i;

	if (__ec == NULL)
		return;

	for (i = 1; i <= (*__ec)->size; i++)
	{
		if (__ec[i] == NULL)
			return;

		if (__ec[i]->title != NULL)
			free(__ec[i]->title);
		if (__ec[i]->subtitle != NULL)
			free(__ec[i]->subtitle);
		if (__ec[i]->desc != NULL)
			free(__ec[i]->desc);

		if ((*__ec)->interf == EC_CLI)
		{
			__decraft(i);
		}
		free(__ec[i]);
		__ec[i] = NULL;
	}
	__ec_final();	/* final cleanup */

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
	__delem();	/* delete elements of the chat story */

	set_term(NULL);
	endwin();

	del_curterm(cur_term);

	delwin((*__ec)->pmtscr);
	delwin(stdscr);
	delwin(curscr);

	tb_shutdown();

	free(*__ec);
}

/**
 * __decraft - frees memory associtated with an ecarft
 *
 * Return: return nothing
*/

void __decraft(int64_t index)
{
	int64_t i, j;

	ecraft_t **ecraft = __ec[index]->ecraft;

	for (i = 0; i < __ec[index]->ec_size; i++)
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
