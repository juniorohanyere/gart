#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ecraft.h>

#ifdef _CRAFT

#if _CRAFT == 1

void ec_start(char *title, char *subtitle, char *description)
{
	if (__ec == NULL)
	{
		dprintf(STDERR_FILENO,
			"invalid start: ecraft not initialized\n");
		abort();
	}
	__ec->title = strdup(title);
	__ec->subtitle = strdup(subtitle);
	__ec->desc = strdup(description);

	if (__ec->title == NULL || __ec->subtitle == NULL ||
		__ec->desc == NULL)
	{
		dprintf(STDERR_FILENO,
			"insufficient memory: coundn't start ecraft");
	}
	/* update screen with heading */
}

void ec_end(void)
{
	__ec->status = EC_END;
}

#endif	/* _CRAFT == 1 */

#endif	/* _CRAFT */
