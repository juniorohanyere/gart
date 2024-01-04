#include <stdlib.h>
#include <string.h>

#include <ecraft.h>

/**
 * __ec_head - prints header info for a chat story for command line
 *		      interface
 *
 * Description: header info include Title, Subtitle, and Description
 *
 * Return: return nothing
*/

void __ec_head(void)
{
	/* TODO calculate the lenght of the strings to determine malloc size */
	char *str = malloc(sizeof(char) * 1024);

	attron(A_BOLD);
	__ec_print("string", "Title:\t\t");
	attroff(A_BOLD);
	strcpy(str, "Title: ");

	__ec_print("string", __ec->title);
	__ec_print("string", "\n");
	strcat(str, __ec->title);
	strcat(str, ". ");

	attron(A_BOLD);
	__ec_print("string", "Subtitle:\t");
	attroff(A_BOLD);
	strcat(str, "Subtitle: ");

	__ec_print("string", __ec->subtitle);
	__ec_print("string", "\n");
	strcat(str, __ec->subtitle);
	strcat(str, ". ");

	attron(A_BOLD);
	__ec_print("string", "Description:\t");
	attroff(A_BOLD);
	strcat(str, "Description: ");

	__ec_print("string", __ec->desc);
	__ec_print("string", "\n");
	strcat(str, __ec->desc);
	strcat(str, ". ");

	__ec_print("string", "\n");	/* print extra new line */

	__ec_read(1);

	clear();
	free(str);
}
