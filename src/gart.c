#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <term.h>
#include <termbox.h>

#include <gart.h>

__ART;	/* bypass betty warning for use of global variables */

/**
 * ginit - initialise the genarative art setting up an interface
 *
 * @interface: GNONE, GCLI, or GGUI
 *
 * Description: subsequent call to ginit() is has no effect unless gfinal() has
 *		been called, initialisation only occur once
 *
 * Return: return nothing
*/

void ginit(void)
{
	/* initialise generative art, do not reinitailise */
	if (__art == NULL)
	{
		__art = calloc(sizeof(art_t *), 1024);

		*__art = calloc(sizeof(art_t), 1);
		/* disable tts and emoji by default */
		(*__art)->tts = GNONE;
		(*__art)->emoji = GNONE;

		(*__art)->interf = _INTERFACE;
		__ginterf();

		(*__art)->status = GINIT;
		(*__art)->size = 0;
		(*__art)->index = (*__art)->size;
		(*__art)->elem_size = 0;
	}
}
