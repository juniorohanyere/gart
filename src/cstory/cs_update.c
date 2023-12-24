#include <stdlib.h>
#include <unistd.h>

#include <ecraft.h>

void ec_update(void)
{
	int64_t i;

	switch (__ec->interf)
	{
		case EC_NONE:
			break;	/* do nothing */

		case EC_CLI:
			#ifdef _CRAFT
			for (i = __ec->top; __ec->ecraft[i] != NULL; i++)
			{
				#if _CRAFT == 1
				__cs_update_cli(__ec->ecraft[i]);
				#endif	/* _CRAFT == 1 */
			}
			#endif	/* _CRAFT */

			break;

		case EC_GUI:
			/* TODO */

			break;

		default:
			dprintf(STDERR_FILENO,
				"invalid interface: no such interface");
			abort();

			return;
	}
}
