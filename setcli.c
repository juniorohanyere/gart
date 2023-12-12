#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ecraft.h"

/**
 * __setcli - set command line interface
 *
 * @meta: meta information of a craft
 *
 * Return: return nothing
*/

void __setcli(meta_t **meta)
{
	int i, emoji_size = 1, emoji_check;
	emoji_t emoji[] = {
		{"smile", "\U0001F600"}, {"angry", "\U0001F621"},
		{"crying-face", "\U0001F622"}, {"crying-cat", "\U0001F63F"},
		{"loudly-crying-face", "\U0001F62D"}, {NULL, NULL}
	};

	if ((*meta)->cast != NULL && (*meta)->cast->__dname != NULL)
		printf("%s: ", (*meta)->cast->__dname);	/* print in bold */

	while ((*meta)->emoji[emoji_size - 1] != NULL)
	{
		assert(emoji_size <= 3);

		for (i = 0; emoji[i].emoji != NULL; i++)
		{
			emoji_check = strcmp((*meta)->emoji[emoji_size - 1],
				emoji[i].emoji);

			/* end of dictionary */
			if (emoji[i + 1].emoji == NULL && emoji_check != 0)
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
