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

void gstart(char *title, char *subtitle, char *description)
{
	if (__art == NULL)
	{
		dprintf(STDERR_FILENO,
			"invalid start: generative art not initialised\n");

		abort();
	}
	__art->title = strdup(title);
	__art->subtitle = strdup(subtitle);
	__art->desc = strdup(description);

	if (__art->title == NULL || __art->subtitle == NULL ||
		__art->desc == NULL)
	{
		dprintf(STDERR_FILENO,
			"insufficient memory: couldn't start generative art");
	}

	erase();
	__ghead();	/* update screen with headers */
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
	if (__art == NULL)
		return;

	if (__art->title != NULL)
		free(__art->title);
	if (__art->subtitle != NULL)
		free(__art->subtitle);
	if (__art->desc != NULL)
		free(__art->desc);

	if (__art->interf == GCLI)
	{
		__delem();	/* delete elements of the chat story */
		__dgbuffer();

		__gfinal();	/* final cleanup */
	}
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
	set_term(NULL);
	endwin();

	del_curterm(cur_term);

	delwin(__art->pmtwin);
	delwin(stdscr);
	delwin(curscr);

	tb_shutdown();
}

/**
 * __dgbuffer - frees memory associated with the screen buffer
 *
 * Return: return nothing
*/

void __dgbuffer(void)
{
	int64_t i, j;
	gbuffer_t **gbuffer = __art->gbuffer;

	for (i = 0; i < __art->vertice; i++)
	{
		if (gbuffer[i]->string != NULL)
			free(gbuffer[i]->string);

		for (j = 0; gbuffer[i]->unicode != NULL &&
			gbuffer[i]->unicode[j] != NULL; j++)
			free(gbuffer[i]->unicode[j]);

		free(gbuffer[i]->unicode);
		free(gbuffer[i]);
	}
	free(gbuffer);
}
