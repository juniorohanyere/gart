#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ecraft.h"

__ECRAFT;	/* by-pass betty error for use of global variables */

/**
 * pushcraft - sends data to the interface referenced by a given craft
 *
 * @craft: pointer to the craft to reference
 * @cast: pointer to the cast in which the data to send is meant for
 * @buffer: the data/string to send
 * @emoji: the state of the @cast at the moment of sending the data
 *
 * Return: return nothing
*/

void pushcraft(craft_t *craft, cast_t *cast, char *buffer, char *emoji)
{
	meta_t *meta, *temp;
	ecraft_t *ec, *ecraft;

	if (craft == NULL)
	{
		/* __nullcraft(cast, buffer, emoji); */
	}
	else
	{
		while (__ecraft != NULL)
		{
			ec = ecraft;
			if (__ecraft->craft == craft)
			{
				temp = __ecraft->meta;
				__ecraft->meta = __meta(cast, buffer, emoji);
				__ecraft->meta->next = temp;
				while (__ecraft->meta != NULL)
				{
					temp = meta, meta = __ecraft->meta;
					meta->next = temp;
					__ecraft->meta = __ecraft->meta->next;
				}
				__ecraft->meta = meta;
			}
			ecraft = __ecraft, ecraft->next = ec;
			__ecraft = __ecraft->next;
		}	/* __ecraft becomes NULL at this point */
		/* rearrange ground to head from earliest to oldest */
		while (ecraft != NULL)	/* ecraft holds the right data */
		{
			ec = __ecraft, __ecraft = ecraft;
			__ecraft->next = ec, ecraft = ecraft->next;
		}
		/* balanced: __ecraft now contains the right data */

		__setinterf(craft, meta);
		/* __interrupt(getline) */
	}
}

/**
 * __eupdate - updates __ecraft
 *
 * @ecraft: pointer to a new placeholder to be used as update for __ecraft
 *
 * Return: return nothing
*/

void __eupdate(ecraft_t *ecraft)
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
