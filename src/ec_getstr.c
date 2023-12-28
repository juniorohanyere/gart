#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ecraft.h>

/**
 * __ec_keymap - maps some special key inputs to a specific function to execute
 *
 * Return: return a pointer to a key mapper
*/

keymap_t *__ec_keymap(void)
{
	static keymap_t keymap[] = {
		{'\n', __ec_nl}, {ERR, NULL}
	};

	return (keymap);
}

/**
 * __ec_getstr - gets keyboard input and stores it in a buffer passed as a
 *		 parameter
 *
 * @win: the window to accept input from
 * @buffer: the variable to store the keyboard input
 *
 * Return: return the number of characters read on success
*/

int __ec_getstr(WINDOW *win, char *buffer)
{
	int ch, i, j, length = 0;
	keymap_t *keymap = __ec_keymap();

	noecho();

	while (1)
	{
		ch = wgetch(win);

		for (i = 0; keymap[i].key != ERR; i++)
		{
			if (ch == keymap[i].key)
			{
				j = keymap[i].func(buffer);
				if (j == -1)	/* end of file condition */
				{
					ec_final();
					exit(EXIT_SUCCESS);
				}

				return (length);
			}
		}
		wprintw(win, "%s", (char *)&ch);

		strcat(buffer, (char *)&ch);
		length++;
	}

	return (length);
}

/**
 * __ec_nl - handles enter key input (new line)
 *
 * @buffer: variable to store key input
 *
 * Return: always return 0
*/

int __ec_nl(char __attribute__((unused))*buffer)
{
	return (0);
}
