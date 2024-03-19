#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <term.h>
#include <termbox.h>

#include <gart.h>

/**
 * gstart - start a new art, setting up headers based on parameters passed to
 *	    the function
 *
 * @title: the title of the genarative art
 * @subtitle: the subtitle of the art
 * @description: the description of the art (can be a phrase or a clause)
 *
 * Description: setting all parameters to NULL discards header set-up
 *
 * Return: return nothing
*/

int64_t gstart(char *title, char *subtitle, char *description)
{
	int64_t i = ++(*__art)->size;

	__art[i] = calloc(sizeof(gart_t), 1);
	if (__art[i] == NULL)
	{
		dprintf(STDERR_FILENO, "fatal: insufficient memory\n");

		return (-1);
	}

	__art[i]->status = GINIT;

	__art[i]->vertice = 0;
	__art[i]->top = -1;
	__art[i]->bottom = 0;
	__art[i]->ref = 0;

	__art[i]->title = strdup(title);
	__art[i]->subtitle = strdup(subtitle);
	__art[i]->desc = strdup(description);

	if (__art[i]->title == NULL || __art[i]->subtitle == NULL ||
		__art[i]->desc == NULL)
	{
		dprintf(STDERR_FILENO,
			"insufficient memory: couldn't start generative art");

		return (-1);
	}

	(*__art)->index = i;

	erase();
	__ghead();	/* update screen with headers */

	return (i);
}

/**
 * gfinal - clean-up
 *
 * Description: must be called at the end of the user's program in order to
 *		clean or free up all allocated blocks of memory, initiated by
 *		the library alone
 *
 * Return: return nothing
*/

void gfinal(void)
{
	int64_t i;

	if (__art == NULL)
		return;

	for (i = 1; i <= (*__art)->size; i++)
	{
		if (__art[i] == NULL)
			return;

		if (__art[i]->title != NULL)
			free(__art[i]->title);
		if (__art[i]->subtitle != NULL)
			free(__art[i]->subtitle);
		if (__art[i]->desc != NULL)
			free(__art[i]->desc);

		if ((*__art)->interf == GCLI)
		{
			__gscr_free(i);
		}
		free(__art[i]);
		__art[i] = NULL;
	}
	__gfinal();	/* final cleanup */
	free(__art);
	__art = NULL;
}

/**
 * __gfinal - clean up ncurses and termbox
 *
 * Description: this is by far the best clean up for ncurses I know of
 *		any help on imporving or making the ncurses clean up perfect is
 *		highly appreciated
 *
 * Return: return nothing
*/

void __gfinal(void)
{
	__glbl_free();	/* delete elements of the chat story */

	set_term(NULL);
	endwin();

	del_curterm(cur_term);

	delwin((*__art)->pmtwin);
	delwin(stdscr);
	delwin(curscr);

	tb_shutdown();

	free(*__art);
}

/**
 * __gscr_free - frees memory associated with the screen buffer
 *
 * Return: return nothing
*/

void __gscr_free(int64_t index)
{
	int64_t i, j;
	gscr_t **scr = __art[index]->scr;

	for (i = 0; i < __art[index]->vertice; i++)
	{
		if (scr[i]->string != NULL)
			free(scr[i]->string);

		for (j = 0; scr[i]->unicode != NULL &&
			scr[i]->unicode[j] != NULL; j++)
			free(scr[i]->unicode[j]);

		free(scr[i]->unicode);
		free(scr[i]);
	}
	free(scr);
}
