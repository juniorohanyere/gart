#include <stdlib.h>
#include <string.h>

#include <gart.h>

/**
 * gcreate - create a new element, adding it to the __art descriptor table
 *
 * @dname: dispaly name of the element
 * @fname: first name of the element
 * @lname: last name of the element
 *
 * Return: return a pointer to the new element created
*/

elem_t *gcreate(char *dname, char *fname, char *lname)
{
	elem_t *elem = calloc(sizeof(elem_t), 1);

	if (elem == NULL)
		return (NULL);

	if (dname == NULL)
		elem->__dname = strdup("<No Name>");
	else
		elem->__dname = strdup(dname);

	if (fname == NULL)
		elem->__fname = strdup("");
	else
		elem->__fname = strdup(fname);

	if (lname == NULL)
		elem->__lname = strdup("");
	else
		elem->__lname = strdup(lname);

	if (elem->__dname == NULL || elem->__fname == NULL ||
		elem->__lname == NULL)
	{
		elem = NULL;
		free(elem);

		return (NULL);
	}

	__gadd(elem);

	return (elem);
}

/**
 * __gadd - adds up a new element to the __art descriptor table
 *
 *  @elem: the new element to add to the descriptor table
 *
 * Return: return nothing
*/

void __gadd(elem_t *elem)
{
	int64_t i, size, base_size = 4;

	if ((*__art) == NULL || elem == NULL)
		return;

	i = (*__art)->elem_size;
	size = base_size * (2 * i + 3);

	if (i == 0)
	{
		(*__art)->elem = calloc(sizeof(elem_t *), size);
		if ((*__art)->elem == NULL)
			return;
	}
	else
	{
		(*__art)->elem = realloc((*__art)->elem,
			sizeof(elem_t *) * size);
		if ((*__art)->elem == NULL)
		{
			free((*__art)->elem);

			return;
		}
	}
	(*__art)->elem[i] = elem;
	(*__art)->elem_size++;
}

/**
 * __delem - free memories allocated by gcreate function
 *
 * Return: return nothing
*/

void __delem(void)
{
	int64_t i;
	elem_t **elem = (*__art)->elem;

	if (elem == NULL)
		return;

	for (i = 0; i < (*__art)->elem_size; i++)
	{
		free(elem[i]->__dname);
		free(elem[i]->__fname);
		free(elem[i]->__lname);
		free(elem[i]);
	}
	free(elem);
}
