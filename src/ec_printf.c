#include <stdlib.h>
#include <string.h>
#include <termbox.h>
#include <assert.h>

#include "ecraft.h"

/**
 * __ec_printf - prints a string, or emoji to the stdscr of the current
 *		terminal screen
 *
 * @screen: the current terminal screen
 * @type: type include string, emoji
 *
 * @str: the content to print/display on @screen
 *
 * Return: return nothing
*/

void __ec_printf(SCREEN *screen, const char *type, char *str)
{
	int x, y;
	uint32_t ch;
	char *s;

	set_term(screen);

	x = getcurx(stdscr);
	y = getcury(stdscr);

	if (strcmp(type, "string") == 0)
	{
		printw(str);
		tb_present();
		refresh();	/* force characters to output -> fflush */
	}
	else if (strcmp(type, "emoji") == 0)
	{
		ch = strtoul(str, &s, 16);
		assert(*s == '\0');

		tb_change_cell(x, y, ch, TB_WHITE, TB_DEFAULT);
		tb_present();
	}
}
