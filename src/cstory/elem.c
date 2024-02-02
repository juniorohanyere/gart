#include <stdlib.h>
#include <string.h>

#include <ecraft.h>

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
	elem_t *elem = calloc(sizeof(elem_t), 1);

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

	__add_elem(elem);

	return (elem);
}

/**
 * __add_elem - adds up a new element to the __ec placeholder (__ec->elem)
 *
 * @elem: the new element to add
 *
 * Return: return nothing
*/

void __add_elem(elem_t *elem)
{
	int64_t i, size, base_size = 4;

	if ((*__ec) == NULL || elem == NULL)
		return;

	i = (*__ec)->elem_size;
	size = base_size * (2 * i + 3);

	if (i == 0)
	{
		(*__ec)->elem = calloc(sizeof(elem_t *), size);
		if ((*__ec)->elem == NULL)
			return;
	}
	else
	{
		(*__ec)->elem = realloc((*__ec)->elem,
			sizeof(elem_t *) * size);
		if ((*__ec)->elem == NULL)
		{
			free((*__ec)->elem);

			return;
		}
	}
	(*__ec)->elem[i] = elem;

	(*__ec)->elem_size++;
}

/**
 * __delem - frees memory for an element assigned by ec_elem function
 *
 * Return: return nothing
*/

void __delem(void)
{
	int64_t i;
	elem_t **elem = (*__ec)->elem;

	if (elem == NULL)
		return;

	for (i = 0; i < (*__ec)->elem_size; i++)
	{
		free(elem[i]->__dname);
		free(elem[i]->__fname);
		free(elem[i]->__lname);
		free(elem[i]);
	}
	free(elem);
}
