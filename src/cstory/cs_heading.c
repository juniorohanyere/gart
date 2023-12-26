#include <stdlib.h>
#include <string.h>

#include <ecraft.h>

/**
 * __cs_heading_cli - prints header info for a chat story for command line
 *		      interface
 *
 * Description: header info include Title, Subtitle, and Description
 *
 * Return: return nothing
*/

void __cs_heading_cli(void)
{
	/* TODO calculate the lenght of the strings to determine malloc size */
	char *str = malloc(sizeof(char) * 1024);

	attron(A_BOLD);
	__ec_printf("string", "Title:\t\t");
	attroff(A_BOLD);
	strcpy(str, "Title: ");

	__ec_printf("string", __ec->title);
	__ec_printf("string", "\n");
	strcat(str, __ec->title);
	strcat(str, ". ");

	attron(A_BOLD);
	__ec_printf("string", "Subtitle:\t");
	attroff(A_BOLD);
	strcat(str, "Subtitle: ");

	__ec_printf("string", __ec->subtitle);
	__ec_printf("string", "\n");
	strcat(str, __ec->subtitle);
	strcat(str, ". ");

	attron(A_BOLD);
	__ec_printf("string", "Description:\t");
	attroff(A_BOLD);
	strcat(str, "Description: ");

	__ec_printf("string", __ec->desc);
	__ec_printf("string", "\n");
	strcat(str, __ec->desc);
	strcat(str, ". ");

	__ec_printf("string", "\n");	/* print extra new line */

	__ec_interrupt(str);

	clear();
	free(str);
}
