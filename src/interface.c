#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <termbox.h>

#include "ecraft.h"

/**
 * __set_interf - sets the interface for a given craft
 *
 * @interface: the interface to set
 *
 * Return: return a pointer to the newly created interface as a union
*/

void __set_interf(ecraft_t *craft)
{
	switch (craft->__interface)
	{
		case EC_CLI:
			if (__cli == __EC_INIT)
			{
				tb_init();	/* TODO: manage init error */
				initscr();

				__cli = EC_CLI;

				cbreak();
				/* enable special key input */
				keypad(stdscr, TRUE);
				/* enable colours */
				refresh();
			}
			craft->__interf.cli = newterm(NULL, stdout, stdin);

			break;

		case EC_GUI:
			if (__gui == __EC_INIT)
			{
				/* init gui */
				__gui = EC_GUI;
			}
			/* ecraft->interf.gui = TODO */

			break;

		default:	/* EC_NONE */
			return;	/* do nothing */
	}
}
