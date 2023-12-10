#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ecraft.h"

/**
 * newcraft - creates/initialises a new craft
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

craft_t *newcraft(char *title, char *format, int interface)
{
	craft_t *craft;
	ecraft_t *temp, *ecraft;

	/* validate interface */
	if (__vinterf(interface) == 1)
	{
		dprintf(STDERR_FILENO, "fatal: invalid interface");
		/* TODO: free malloc'ed variables */
		exit(EXIT_FAILURE);
	}

	craft = malloc(sizeof(craft_t));
	ecraft = malloc(sizeof(ecraft_t));
	if (craft == NULL || ecraft == NULL)
		return (NULL);

	craft->__status = EC_INIT, craft->__interface = interface;
	craft->__title = malloc(sizeof(char));
	craft->__format = malloc(sizeof(char));
	if (craft->__title == NULL || craft->__format == NULL)
	{
		free(craft)
		return (NULL);
	}

	strcpy(craft->__title, title), strcpy(craft->__format, format);
	ecraft->craft = craft, ecraft->meta = NULL, ecraft->next = __ecraft;
	__ecraft = ecraft, ecraft = NULL;

	while (__ecraft != NULL)
	{
		temp = malloc(sizeof(ecraft_t));
		temp->craft = __ecraft->craft, temp->meta = __ecraft->meta;
		temp->next = ecraft, ecraft = temp, __ecraft = __ecraft->next;
	}
	__ecraft = ecraft;
	/* free(temp); */
	/* free(ecraft); */
	return (craft);
}

/**
 * startcraft - prepares a craft for work :)
 *
 * @craft: the craft to prepare
 *
 * Return: return nothing
*/

void startcraft(craft_t *craft)
{
	if (craft == NULL)
		return;

	craft->__status = EC_START;
}

/**
 * endcraft - ends/hides a specified craft passed as a parameter
 *
 * @craft: pointer to the craft to end/hide
 *
 * Return: return nothing
*/

void endcraft(craft_t *craft)
{
	craft->__status = EC_END;
}

/**
 * delcraft - finalises a craft and frees all memory associated
 *
 * @craft: the craft to finalise
 *
 * Return: return nothing
*/

void delcraft(craft_t *craft)
{
	/* free all malloc'ed variables */
}
