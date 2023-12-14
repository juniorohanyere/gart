#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ecraft.h"

/**
 * newcast - set up a new cast
 *
 * @dname: the display name for the new cast to create
 * @fname: the first name of the new cast to create
 * @lname: the last name of the new cast to create
 * @altnames: alternate names of the new cast to create
 *
 * Description: @dname and @altnames should be strings separated by spaces if
 *		the names contains more than one word
 *
 * Return: return a pointer to the newly created cast
*/

cast_t *newcast(char *dname, char *fname, char *lname, char *altnames)
{
	cast_t *cast;

	cast = malloc(sizeof(cast_t));
	if (cast == NULL)
		return (NULL);

	cast->__height = EC_NONE;
	cast->__weight = EC_NONE;
	cast->__gender = EC_NONE;

	cast->__dname = strdup(dname);
	cast->__fname = strdup(fname);
	cast->__lname = strdup(lname);
	cast->__altnames = strdup(altnames);

	if (cast->__fname == NULL || cast->__lname == NULL ||
		cast->__altnames == NULL || cast->__dname == NULL)
	{
		free(cast);

		return (NULL);
	}

	__addcast(cast);

	return (cast);
}


void __addcast(cast_t *cast)
{
	int i, craft_size = __ec_size;

	assert(craft_size >= 1024);

	if (__cast == NULL)
		__cast = calloc(sizeof(cast_t *), __ec_size);

	for (i = 0; __cast[i] != NULL; i++)
		;

	/* update __cast */
	__cast[i] = cast;
}

/**
 * __freecast - deletes all casts contained in __cast
 *
 * Description: __cast is a double pointer to all the casts
 *		(see macro __CAST)
 *
 * Return: return nothing
*/

void __freecast(void)
{
	int i = 0;

	if (__cast == NULL)
		return;

	while (__cast[i] != NULL)
	{
		free(__cast[i]->__altnames);
		free(__cast[i]->__lname);
		free(__cast[i]->__fname);
		free(__cast[i]->__dname);

		free(__cast[i]);

		i++;
	}
	free(__cast);
}

/**
 * setname - resets the name(s) of a cast
 *
 * @cast: pointer to the cast
 * @dname: display name
 * @fname: first name
 * @lname: last name
 * @altnames: alternate names
 *
 * Return: return nothing
*/

void setname(cast_t *cast, char *dname, char *fname, char *lname,
	char *altnames)
{
	if (cast == NULL)
		return;

	cast->__dname = strdup(dname);
	cast->__fname = strdup(fname);
	cast->__lname = strdup(lname);
	cast->__altnames = strdup(altnames);
}
