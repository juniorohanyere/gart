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
	int flag;
	int64_t i = (*__art)->index, offset, size;
	char *line = malloc(sizeof(char) * 1024);

	offset = __art[i]->bottom;
	size = __art[i]->vertice;

	mvwprintw((*__art)->pmtwin, 0, 0, "$ ");
	wrefresh((*__art)->pmtwin);

	if (offset == size)
	{
		free(line);

		return;
	}

	flag = __gget((*__art)->pmtwin, line);

	werase((*__art)->pmtwin);

	if (flag == - 1)
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
	int64_t index = (*__art)->index, offset;
	gbuffer_t **gbuffer = __art[index]->gbuffer;

	if (__art[index]->top < 0)
		return;

	x = getcurx(stdscr);
	y = getcury(stdscr);

	scrl(-1);
	refresh();

	offset = __art[index]->top--;
	__art[index]->bottom--;

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
	werase((*__art)->pmtwin);
	mvwprintw((*__art)->pmtwin, 0, 0, "$ ");
	wrefresh((*__art)->pmtwin);

	if (gbuffer[offset]->tts == GINIT)
		__gtts(gbuffer[offset]->string);
	move(y, x);
}
