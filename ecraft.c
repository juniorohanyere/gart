#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ecraft.h"

__ECRAFT;	/* by-pass betty error for use of global variables */

/**
 * freecraft - clean-up
 *	       this function must be called at the end of the user program in
 *	       order to clean up or free allocated memory
 *
 * Return: return nothing
*/

void freecraft(void)
{
	ecraft_t *ecraft = __ecraft, *next;

	if (__ecraft == NULL)
		return;

	while (ecraft != NULL)
	{
		next = ecraft->next;

		endcraft(ecraft->craft);
		__delecho(ecraft->echo);
		free(ecraft);

		ecraft = next;
	}
}
