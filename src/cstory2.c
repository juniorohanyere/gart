#include <ecraft.h>

/**
 * __h_cstory - prints header info for a chat story
 *
 * @cstory: pointer to the chat story
 *
 * Description: header info include Title, Subtitle, and Description
 *
 * Return: return nothing
*/

void __h_cstory(ecraft_t *cstory)
{
	SCREEN *cli = cstory->__interf.cli;

	attron(A_BOLD);
	__ec_printf(cli, "string", "Title:		");
	attroff(A_BOLD);

	__ec_printf(cli, "string", cstory->__title);
	__ec_printf(cli, "string", "\n");

	attron(A_BOLD);
	__ec_printf(cli, "string", "Subtitle:	");
	attroff(A_BOLD);

	__ec_printf(cli, "string", cstory->__subtitle);
	__ec_printf(cli, "string", "\n");

	attron(A_BOLD);
	__ec_printf(cli, "string", "Description:	");
	attroff(A_BOLD);

	__ec_printf(cli, "string", cstory->__description);
	__ec_printf(cli, "string", "\n\n");
}
