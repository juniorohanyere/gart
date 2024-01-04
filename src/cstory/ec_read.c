#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <termbox.h>

#include <ecraft.h>

/**
 * __ec_read - interrupt handler that prompts for user input
 *
 * @tts_msg: the text to convert to speech if tts is enabled
 *
 * Return: return nothing
*/

void __ec_read(int __attribute__((unused))step)
{
	int i;
	int64_t offset, size;
	char *line = malloc(sizeof(char) * 1024);

	offset = __ec->bottom;
	size = __ec->ec_size;

	mvwprintw(__ec->pmtscr, 0, 0, "$ ");
	wrefresh(__ec->pmtscr);

	if (offset == size)
	{
		free(line);

		return;
	}

	i = __ec_get(__ec->pmtscr, line);

	werase(__ec->pmtscr);

	if (i == -1)
	{
		free(line);
		ec_final();
		exit(EXIT_SUCCESS);
	}

	__ec_exec(line);
	free(line);
	__ec_read(step);

}
