#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <termbox.h>

#include <gart.h>

/**
 * __gprint - print a string, or emoji to the stdscr
 *
 * @type: type include: 's' for string
 *			 'u' for emoji
 * @str: the string to print to the stdscr
 *
 * Return: return nothing
*/

void __gprint(const char *type, char *str)
{
	int x, y;
	uint32_t ch;
	char *s;

	if (__art->interf != GCLI)	/* TODO to be amended */
		return;

	x = getcurx(stdscr);
	y = getcury(stdscr);

	if (y == getmaxy(stdscr) - 1)
	{
		scrl(1);
		refresh();
		__art->top++;
		move(getcury(stdscr) - 1, 0);
	}

	if (strcmp(type, "s") == 0)
	{
		printw("%s", str);
		refresh();	/* force characters to output -> fflush */
	}

	else if (strcmp(type, "u") == 0)
	{
		ch = strtoul(str, &s, 16);
		assert(*s == '\0');

		tb_change_cell(x, y, ch, TB_WHITE, TB_DEFAULT);
		tb_change_cell(x + 1, y, 0x00000, TB_WHITE, TB_DEFAULT);
		tb_change_cell(x + 2, y, 0x00000, TB_WHITE, TB_DEFAULT);
		tb_change_cell(x + 3, y, 0x00000, TB_WHITE, TB_DEFAULT);
		tb_change_cell(x + 4, y, 0x00000, TB_WHITE, TB_DEFAULT);
		tb_present();
	}
}
