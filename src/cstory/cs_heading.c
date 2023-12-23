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
	attron(A_BOLD);
	__ec_printf("string", "Title:\t");
	attroff(A_BOLD);

	__ec_printf("string", __ec->title);
	__ec_printf("string", "\n");

	attron(A_BOLD);
	__ec_printf("string", "Subtitle:\t");
	attroff(A_BOLD);

	__ec_printf("string", __ec->subtitle);
	__ec_printf("string", "\n");

	attron(A_BOLD);
	__ec_printf("string", "Description:\t");
	attroff(A_BOLD);

	__ec_printf("string", __ec->desc);
	__ec_printf("string", "\n");

	__ec_printf("string", "\n");	/* print extra new line */
}
