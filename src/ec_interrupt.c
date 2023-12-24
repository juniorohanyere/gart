#include <stdio.h>
#include <stdlib.h>
#include <termbox.h>

#include <ecraft.h>

/**
 * __ec_interrupt - interrupt handler that prompts for user input
 *
 * @screen: current terminal screen
 * @tts_msg: the text to convert to speech if tts is enabled
 *
 * Return: return nothing
*/

void __ec_interrupt(char *tts_msg)
{
	char *line = malloc(sizeof(char) * 1024);

	wattron(__ec->pmtscr, A_BOLD);
	mvwprintw(__ec->pmtscr, 0, 0, "$ ");
	wattroff(__ec->pmtscr, A_BOLD);
	wrefresh(__ec->pmtscr);

	__ec_tts(tts_msg);

	wgetstr(__ec->pmtscr, line);
	werase(__ec->pmtscr);

	free(line);
}
