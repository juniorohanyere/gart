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
		case EC_NONE:
			break;
		case EC_CLI:
			if (__cli == EC_NONE)
			{
				tb_init();	/* TODO: manage init error */
				initscr();

				__cli = __EC_INIT;
			}
			ecraft->interf.cli = newterm(NULL, stdout, stdin);

			break;

		case EC_GUI:
			if (__gui == EC_NONE)
			{
				/* init gui */
				__gui = __EC_INIT;
			}
			break;	/* TODO */

		default:	/* invalid interface */
			assert(ecraft->craft->__interface == EC_NONE ||
				ecraft->craft->__interface == EC_CLI ||
				ecraft->craft->__interface == EC_GUI);

			return;	/* to avoid unexpected bug */
	}
}

/**
 * __stagecli - set command line interface
 *
 * @meta: meta information of a craft
 *
 * Return: return nothing
*/

/*void __stagecli(meta_t **meta)
{
	int i, emoji_size = 1, emoji_check;
	emoji_t emoji[] = {
		{"smile", "\U0001F600"}, {"angry", "\U0001F621"},
		{"crying-face", "\U0001F622"}, {"crying-cat", "\U0001F63F"},
		{"loudly-crying-face", "\U0001F62D"}, {NULL, NULL}
	};

	if ((*meta)->cast != NULL && (*meta)->cast->__dname != NULL)
		printf("%s: ", (*meta)->cast->__dname);*/	/* print in bold */

/*	while ((*meta)->emoji[emoji_size - 1] != NULL)
	{
		assert(emoji_size <= 3);

		for (i = 0; emoji[i].emoji != NULL; i++)
		{
			emoji_check = strcmp((*meta)->emoji[emoji_size - 1],
				emoji[i].emoji);
*/
			/* end of dictionary */
/*			if (emoji[i + 1].emoji == NULL && emoji_check != 0)
				assert(emoji_check == 0);
			else if (emoji_check == 0)
			{
				printf("%s", emoji[i].unicode);

				break;
			}
		}
		emoji_size++;
	}
	printf("\n");

	printf("%s\n", (*meta)->message);

	__interrupt();
}
*/
