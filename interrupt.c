#include <stdio.h>
#include <stdlib.h>
#include <termbox.h>

#include "ecraft.h"

/**
 * __interrupt - interrupt handler that prompts for user input
 *
 * Return: return nothing
*/

void __interrupt(SCREEN *screen)
{
	char *line = malloc(sizeof(char) * 1024);
	size_t n = 1024;
	ssize_t flag;

	__ecprintf(screen, "string", "\n$ ");

	getstr(line);
	refresh();
	endwin();
	delscreen(screen);
	tb_shutdown();
	exit(0);
//	flag = getline(&line, &n, stdin);
//	if (flag == -1)
//	{
//		exit(EXIT_SUCCESS);
//	}

//	free(line);
}
