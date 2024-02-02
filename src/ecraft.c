#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <term.h>
#include <termbox.h>

#include <ecraft.h>

__EC;	/* bypass betty warining for use of global variables */

/**
 * ec_init - initialise ecraft
 *
 * Description: subsequent call to ec_init() is useless unless ec_free() has
 *		being called, initialisation only occur once
 *		hence, it's not an error to call ec_init() multiple times
 *		without a call to ec_free()
 *
 * Return: return nothing
*/

void ec_init(void)
{
	/* initialise ecraft, do not reinitialise */
	if (__ec == NULL)
	{
		__ec = calloc(sizeof(ec_t *), 1024);

		*__ec = calloc(sizeof(ec_t), 1);
		/* disable tts and emoji by default */
		(*__ec)->tts = EC_NONE;
		(*__ec)->emoji = EC_NONE;

		(*__ec)->interf = _INTERFACE;
		__ec_interf();

		(*__ec)->status = EC_INIT;
		(*__ec)->size = 0;
		(*__ec)->index = (*__ec)->size;
		(*__ec)->elem_size = 0;
	}
}
