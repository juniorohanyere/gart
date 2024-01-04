#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <termbox.h>

#include "ecraft.h"

/**
 * __ec_interf - sets the interface for a given chat story
 *
 * Description: initialise termbox and ncurses in cli mode
 *		termbox is used to handle unicode characters since
 *		ncurses only supports unicode for some specific
 *		range of terminal or terminal configuration
 *		termbox does the magic!
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
			cli_init = tb_init();
			assert(cli_init == 0);

			initscr();

			curs_set(1);

			raw();
			cbreak();

			/* enable special key input and scrolling effect */
			keypad(stdscr, TRUE);
			scrollok(stdscr, TRUE);

			refresh();

			__prompt_win();	/* prompt screen */

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

	raw();
	cbreak();
	noecho();

	/* enable special key input */
	keypad(__ec->pmtscr, TRUE);

	wattron(__ec->pmtscr, EC_BOLD);

	wrefresh(__ec->pmtscr);
}
