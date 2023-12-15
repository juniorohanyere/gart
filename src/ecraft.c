#include <stdlib.h>
#include <string.h>
#include <term.h>
#include <termbox.h>

#include "ecraft.h"

__ECRAFT;

__EC_CLI;
__EC_GUI;

ecraft_t *ec_cstory(char *title, char *subtitle, int interface)
{
	int i = 0, ec_size, size = 4;

	if (__ecraft == NULL)
	{
		ec_size = size * (2 * i + 3);

		__ecraft = calloc(sizeof(ecraft_t *), ec_size);
		if (__ecraft == NULL)
			return (NULL);
	}

	for (i = 0; __ecraft[i] != NULL; i++)
		;

	ec_size = size * (2 * i + 3);

	__ecraft = realloc(__ecraft, sizeof(ecraft_t *) * ec_size);
	if (__ecraft == NULL)
		return (NULL);

	__ecraft[i] = calloc(sizeof(ecraft_t), 1);
	if (__ecraft[i] == NULL)
		return (NULL);

	__ecraft[i]->__interface = interface;
	__ecraft[i]->__title = strdup(title);
	__ecraft[i]->__subtitle = strdup(subtitle);
	__ecraft[i]->__type = strdup("ec_cstory");
	__set_interf(__ecraft[i]);
	__ecraft[i]->__cast = NULL;
	__ecraft[i]->__meta = NULL;

	return (__ecraft[i]);
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
	int i = 0, interface;

	if (__ecraft == NULL)
		return;

	while (__ecraft[i] != NULL)
	{
		interface = __ecraft[i]->__interface;

		__freecraft(__ecraft[i]);
		__c_del_cstory(__ecraft[i]->__cast);
		__m_del_cstory(__ecraft[i]->__meta);
		if (interface == EC_CLI)
			delscreen(__ecraft[i]->__interf.cli);
		else if (interface == EC_GUI)
		{
			/* delete gui window */
		}
		free(__ecraft[i]);
		i++;
	}
	free(__ecraft);
	if (__cli == EC_CLI)
	{
		endwin(), del_curterm(cur_term);
		delwin(stdscr), delwin(curscr), delwin(newscr);
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
	__cli = __EC_INIT, __gui = __EC_INIT;
}

void __freecraft(ecraft_t *craft)
{
	if (craft == NULL)
		return;

	free(craft->__title);
	free(craft->__subtitle);
	free(craft->__type);
}
