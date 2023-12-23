#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <termbox.h>

#include "ecraft.h"

/**
 * __ec_interf - sets the interface for a given craft
 *
 * @craft: pointer to the given craft
 *
 * Return: return nothing
*/

void __ec_interf(void)
{
	int cli_init;

	switch (__ec->interf)
	{
		case EC_NONE:
			break;	/* do nothing */

		case EC_CLI:
			/*
			 * initialise termbox and ncurses
			 * termbox is used to handle unicode characters since
			 * ncurses only supports unicode for some specific
			 * range of terminal or terminal configuration
			 * termbox does the magic!
			*/
			cli_init = tb_init();
			assert(cli_init == 0);

			initscr();
			cbreak();
			/* enable special key input */
			keypad(stdscr, TRUE);
			refresh();
			/* create new terminal screen */
			__ec->screen.cli = newterm(NULL, stdout, stdin);
			scrollok(stdscr, TRUE);
			__ec_pmtwin();	/* prompt screen */

			break;

		case EC_GUI:
			/* ecraft->interf.gui = TODO */

			break;

		default:
			dprintf(STDERR_FILENO,
				"invalid interface: couldn't set up interface"
			);

			abort();
	}
}

/**
 * __ec_pmtwin - creates a new window screen for prompt at the bottom of the
 *		  stdscr
 *
 * Return: return nothing
*/

void __ec_pmtwin(void)
{
	int x, y;

	getmaxyx(stdscr, y, x);

	/* set the height of the prompt screen to 1 */
	__ec->pmtscr = newwin(1, x, y - 1, 0);
	/* noecho(); */
}
