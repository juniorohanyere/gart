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
		curs_set(1);
		ch = wgetch(win);
		switch (ch)
		{
			case '\n':
				curs_set(0);

				return (i);
			case '\b':
				i = __bkspace(win, buffer, ch, i);
				wrefresh(win);
				break;

			case 4:	/* end of file condition (CTRL + D) */
				if (getcurx(win) == 2)
				{
					curs_set(0);

					return (-1);
				}

				i--;
				break;

			case KEY_UP:
				__key_up();
				break;

			default:
				wprintw(win, "%s", (char *)&ch);
				wrefresh(win);

				strcat(buffer, (char *)&ch);
				i++;
				break;
		}
	}
	curs_set(0);

	return (i);
}

/**
 * __bkspace - handles backspace character
 *
 * @win: the window screen to handle the character from
 * @buffer: the buffer to manipulate based on the backspace character
 * @ch: the character
 * @length: the length of the @buffer
 *
 * Return: return the new length of @buffer
*/

int __bkspace(WINDOW *win, char *buffer, int ch, int length)
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

	return (length);
}

/**
 * __ec_signal - handles the signint signal
 *
 * @signal: the signal to handle
 *
 * Return: return nothing
*/

void __ec_signal(int __attribute__((unused))signal)
{
	/* dummy */
}
