#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <ecraft.h>

/**
 * __ec_get - gets keyboard input and stores it in a buffer passed as a
 *		 parameter
 *
 * @win: the window to accept input from
 * @buffer: the variable to store the keyboard input
 *
 * Return: return the number of characters read on success
*/

int __ec_get(WINDOW *win, char *buffer)
{
	int ch, i = 0;
	char *str = "";

	strcpy(buffer, str);
	signal(SIGINT, __ec_signal);

	while (1)
	{
		ch = wgetch(win);
		switch (ch)
		{
			case '\n':
				return (i);
			case '\b':
				__bkspace(win, buffer, ch, i);

				break;

			case 4:	/* end of file condition (CTRL + D) */
				if (getcurx(win) == 2)
					return (-1);

				i--;

				break;

			default:
				wprintw(win, "%s", (char *)&ch);
				wrefresh(win);

				strcat(buffer, (char *)&ch);
				i++;

				break;
		}
	}

	return (i);
}

void __bkspace(WINDOW *win, char *buffer, int ch, int length)
{
	wprintw(win, "%s", (char *)&ch);
	if (getcurx(win) == 1)
		wmove(win, getcury(win), getcurx(win) + 1);
	else
	{
		wclrtoeol(win);
		length--;
		buffer[length] = '\0';
	}
	wrefresh(win);
}

void __ec_signal(int __attribute__((unused))signal)
{
	int i;

	for (i = 0; __ec->ecraft[i] != NULL; i++)
		;

	//__cs_scrolldown();
	scrl(-1);
}
