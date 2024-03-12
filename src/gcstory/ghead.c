#include <stdlib.h>
#include <string.h>

#include <gart.h>

/**
 * __ghead - print headers for a chat story on the cli
 *
 * Description: headers include Title, Subtitle, and Description
 *
 * Return: return nothing
*/

void __ghead(void)
{
	/* TODO calculate the length of the strings to determine malloc size */
	char *str = malloc(sizeof(char) * 1024);

	attron(A_BOLD);
	__gprint("s", "Title:\t\t");
	attroff(A_BOLD);
	strcpy(str, "Title: ");

	__gprint("s", __art->title);
	__gprint("s", "\n");
	strcat(str, __art->title);
	strcat(str, ". ");

	attron(A_BOLD);
	__gprint("s", "Subtitle:\t");
	attroff(A_BOLD);
	strcat(str, "Subtitle: ");

	__gprint("s", __art->subtitle);
	__gprint("s", "\n");
	strcat(str, __art->subtitle);
	strcat(str, ". ");

	attron(A_BOLD);
	__gprint("s", "Description:\t");
	attroff(A_BOLD);
	strcat(str, "Description: ");

	__gprint("s", __art->desc);
	__gprint("s", "\n");
	strcat(str, __art->desc);
	strcat(str, ". ");

	__gprint("s", "\n");  /* print extra new line */

	__gread(1);

	erase();
	free(str);
}
