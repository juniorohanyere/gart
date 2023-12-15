#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ecraft.h"

cast_t *c_cstory(ecraft_t *cstory, char *dname, char *fname, char *lname,
	char *altnames)
{
	cast_t *cast;
	cast = calloc(sizeof(cast_t), 1);
	if (cast == NULL)
		return (NULL);

	cast->__dname = strdup(dname);
	cast->__fname = strdup(fname);
	cast->__lname = strdup(lname);
	cast->__altnames = strdup(altnames);

	if (cast->__dname == NULL || cast->__fname == NULL ||
		cast->__lname == NULL || cast->__altnames == NULL)
	{
		free(cast);

		return (NULL);
	}

	__c_add_cstory(cstory, cast);

	return (cast);
}

int s_cstory(ecraft_t *cstory, cast_t *cast, char *message, char *emoji)
{
	int i, j;
	char *emoji_dup;

	if (message == NULL)
		message = "";

	if (emoji == NULL)
		emoji = "";

	if (cstory == NULL)
	{
		/* __null_cstory(cstory, cast, message, emoji); */

		return (-1);
	}

	for (i = 0; __ecraft[i] != NULL; i++)
	{
		if (__ecraft[i] == cstory)
		{
			emoji_dup = strdup(emoji);
			__ecraft[i]->__meta = __m_add_cstory(
				__ecraft[i]->__meta, cast, message, emoji_dup);

			for (j = 0; __ecraft[i]->__meta[j] != NULL; j++)
				;

			__s_cstory(cstory, __ecraft[i]->__meta[j - 1]);

			free(emoji_dup);

			return (j - 1);
		}
	}
}

void __s_cstory(ecraft_t *cstory, meta_t *meta)
{
	switch (cstory->__interface)
	{
		case EC_CLI:
			__s_cli_cstory(cstory, meta);

			break;

		case EC_GUI:
			break;	/* TODO */

		default:	/* EC_NONE */
			return;
	}
}

void __s_cli_cstory(ecraft_t *cstory, meta_t *meta)
{
	int i, emoji_size = 1, emoji_check, x, y;
	emoji_t *emoji = __emoji_list();
	SCREEN *cli = cstory->__interf.cli;

	/* display name should be printed in bold */
	if (meta->cast != NULL && meta->cast->__dname != NULL)
	{
		attron(A_BOLD);
		__ec_printf(cli, "string", meta->cast->__dname);
		__ec_printf(cli, "string", ": "), attroff(A_BOLD);
	}

	while (meta->emoji != NULL && meta->emoji[emoji_size - 1] != NULL)
	{
		assert(emoji_size <= 3);
		for (i = 0; emoji[i].rep != NULL; i++)
		{
			emoji_check = strcmp(meta->emoji[emoji_size - 1],
				emoji[i].rep);
//			printf("%s->%s\n", meta->emoji[emoji_size - 1], emoji[i].rep);
			/* end of dictionary, yet couldn't validate emoji */
			if (emoji[i + 1].rep == NULL && emoji_check != 0)
			{
				//assert(emoji_check == 0);
			}
			else if (emoji_check == 0)
			{
				if (meta->cast == NULL)
					break;

				attron(A_BOLD);
				__ec_printf(cli, "emoji", emoji[i].unicode);
				__ec_printf(cli, "string", "  ");
				attroff(A_BOLD);

				break;
			}
		}
		emoji_size++;
	}
	__ec_printf(cli, "string", "\n");
	__ec_printf(cli, "string", meta->message);
	__interrupt(cli);
}
