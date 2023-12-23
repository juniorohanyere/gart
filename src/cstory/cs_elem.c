#include <stdlib.h>
#include <string.h>

#include <cstory.h>

#ifdef _CRAFT
#if _CRAFT == 1

void ec_create(elem_t *elem, char *dname, char *fname, char *lname,
	char *altnames)
{
	if (elem == NULL)
	{
		/* initialise element */
		elem = malloc(sizeof(elem_t));
		if (elem == NULL)
			return;
	}

	if (dname == NULL)
		dname = "<No Name>";
	if (fname == NULL)
		fname = "";
	if (lname == NULL)
		lname = "";
	if (altnames == NULL)
		altnames = "";

	elem->__dname = strdup(dname);
	elem->__fname = strdup(fname);
	elem->__lname = strdup(lname);
	elem->__altnames = strdup(altnames);

	if (elem->__dname == NULL || elem->__fname == NULL ||
		elem->__lname == NULL || elem->__altnames == NULL)
	{
		elem = NULL;
		free(elem);

		return;
	}
}

#endif	/* _CRAFT == 1 */
#endif	/* _CRAFT */
