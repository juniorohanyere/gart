#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <termbox.h>

#include "ecraft.h"

/**
 * __set_interf - sets the interface for a given craft
 *
 * @craft: pointer to the given craft
 *
 * Return: return nothing
*/

void __set_interf(ecraft_t *craft)
{
	switch (craft->__interface)
	{
		case EC_CLI:
			craft->__interf.cli = newterm(NULL, stdout, stdin);
			scrollok(stdscr, TRUE);
			__prompt_win();

			break;

		case EC_GUI:
			if (__ec->gui == EC_NONE)
			{
				/* init gui */
				__ec->gui = __EC_INIT;
			}
			/* ecraft->interf.gui = TODO */

			break;

		default:	/* EC_NONE */
			return;	/* do nothing */
	}
}

/**
 * __prompt_win - creates a new window screen for prompt at the bottom of the
 *		  stdscr
 *
 * Return: return nothing
*/

void __prompt_win(void)
{
	int x, y;

	getmaxyx(stdscr, y, x);

	/* set the height of the prompt screen to 1 */
	__ec->pmtscr = newwin(1, x, y - 1, 0);
	/* noecho(); */
}
