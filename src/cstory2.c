#include <string.h>
#include <assert.h>

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

/**
 * __emoji_cstory - validates and prints emoji for a chat story
 *
 * @screen: the display
 * @emoji: pointer to an array of emoji to validate and print
 *
 * Return: return nothing
*/

void __emoji_cstory(SCREEN *screen, char **emoji)
{
	int i, emoji_size = 1, emoji_check;
	emoji_t *emojis = __emoji_list();

	while (emoji[emoji_size - 1] != NULL)
	{
		if (emoji_size > 3)
		{
			/* do some clean up at least */
			delscreen(screen);
			__scr_cleanup();

			assert(emoji_size <= 3);
		}
		for (i = 0; emojis[i].emoji != NULL; i++)
		{
			emoji_check = strcmp(emoji[emoji_size - 1],
				emojis[i].emoji);
			/* end of dictionary, yet couldn't validate emoji */
			if (emojis[i + 1].emoji == NULL && emoji_check != 0)
			{
				delscreen(screen);
				__scr_cleanup();

				assert(emoji_check == 0);
			}
			else if (emoji_check == 0)
			{
				if (__ec->emoji == __EC_INIT)
				{
					attron(A_BOLD);
					__ec_printf(screen, "emoji",
						emojis[i].unicode);
					__ec_printf(screen, "string", "  ");
					attroff(A_BOLD);
				}

				else if (__ec->emoji == __EC_INIT1)
				{
					attron(A_BOLD);
					__ec_printf(screen, "string",
						emojis[i].string);
					attroff(A_BOLD);
				}

				else if (__ec->emoji == __EC_INIT2)
				{
					attron(A_BOLD);
					__ec_printf(screen, "string", "[");
					__ec_printf(screen, "string",
						emojis[i].emoji);
					__ec_printf(screen, "string", "]");
					attroff(A_BOLD);
				}
				break;	/* check next emoji */
			}
		}
		emoji_size++;	/* next emoji */
	}
}
