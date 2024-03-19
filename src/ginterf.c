#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <termbox.h>

#include <gart.h>

/**
 * __ginterf - set the interface for a given chat story
 *
 * Description: initialise termbox and ncurses in cli mode
 *		termbox is used to handle unicode characters since ncurses only
 *		supports unicode for some specific range of terminal or
 *		terminal configurations
 *		termbox does the magic!
 *
 * Return: return nothing
*/

void __ginterf(void)
{
	int init;

	switch ((*__art)->interf)
	{
		case GNONE:
			break;	/* do nothing */

		case GCLI:
			init = tb_init();
			assert(init == 0);

			initscr();
			curs_set(1);
			raw();
			cbreak();

			/* enable special key input and scrolling effect */
			keypad(stdscr, TRUE);
			scrollok(stdscr, TRUE);

			refresh();

			__gpmtwin();	/* prompt window */

			break;

		case GGUI:
			/* scr->interf.gui = TODO */
			break;

		default:
			dprintf(STDERR_FILENO,
				"invalid interface: couldn't set up interface"
			);
			abort();
	}
}

/**
 * __gpmtwin - create a new window for prompt at the bottom of the stdscr
 *
 * Return: return nothing
*/

void __gpmtwin(void)
{
	int x, y;

	getmaxyx(stdscr, y, x);

	/* set the height of the prompt window to 1 */
	(*__art)->pmtwin = newwin(1, x, y - 1, 0);

	raw();
	cbreak();
	noecho();

	/* enable special key input */
	keypad((*__art)->pmtwin, TRUE);

	wattron((*__art)->pmtwin, GBOLD);

	wrefresh((*__art)->pmtwin);
}
