#include <stdio.h>
#include <stdlib.h>

#include "ecraft.h"

void __interrupt(void)
{
	char *line = NULL;
	size_t n = 1024;
	ssize_t flag;

	printf("$ ");

	flag = getline(&line, &n, stdin);
	if (flag == -1)
	{
		exit(EXIT_SUCCESS);
	}

	free(line);
}
