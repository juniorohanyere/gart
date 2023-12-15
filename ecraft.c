#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <term.h>
#include <termbox.h>

#include "ecraft.h"

/* by-pass betty error for use of global variables */
__ECRAFT;
__CAST;

__EC_CLI;
__EC_GUI;

__EC_SIZE;

/**
 * __addcraft - updates __ecraft
 *
 * @ecraft: pointer to a new placeholder to be used as update for __ecraft
 *
 * Return: return nothing
*/

void __addcraft(ecraft_t *ecraft)
{
	int size = 4;
	ecraft_t *temp;

	if (__ecraft == NULL)
		__ecraft = ecraft;
	else
	{
		temp = __ecraft;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = ecraft;
	}
}

/**
 * freecraft - clean-up
 *	       this function must be called at the end of the user's program
 *	       in order to clean up or free all allocated blocks of  memory
 *
 * Return: return nothing
*/

void freecraft(void)
{
	int i, interface;
	ecraft_t *ecraft = __ecraft, *next;

	if (__ecraft == NULL)
		return;

	while (ecraft != NULL)
	{
		next = ecraft->next;
		interface = ecraft->craft->__interface;

		endcraft(ecraft->craft);
		__delmeta(ecraft->meta);

		if (interface == EC_CLI)
			delscreen(ecraft->interf.cli);

		else if (interface == EC_GUI)
		{
			/* delete gui window */
		}


		free(ecraft);

		ecraft = next;
	}

	__freecast();

	if (__cli == EC_CLI)
	{
		endwin();
		del_curterm(cur_term);
		delwin(stdscr);
		delwin(curscr);
		delwin(newscr);
		/*
		 * this is by far the best clean up for ncurses I know of
		 * any help on improving or making the ncurses clean up perfect
		 * is highly appreciated
		*/

		tb_shutdown();
	}

	if (__gui == EC_GUI)
	{
		/* end gui */
	}

	__cli = __EC_INIT;
	__gui = __EC_INIT;
}
