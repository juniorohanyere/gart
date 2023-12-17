#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ecraft.h"


/**
 * ec_cstory - ecraft_cstory => initialises a new chat-story
 *
 * @title: title of the chat-story
 * @subtitle: subtitle of the chat-story
 * @interface: interface to use (cli, gui, or none)
 *
 * Description: @title and @subtitle can be set to NULL
 *
 * Return: return a pointer to the new chat-story
*/

ecraft_t *ec_cstory(char *title, char *subtitle, char *description,
	int interface)
{
	int i = 0, ec_size, size = 4;
	char *type = "ec_cstory";

	/* validate interface */
	assert(interface == EC_NONE || interface == EC_CLI ||
		interface == EC_GUI);

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
	__ecraft[i]->__description = strdup(description);
	__ecraft[i]->__type = strdup(type);

	__set_interf(__ecraft[i]);

	__ecraft[i]->__cast = NULL;
	__ecraft[i]->__meta = NULL;

	return (__ecraft[i]);
}

/**
 * c_cstory - cast_cstory => creates a new cast for a chat-story
 *
 * @cstory: pointer to the head of the chat-story to add the new cast
 * @dname: display name
 * @fname: first name
 * @lname: last name
 * @altnames: alternate names
 *
 * Description: recommended that @fname and @lname be a single word name
 *		@dname and @altnames can contain more than one names
 *
 * Return: return a pointer to the newly created cast
*/

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

/**
 * s_cstory - stage_cstory => stages a chat-story for display providing a
 *	      message and the cast responsible for the message
 *
 * @cstory: pointer to the head of the chat-story
 * @cast: pointer to the cast responsible for the message to display
 * @message: message to display
 * @emoji: state of the @cast at the moment
 *
 * Return: return the index position of the stage within @cstory->meta
*/

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

			if (j - 1 == 0)
			{
				attron(A_BOLD);
				__ec_printf(__ecraft[i]->__interf.cli,
					"string", "Title:		");
				attroff(A_BOLD);
				__ec_printf(__ecraft[i]->__interf.cli,
					"string", __ecraft[i]->__title);
				__ec_printf(__ecraft[i]->__interf.cli,
					"string", "\n");

				attron(A_BOLD);
				__ec_printf(__ecraft[i]->__interf.cli,
					"string", "Subtitle:	");
				attroff(A_BOLD);

				__ec_printf(__ecraft[i]->__interf.cli,
					"string", __ecraft[i]->__subtitle);
				__ec_printf(__ecraft[i]->__interf.cli,
					"string", "\n");

				attron(A_BOLD);
				__ec_printf(__ecraft[i]->__interf.cli,
					"string", "Description:	");
				attroff(A_BOLD);

				__ec_printf(__ecraft[i]->__interf.cli,
					"string", __ecraft[i]->__description);
				__ec_printf(__ecraft[i]->__interf.cli,
					"string", "\n\n");
			}

			__s_cstory(cstory, __ecraft[i]->__meta[j - 1]);

			free(emoji_dup);

			return (j - 1);
		}
	}
	return (-1);
}

/**
 * __s_cstory - stage_cstory => stages a cstory for display
 *
 * @cstory: the chat-story to be staged for display
 * @meta: pointer to the meta data for @cstory
 *
 * Return: return nothing
*/

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

/**
 * __s_cli_cstory - stage_cli_cstory => stages a cstory to the command line
 *		    interface
 *
 * @cstory: pointer to the chat-story to stage for display
 * @meta: pointer to meta data for @cstory
 *
 * Return: return nothing
*/

void __s_cli_cstory(ecraft_t *cstory, meta_t *meta)
{
	int i, emoji_size = 1, emoji_check, y;
	emoji_t *emoji = __emoji_list();
	SCREEN *cli = cstory->__interf.cli;

	y = getcury(stdscr);
	if (y == getmaxy(stdscr) - 2)
	{
		scrl(2);
		refresh();
		doupdate();
	}

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
			/* end of dictionary, yet couldn't validate emoji */
			if (emoji[i + 1].rep == NULL && emoji_check != 0)
				assert(emoji_check == 0);
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
