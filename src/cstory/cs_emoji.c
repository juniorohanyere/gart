#include <string.h>
#include <assert.h>

#include <cstory.h>

/**
 * __cs_emoji - validates emoji for a chat story
 *
 * @emoji: pointer to an array of emoji to validate
 *
 * Return: return nothing
*/

void __cs_emoji(char **emoji)
{
	int emoji_check;
	int64_t i, emoji_size = 1;
	emoji_t *lemoji = __ec_lemoji();

	while (emoji[emoji_size - 1] != NULL)
	{
		if (emoji_size > 3)
		{
			/* do some clean up at least */
			if (__ec->interf == EC_CLI)
			{
				delscreen(__ec->screen.cli), ec_final();
				assert(emoji_size <= 3);
			}
		}
		for (i = 0; lemoji[i].emoji != NULL; i++)
		{
			emoji_check = strcmp(emoji[emoji_size - 1],
				lemoji[i].emoji);
			/* end of dictionary, yet couldn't validate emoji */
			if (lemoji[i + 1].emoji == NULL && emoji_check != 0)
			{
				if (__ec->interf == EC_CLI)
				{
					delscreen(__ec->screen.cli);
					ec_final();
					assert(emoji_check == 0);
				}
			}
			else if (emoji_check == 0)
			{
				if (__ec->emoji == __EC_EMOJI)
					__ec_printf("emoji", "0x00000");
				__cs_pemoji(lemoji[i]);

				break;	/* check next emoji */
			}
		}
		emoji_size++;	/* next emoji */
	}
}

/**
 * __cs_pemoji - prints emoji based on current emoji mode
 *
 * @emoji: the emoji to print
 *
 * Return: return nothing
*/

void __cs_pemoji(emoji_t emoji)
{
	if (__ec->interf != EC_CLI)	/* TODO to be ammended */
		return;

	if (__ec->emoji == __EC_EMOJI)	/* emoji mode is enabled */
	{
		attron(A_BOLD);
		__ec_printf("emoji", emoji.unicode);
		move(getcury(stdscr), getcurx(stdscr) + 2);	/* handle wide character */
		attroff(A_BOLD);
	}
	else if (__ec->emoji == __EC_LEMOJI)	/* long string mode enabled */
	{
		attron(A_BOLD);
		__ec_printf("string", emoji.string);
		attroff(A_BOLD);
	}
	else if (__ec->emoji == __EC_SEMOJI)	/* short string mode enabled */
	{
		attron(A_BOLD);
		__ec_printf("string", "[");
		__ec_printf("string", emoji.emoji);
		__ec_printf("string", "]");
		attroff(A_BOLD);
	}
}
