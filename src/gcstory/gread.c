#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <termbox.h>

#include <gart.h>

/**
 * __gread - interrupt handler that prompts for user input
 *
 * @step: flag to set up number of lines to print before the interrupt
 *
 * Return: return nothing
*/

void __gread(int step)
{
	int i;
	int64_t offset, size;
	char *line = malloc(sizeof(char) * 1024);

	offset = __art->bottom;
	size = __art->vertice;

	mvwprintw(__art->pmtwin, 0, 0, "$ ");
	wrefresh(__art->pmtwin);

	if (offset == size)
	{
		free(line);

		return;
	}

	i = __gget(__art->pmtwin, line);

	werase(__art->pmtwin);

	if (i == - 1)
	{
		free(line);
		gfinal();
		exit(EXIT_SUCCESS);
	}

	__gexec(line);
	free(line);
	__gread(step);
}

/**
 * __key_up - handle key-up button press
 *
 * Return: return nothing
*/

void __key_up(void)
{
	int i = 0, x, y;
	int64_t offset;
	gbuffer_t **gbuffer = __art->gbuffer;

	if (__art->top < 0)
		return;

	x = getcurx(stdscr);
	y = getcury(stdscr);

	scrl(-1);
	refresh();

	offset = __art->top--;
	__art->bottom--;

	move(0, 0);
	attron(gbuffer[offset]->attrs);
	__gprint("s", gbuffer[offset]->string);
	attroff(gbuffer[offset]->attrs);
	__gprint("s", " ");

	while (gbuffer[offset]->unicode != NULL &&
		gbuffer[offset]->unicode[i] != NULL)
	{
		attron(gbuffer[offset]->attrs);
		__gemoji(gbuffer[offset]->unicode[i], i);
		attroff(gbuffer[offset]->attrs);
		move(0, getcurx(stdscr) + 2);
		refresh();
		i++;
	}
	werase(__art->pmtwin);
	mvwprintw(__art->pmtwin, 0, 0, "$ ");
	wrefresh(__art->pmtwin);

	if (gbuffer[offset]->tts == GINIT)
		__gtts(gbuffer[offset]->string);
	move(y, x);
}
