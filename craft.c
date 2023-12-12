#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "ecraft.h"

/**
 * initcraft - creates/initialises a new craft
 *
 * @title: the desired title for the new craft
 * @format: the format of the new craft
 *	    valid formats: letter, story, chat-story, comic, etc
 * @interface: the desired interface for the craft
 *	       valid interfaces: NONE, CLI, CLI1, CLI2, CLI3, GUI, GUI2, etc
 *
 * Description: adds, to the end of the master node, a new craft
 *
 * Return: return a pointer to the newly created craft
 *	   return a NULL pointer on failure
*/

craft_t *initcraft(char *title, char *format, int interface)
{
	craft_t *craft;
	ecraft_t *ecraft;

	/* validate interface */
	assert(interface == EC_NONE || interface == EC_CLI);

	craft = calloc(sizeof(craft_t), 1);
	ecraft = malloc(sizeof(ecraft_t));

	if (craft == NULL || ecraft == NULL)
		return (NULL);

	craft->__interface = interface;

	craft->__title = strdup(title);
	craft->__format = strdup(format);

	if (craft->__title == NULL || craft->__format == NULL)
	{
		free(ecraft);
		free(craft);
		return (NULL);
	}

	ecraft->craft = craft;
	ecraft->echo = NULL;
	ecraft->next = NULL;

	__addcraft(ecraft);

	return (craft);
}

/**
 * endcraft - finalises/ends and frees all memory associated
 *
 * @craft: the craft to finalise
 *
 * Return: return nothing
*/

void endcraft(craft_t *craft)
{
	/* free all malloc'ed variables */
	if (craft == NULL)
		return;

	free(craft->__title);
	free(craft->__format);

	free(craft);
}

/**
 * __addcraft - updates __ecraft
 *
 * @ecraft: pointer to a new placeholder to be used as update for __ecraft
 *
 * Return: return nothing
*/

void __addcraft(ecraft_t *ecraft)
{
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
