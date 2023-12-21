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

void __interrupt(SCREEN *screen, char *tts_msg)
{
	char *line = malloc(sizeof(char) * 1024);

	__ec_printf(screen, "string", "\n");

	wattron(__ec->pmtscr, A_BOLD);
	mvwprintw(__ec->pmtscr, 0, 0, "$ ");
	wattroff(__ec->pmtscr, A_BOLD);
	wrefresh(__ec->pmtscr);

	__ec_tts(tts_msg);

	wgetstr(__ec->pmtscr, line);
	werase(__ec->pmtscr);

	free(line);
}
