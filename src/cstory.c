#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <ecraft.h>


/**
 * ec_cstory - ecraft_cstory => initialises a new chat-story
 *
 * @title: title of the chat-story
 * @subtitle: subtitle of the chat-story
 * @description: description of the chat story
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

	if (__ec->ecraft == NULL)
	{
		ec_size = size * (2 * i + 3);
		__ec->ecraft = calloc(sizeof(ecraft_t *), ec_size);
		if (__ec->ecraft == NULL)
			return (NULL);
	}
	for (i = 0; __ec->ecraft[i] != NULL; i++)
		;
	ec_size = size * (2 * i + 3);
	__ec->ecraft = realloc(__ec->ecraft, sizeof(ecraft_t *) * ec_size);
	if (__ec->ecraft == NULL)
		return (NULL);

	__ec->ecraft[i] = calloc(sizeof(ecraft_t), 1);
	if (__ec->ecraft[i] == NULL)
		return (NULL);

	__ec->ecraft[i]->__interface = interface;

	__ec->ecraft[i]->__title = strdup(title);
	__ec->ecraft[i]->__subtitle = strdup(subtitle);
	__ec->ecraft[i]->__description = strdup(description);
	__ec->ecraft[i]->__type = strdup(type);

	__set_interf(__ec->ecraft[i]);

	__ec->ecraft[i]->__cast = NULL;
	__ec->ecraft[i]->__meta = NULL;

	return (__ec->ecraft[i]);
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

	if (dname == NULL)
		dname = "<No Name>";
	if (fname == NULL)
		fname = "";
	if (lname == NULL)
		lname = "";
	if (altnames == NULL)
		altnames = "";

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
 * @cast: pointer to the an array of cast responsible for the message to
 *	  display
 * @emoji: state of the @cast at the moment
 * @message: message to display
 * @nmemb: number of cast pointers to reference for number of cast pointers to
 *	   reference is less than or equal to number of the total cast pointers
 *	   in @cast
 *
 * Description: if the @nmemb is greater than number of cast pointers present
 *		in @cast, could lead to undefined behaviour
 *		@cast or any of its elements can be set to NULL
 *		any element of @cast set to NULL will be assigned an identity
 *		of <Unknown>
 *		if @cast is NULL, message to broadcast is taken as anonymous
 *		message
 *		@emoji must also contain the same number of elements in @cast
 *
 * Return: return the index position of the stage within @cstory->meta
*/

int s_cstory(ecraft_t *cstory, cast_t **cast, char **emoji, char *message,
	int nmemb)
{
	int i, j;
	char **emoji_dup = malloc(sizeof(char *) * nmemb);

	if (message == NULL)
		message = "\r";
	if (cstory == NULL)
	{
		/* __null_cstory(cstory, cast, message, emoji); */
		return (-1);
	}
	for (i = 0; i < nmemb; i++)
	{
		if (emoji[i] == NULL)
			emoji[i] = "";
		emoji_dup[i] = strdup(emoji[i]);
	}

	for (i = 0; __ec->ecraft[i] != NULL; i++)
	{
		if (__ec->ecraft[i] == cstory)
		{
			__ec->ecraft[i]->__meta = __m_add_cstory(
				__ec->ecraft[i]->__meta, cast, emoji_dup, message,
					nmemb);
			for (j = 0; __ec->ecraft[i]->__meta[j] != NULL; j++)
				;

			if (j - 1 == 0)	/* print header */
				__h_cstory(__ec->ecraft[i]);
			__s_cstory(cstory, __ec->ecraft[i]->__meta[j - 1],
				nmemb);
			for (i = 0; i < nmemb; i++)
				free(emoji_dup[i]);
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
 * @ncast: number of cast members to reference
 *
 * Return: return nothing
*/

void __s_cstory(ecraft_t *cstory, meta_t *meta, int ncast)
{
	switch (cstory->__interface)
	{
		case EC_CLI:
			__s_cli_cstory(cstory, meta, ncast);

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
 * @ncast: number of cast members to reference
 *
 * Return: return nothing
*/

void __s_cli_cstory(ecraft_t *cstory, meta_t *meta, int ncast)
{
	int i;
	SCREEN *cli = cstory->__interf.cli;

	/* display name should be printed in bold */
	if (meta->cast != NULL)
	{
		for (i = 0; i < ncast; i++)
		{
			attron(A_BOLD);
			if (meta->cast[i] == NULL)
			{
				/* unknown cast/character */
				__ec_printf(cli, "string", "<Unknown>");
			}
			else
			{
				__ec_printf(cli, "string",
					meta->cast[i]->__dname);
			}
			__ec_printf(cli, "string", ": ");
			attroff(A_BOLD);
			if (meta->emoji != NULL && meta->emoji[i] != NULL)
				__emoji_cstory(cli, meta->emoji[i]);
			__ec_printf(cli, "string", "\n");
			/* next cast */
		}
	}	/* if cast is NULL, just print the message */
	__ec_printf(cli, "string", meta->message);
	if (strcmp(meta->message, "\r") != 0)
		__ec_printf(cli, "string", "\n");

	__interrupt(cli, meta->message);
}
