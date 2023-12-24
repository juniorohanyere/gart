#include <stdlib.h>
#include <string.h>

#include <cstory.h>

#ifdef _CRAFT
#if _CRAFT == 1

/**
 * ec_create - initialises a new element, without adding it to the stack
 *
 * @elem: the new element to initialise
 * @dname: display name of the element
 * @fname: first name of the element
 * @lname: last name of the element
 *
 * Description: @elem should be a malloc'd variable, otherwise an the element
 *		will be marked as <Unknown>
 *
 * Return: return nothing
*/

void ec_create(elem_t *elem, char *dname, char *fname, char *lname)
{
	if (elem == NULL)
		return;

	if (dname == NULL)
		dname = "<No Name>";
	if (fname == NULL)
		fname = "";
	if (lname == NULL)
		lname = "";

	elem->__dname = strdup(dname);
	elem->__fname = strdup(fname);
	elem->__lname = strdup(lname);

	if (elem->__dname == NULL || elem->__fname == NULL ||
		elem->__lname == NULL)
	{
		elem = NULL;
		free(elem);

		return;
	}
}

#endif	/* _CRAFT == 1 */
#endif	/* _CRAFT */
