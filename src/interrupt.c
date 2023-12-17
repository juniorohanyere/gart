#include <stdio.h>
#include <stdlib.h>
#include <termbox.h>

#include "ecraft.h"

/**
 * __interrupt - interrupt handler that prompts for user input
 *
 * @screen: current terminal screen
 *
 * Return: return nothing
*/

void __interrupt(SCREEN *screen)
{
	char *line = malloc(sizeof(char) * 1024);

	__ec_printf(screen, "string", "\n\n");

	wattron(__pmtscr, A_BOLD);
	mvwprintw(__pmtscr, 0, 0, "$ ");
	wattroff(__pmtscr, A_BOLD);
	wrefresh(__pmtscr);

	wgetstr(__pmtscr, line);
	werase(__pmtscr);

	free(line);
}
