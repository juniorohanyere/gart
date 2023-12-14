#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <termbox.h>

#include "ecraft.h"

/**
 * __setinterf - sets the interface for a given craft
 *
 * @craft: the given craft
 * @meta: the meta information for the given craft
 *
 * Return: return nothing
*/

void __setinterf(ecraft_t *ecraft)
{
	switch (ecraft->craft->__interface)
	{
		case EC_CLI:
			if (__cli == __EC_INIT)
			{
				tb_init();	/* TODO: manage init error */
				initscr();

				__cli = EC_CLI;
			}
			ecraft->interf.cli = newterm(NULL, stdout, stdin);

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
