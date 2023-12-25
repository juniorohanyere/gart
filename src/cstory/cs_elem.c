#include <stdlib.h>
#include <string.h>

#include <cstory.h>

/**
 * ec_elem - initialises a new element, adding it to the __ec stack
 *
 * @dname: display name of the element
 * @fname: first name of the element
 * @lname: last name of the element
 *
 * Description: @elem should be a malloc'd variable, otherwise an the element
 *		will be marked as <Unknown>
 *
 * Return: return a pointer to the new element created
*/

elem_t *ec_elem(char *dname, char *fname, char *lname)
{
	elem_t *elem = malloc(sizeof(elem_t));

	if (elem == NULL)
		return (NULL);

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

		return (NULL);
	}

	__cs_elem(elem);

	return (elem);
}

/**
 * __cs_delem - frees memory for an element assigned by ec_elem function
 *
 * Return: return nothing
*/

void __cs_delem(void)
{
	int64_t i;
	elem_t **elem = __ec->elem;

	if (elem == NULL)
		return;

	for (i = 0; elem[i] != NULL; i++)
	{
		if (elem[i]->__dname != NULL)
			free(elem[i]->__dname);
		if (elem[i]->__fname != NULL)
			free(elem[i]->__fname);
		if (elem[i]->__lname != NULL)
			free(elem[i]->__lname);

		free(elem[i]);
	}
	free(elem);
}

/**
 * __cs_elem - adds up a new element to the craft stack (__ec->elem)
 *
 * @elem: the new element to add
 *
 * Return: return nothing
*/

void __cs_elem(elem_t *elem)
{
	int64_t i = 0, elem_size, base_size = 4;

	if (__ec == NULL || elem == NULL)
		return;


	if (__ec->elem == NULL)
	{
		elem_size = base_size * (2 * i + 3);
		__ec->elem = calloc(sizeof(elem_t *), elem_size);
		if (__ec->elem == NULL)
			return;
	}

	for (i = 0; __ec->elem[i] != NULL; i++)
		;
	elem_size = base_size * (2 * i + 3);
	__ec->elem = realloc(__ec->elem, sizeof(elem_t *) * elem_size);
	if (__ec->elem == NULL)
	{
		free(__ec->elem);

		return;
	}

	__ec->elem[i] = elem;
}
