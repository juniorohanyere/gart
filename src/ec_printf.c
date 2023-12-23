#include <stdlib.h>
#include <string.h>
#include <termbox.h>
#include <assert.h>

#include <ecraft.h>

/**
 * __ec_printf - prints a string, or emoji to the stdscr of the current
 *		terminal screen
 *
 * @type: type include string, emoji
 *
 * @str: the content to print/display on @screen
 *
 * Return: return nothing
*/

void __ec_printf(const char *type, char *str)
{
	int x, y;
	uint32_t ch;
	char *s;

	if (__ec->interf != EC_CLI)	/* TODO to be amended */
		return;

	set_term(__ec->screen.cli);

	x = getcurx(stdscr);
	y = getcury(stdscr);

	if (y == getmaxy(stdscr))
	{
		/*
		 * manual management of scrolling might resolve the glitch with
		 * printing emoji
		*/
		scroll(stdscr);
		refresh();
	}

	if (strcmp(type, "string") == 0)
	{
		printw("%s", str);
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
