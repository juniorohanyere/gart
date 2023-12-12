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
