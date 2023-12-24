#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ecraft.h>

#ifdef _CRAFT

#if _CRAFT == 1

int64_t ec_echo(elem_t **elem, char **emoji, char *string, int64_t nmemb)
{
	int64_t i;
	char *str = "";
	char **emoji_dup;

	emoji_dup = malloc(sizeof(char *) * nmemb);

	for (i = 0; i < nmemb; i++)
	{
		if (emoji[i] == NULL)
			emoji_dup[i] = strdup(str);
		else
			emoji_dup[i] = strdup(emoji[i]);
	}
	if (string == NULL)
	{
		str = "\r";	/* sentinel value to track NULL string */
		/* set last parameter to -1 for no ref */
		i = __cs_load(elem, emoji_dup, str, nmemb, -1);
	}
	else
		i = __cs_load(elem, emoji_dup, string, nmemb, -1);

	ec_update();

	__ec_interrupt(__ec->ecraft[i]->string);

	return (i);
}

int64_t ec_recho(elem_t **elem, char **emoji, char *string, int64_t nmemb,
	int64_t ref)
{
	int64_t i;
	char *str = "";	/* so as not to modify the original string(s) passed */
	char **emoji_dup;

	emoji_dup = malloc(sizeof(char *) * nmemb);

	for (i = 0; i < nmemb; i++)
	{
		if (emoji[i] == NULL)
			emoji_dup[i] = strdup(str);
		else
			emoji_dup[i] = strdup(emoji[i]);
	}

	if (string == NULL)
	{
		str = "\r";	/* sentinel value to track NULL string */
		/* set last parameter to value of @ref */
		i = __cs_load(elem, emoji_dup, str, nmemb, ref);
	}
	else
		i = __cs_load(elem, emoji_dup, string, nmemb, ref);

	clear();
	ec_update();

	__ec_interrupt(__ec->ecraft[i]->string);

	return (i);
}
#endif	/* _CRAFT == 1 */

#endif	/* _CRAFT */
