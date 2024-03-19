#include <stdlib.h>
#include <string.h>

#include <gart.h>

/**
 * glabel - create a new label, adding it to the __art descriptor table
 *
 * @dname: dispaly name of the label
 * @fname: first name of the label
 * @lname: last name of the label
 *
 * Return: return id of the newly created label
*/

int64_t glabel(char *dname, char *fname, char *lname)
{
	int64_t i;
	glbl_t *lbl = calloc(sizeof(glbl_t), 1);

	if (lbl == NULL)
		return (-1);

	if (dname == NULL)
		lbl->__dname = strdup("<No Name>");
	else
		lbl->__dname = strdup(dname);

	if (fname == NULL)
		lbl->__fname = strdup("");
	else
		lbl->__fname = strdup(fname);

	if (lname == NULL)
		lbl->__lname = strdup("");
	else
		lbl->__lname = strdup(lname);

	if (lbl->__dname == NULL || lbl->__fname == NULL ||
		lbl->__lname == NULL)
	{
		lbl = NULL;
		free(lbl);

		return (-1);
	}

	i = __gadd(lbl);

	return (i);
}

/**
 * __gadd - adds up a new element to the __art descriptor table
 *
 *  @elem: the new element to add to the descriptor table
 *
 * Return: return nothing
*/

int64_t __gadd(glbl_t *lbl)
{
	int64_t i, size, base_size = 4;

	if ((*__art) == NULL || lbl == NULL)
		return (-1);

	i = (*__art)->lbl_size;
	size = base_size * (2 * i + 3);

	if (i == 0)
	{
		(*__art)->lbl = calloc(sizeof(glbl_t *), size);
		if ((*__art)->lbl == NULL)
			return (-1);
	}
	else
	{
		(*__art)->lbl = realloc((*__art)->lbl,
			sizeof(glbl_t *) * size);
		if ((*__art)->lbl == NULL)
		{
			free((*__art)->lbl);

			return (-1);
		}
	}
	(*__art)->lbl[i] = lbl;
	(*__art)->lbl_size++;

	return (i);
}

/**
 * __glbl_free - free memories allocated by glabel function
 *
 * Return: return nothing
*/

void __glbl_free(void)
{
	int64_t i;
	glbl_t **lbl = (*__art)->lbl;

	if (lbl == NULL)
		return;

	for (i = 0; i < (*__art)->lbl_size; i++)
	{
		free(lbl[i]->__dname);
		free(lbl[i]->__fname);
		free(lbl[i]->__lname);
		free(lbl[i]);
	}
	free(lbl);
}
