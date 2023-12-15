#include <stdio.h>
#include <stdlib.h>
#include <termbox.h>

#include "ecraft.h"

/**
 * __interrupt - interrupt handler that prompts for user input
 *
 * @screen: current terminal screen
 *
 * Return: return nothing
*/

void __interrupt(SCREEN *screen)
{
	char *line = malloc(sizeof(char) * 1024);
	ssize_t flag;

	__ec_printf(screen, "string", "\n");

	getstr(line);
	refresh();

	free(line);
}
