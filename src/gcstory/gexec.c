#include <stdlib.h>
#include <string.h>

#include <gart.h>

/**
 * __gexec - run a function based on the value of the passed parameter
 *
 * @cmd: command
 *
 * Return: return nothing
*/

void __gexec(char *cmd)
{
	int i = 0;
	int64_t offset = __art->bottom;
	char *str = "", *string = __art->gbuffer[offset]->string;
	char **unicode = __art->gbuffer[offset]->unicode;

	if (cmd == NULL || strcmp(cmd, str) == 0)
	{
		attron(__art->gbuffer[offset]->attrs);
		__gprint("s", string);
		attroff(__art->gbuffer[offset]->attrs);
		__gprint("s", " ");

		while (unicode != NULL && unicode[i] != NULL)
		{
			attron(__art->gbuffer[offset]->attrs);
			__gemoji(unicode[i], i);
			attroff(__art->gbuffer[offset]->attrs);
			move(getcury(stdscr), getcurx(stdscr) + 2);
			i++;
		}
		mvwprintw(__art->pmtwin, 0, 0, "$ ");
		wrefresh(__art->pmtwin);
		if (__art->gbuffer[offset]->tts == GINIT)
			__gtts(string);
		move(getcury(stdscr) + 1, 0);

		offset = ++__art->bottom;

		if (__art->gbuffer[offset] != NULL &&
			getcury(stdscr) < getmaxy(stdscr) - 2)
			__gexec(str);
	}
}
