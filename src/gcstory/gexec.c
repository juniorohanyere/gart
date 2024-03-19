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
	int64_t index = (*__art)->index, offset = __art[index]->bottom;
	char *str = "", *string = __art[index]->scr[offset]->string;
	char **unicode = __art[index]->scr[offset]->unicode;

	if (cmd == NULL || strcmp(cmd, str) == 0)
	{
		attron(__art[index]->scr[offset]->attrs);
		__gprint("s", string);
		attroff(__art[index]->scr[offset]->attrs);
		__gprint("s", " ");

		while (unicode != NULL && unicode[i] != NULL)
		{
			attron(__art[index]->scr[offset]->attrs);
			__gemoji(unicode[i], i);
			attroff(__art[index]->scr[offset]->attrs);
			move(getcury(stdscr), getcurx(stdscr) + 2);
			i++;
		}
		mvwprintw((*__art)->pmtwin, 0, 0, "$ ");
		wrefresh((*__art)->pmtwin);
		if (__art[index]->scr[offset]->tts == GINIT)
			__gtts(string);
		move(getcury(stdscr) + 1, 0);

		offset = ++__art[index]->bottom;

		if (__art[index]->scr[offset] != NULL &&
			__art[index]->scr[offset]->ref == -1 &&
			getcury(stdscr) < getmaxy(stdscr) - 2)
			__gexec(str);
	}
}
