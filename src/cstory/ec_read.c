#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <termbox.h>

#include <ecraft.h>

/**
 * __ec_read - interrupt handler that prompts for user input
 *
 * @step: flag to set up number of lines to print before accepting input
 *
 * Return: return nothing
*/

void __ec_read(int step)
{
	int flag;
	int64_t i = (*__ec)->index, offset, size;
	char *line = malloc(sizeof(char) * 1024);

	offset = __ec[i]->bottom;
	size = __ec[i]->ec_size;

	mvwprintw((*__ec)->pmtscr, 0, 0, "$ ");
	wrefresh((*__ec)->pmtscr);

	if (offset == size)
	{
		free(line);

		return;
	}

	flag = __ec_get((*__ec)->pmtscr, line);

	werase((*__ec)->pmtscr);

	if (flag == -1)
	{
		free(line);
		decraft();
		exit(EXIT_SUCCESS);
	}

	__ec_exec(line);
	free(line);
	__ec_read(step);

}

/**
 * __key_up - handles key-up button press
 *
 * Return: return nothing
*/

void __key_up(void)
{
	int i = 0, x, y;
	int64_t index = (*__ec)->index, offset;
	ecraft_t **ecraft = __ec[index]->ecraft;

	if (__ec[index]->top < 0)
		return;

	x = getcurx(stdscr);
	y = getcury(stdscr);

	scrl(-1);
	refresh();

	offset = __ec[index]->top--;
	__ec[index]->bottom--;

	move(0, 0);
	attron(ecraft[offset]->attrs);
	__ec_print("s", ecraft[offset]->string);
	attroff(ecraft[offset]->attrs);
	__ec_print("s", " ");

	while (ecraft[offset]->unicode != NULL &&
		ecraft[offset]->unicode[i] != NULL)
	{
		attron(ecraft[offset]->attrs);
		__ec_emoji(ecraft[offset]->unicode[i], i);
		attroff(ecraft[offset]->attrs);
		move(0, getcurx(stdscr) + 2);
		refresh();
		i++;
	}
	werase((*__ec)->pmtscr);
	mvwprintw((*__ec)->pmtscr, 0, 0, "$ ");
	wrefresh((*__ec)->pmtscr);

	if (ecraft[offset]->tts == EC_INIT)
		__ec_tts(ecraft[offset]->string);
	move(y, x);
}
