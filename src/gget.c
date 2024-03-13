#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <gart.h>

/**
 * __gget - get keyboard input and store it in a buffer passed as a parameter
 *
 * @win: the window to accept input from
 * @buffer: the variable to store the keyboard input
 *
 * Return: return the number of characters read on success
*/

int __gget(WINDOW *win, char *buffer)
{
	int ch, i = 0;
	char *str = "";

	strcpy(buffer, str);
	signal(SIGINT, __gsignal);

	while (1)
	{
		ch = wgetch(win);
		switch (ch)
		{
			case '\n':
				return (i);
			case '\b':
				i = __bkspace(win, buffer, ch, i);
				wrefresh(win);
				break;
			case 4:	/* end of file condition (CTRL + D) */
				if (getcurx(win) == 2)
					return (-1);
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
 * __bkspace - handle backspace character
 *
 * @win: pointer to the window object to handle the character from
 * @buffer: the buffer to manipulate based on the backspace character
 * @ch: the character
 * @length: the length of the @buffer
 *
 * Return: return the new length of @buffer after manipulation
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
 * __gsignal - handle the sigint signal
 *
 * @signal: the signal to handle
 *
 * Return: return nothing
*/

void __gsignal(int __attribute__((unused))signal)
{
	/* dummy */
}
