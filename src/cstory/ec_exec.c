#include <stdlib.h>
#include <string.h>

#include <ecraft.h>

void __ec_exec(char *cmd)
{
	int i = 0;
	int64_t offset = __ec->bottom;
	char *str = "", *string = __ec->ecraft[offset]->string;
	char **unicode = __ec->ecraft[offset]->unicode;

	if (cmd == NULL || strcmp(cmd, str) == 0)
	{
		attron(__ec->ecraft[offset]->attrs);
		__ec_print("s", string);
		attroff(__ec->ecraft[offset]->attrs);
		__ec_print("s", " ");

		while (unicode != NULL && unicode[i] != NULL)
		{
			attron(__ec->ecraft[offset]->attrs);
			__ec_emoji(unicode[i], i);
			attroff(__ec->ecraft[offset]->attrs);
			move(getcury(stdscr), getcurx(stdscr) + 2);
			i++;
		}
		mvwprintw(__ec->pmtscr, 0, 0, "$ ");
		wrefresh(__ec->pmtscr);
		if (__ec->ecraft[offset]->tts == EC_INIT)
			__ec_tts(string);
		move(getcury(stdscr) + 1, 0);
		__ec->bottom++;

		offset = __ec->bottom;

		if (__ec->ecraft[offset] != NULL &&
			__ec->ecraft[offset]->ref == -1)
			__ec_exec(str);
	}
}
