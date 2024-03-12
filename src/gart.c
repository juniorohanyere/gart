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

void ginit(int interface)
{
	/* initialise generative art, do not reinitailise */
	if (__art == NULL)
	{
		__art = calloc(sizeof(art_t), 1);

		/* disable tts and emoji by default */
		__art->tts = GNONE;
		__art->emoji = GNONE;
		__art->interf = interface;

		__ginterf();

		__art->status = GINIT;
		__art->vertice = 0;
		__art->top = -1;
		__art->bottom = 0;
		__art->ref = 0;
	}
}
