#include <stdio.h>
#include <stdlib.h>

#include "ecraft.h"

/**
 * __setcli - set command line interface (index 0)
 *
 * @meta: meta information of a craft
 *
 * Return: return nothing
*/

void __setcli(meta_t *meta)
{
	int i = 0;

	printf("\n");

	if (meta->cast != NULL && meta->cast->__dname != NULL)
		printf("%s: ", meta->cast->__dname);	/* print in bold */

	while (meta->emoji[i] != NULL)
	{
		printf("%s ", meta->emoji[i]);
		i++;
	}
	printf("\n");

	printf("%s\n", meta->body);
}
