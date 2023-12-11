#include <stdio.h>
#include <stdlib.h>

#include "ecraft.h"

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

/**
 * __mupdate - updates __ecraft->craft->meta
 *
 * @meta: pointer to the meta to update (__ecraft->craft->meta)
 * @temp: pointer to the new meta to be used as update for @meta
 *
 * Return: return nothing
*/

meta_t *__mupdate(meta_t *meta, meta_t *temp)
{
	meta_t *new;

	if (meta == NULL)
	{
		meta = temp;
	}
	else
	{
		new = meta;
		while (new->next != NULL)
		{
			new = new->next;
		}

		new->next = temp;
		/* meta = new; */
	}

	return (meta);
}
