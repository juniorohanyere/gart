#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ecraft.h"

/**
 * stage - sends data to the interface referenced by a given craft
 *
 * @craft: pointer to the craft to reference
 * @cast: pointer to the cast in which the data to send is meant for
 * @message: the data/string to send
 * @emoji: the state of the @cast at the moment of sending the data
 *
 * Return: return an integral position of the message to echo from
 *	   __ecraft->meta
*/

int stage(craft_t *craft, char *message, char *emoji, cast_t *cast)
{
	int i;
	char *emoji_dup;
	meta_t **meta = NULL;
	ecraft_t *ecraft;

	if (message == NULL)
		message = "";

	if (emoji == NULL)
		emoji = "";

	if (craft == NULL)
	{
		/* __nullcraft(cast, buffer, emoji); */
	}
	else
	{
		ecraft = __ecraft;

		while (ecraft != NULL)
		{
			if (ecraft->craft == craft)
			{
				emoji_dup = strdup(emoji);
				meta = __addmeta(meta, cast, message, emoji_dup);
				ecraft->meta = __addmeta(ecraft->meta, cast,
					message, emoji_dup);

				__stage(ecraft, meta);

				for (i = 0; ecraft->meta[i] != NULL; i++)
					;
				free((*meta)->message);
				free((*meta)->emoji);
				free(*meta);
				free(meta);

				free(emoji_dup);

				return (i - 1);
			}
			ecraft = ecraft->next;
		}
	}
}

void __stage(ecraft_t *ecraft, meta_t **meta)
{
	switch (ecraft->craft->__interface)
	{
		case EC_CLI:
			__stagecli(ecraft, meta);

			break;

		case EC_GUI:
			break;	/* TODO */

		default:	/* EC_NONE */
			return;
	}
}

void __stagecli(ecraft_t *ecraft, meta_t **meta)
{
	int i, emoji_size = 1, emoji_check, x, y;
	emoji_t emoji[] = {
		{"grinning-face", "0x1F600", "[grinning face]"},
		{"crying-face", "0x1F622", "[crying face]"},
		{NULL, NULL, NULL},
	};
	craft_t *craft = ecraft->craft;
	SCREEN *cli = ecraft->interf.cli;

	/* display name should be printed in bold */
	if ((*meta)->cast != NULL && (*meta)->cast->__dname != NULL)
	{
		__ecprintf(cli, "string", (*meta)->cast->__dname);
		__ecprintf(cli, "string", ": ");
	}

	while ((*meta)->emoji != NULL &&
		(*meta)->emoji[emoji_size - 1] != NULL)
	{
		assert(emoji_size <= 3);

		for (i = 0; emoji[i].rep != NULL; i++)
		{
			emoji_check = strcmp((*meta)->emoji[emoji_size - 1],
				emoji[i].rep);
			/* end of dictionary yet coudn't validate emoji */
			if (emoji[i + 1].rep == NULL && emoji_check != 0)
				assert(emoji_check == 0);
			else if (emoji_check == 0)
			{
				if ((*meta)->cast == NULL)
					break;

				__ecprintf(cli, "emoji", emoji[i].unicode);
				__ecprintf(cli, "string", "  ");

				break;
			}
		}
		emoji_size++;
	}
	__ecprintf(cli, "string", "\n");
	__ecprintf(cli, "string", (*meta)->message);
	__interrupt(cli);
}
