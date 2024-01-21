#include <string.h>
#include <assert.h>

#include <ecraft.h>

/**
 * __ec_emoji - validates emoji for a chat story
 *
 * @emoji: pointer to an array of emoji to validate
 * @index: location of @emoji within an array of emojis
 *
 * Return: return nothing
*/

void __ec_emoji(char *emoji, int64_t index)
{
	int emoji_check;
	int64_t i, emoji_size = index + 1;
	emoji_t *lemoji = __emoji_list();

	if (emoji != NULL)
	{
		if (emoji_size > 3)
		{
			/* do some clean up at least */
			if ((*__ec)->interf == EC_CLI)
			{
				decraft();
				assert(emoji_size <= 3);
			}
		}
		for (i = 0; lemoji[i].emoji != NULL; i++)
		{
			emoji_check = strcmp(emoji, lemoji[i].emoji);
			/* end of dictionary, yet couldn't validate emoji */
			if (lemoji[i + 1].emoji == NULL && emoji_check != 0)
			{
				if ((*__ec)->interf == EC_CLI)
				{
					decraft();
					assert(emoji_check == 0);
				}
			}
			else if (emoji_check == 0)
			{
				if ((*__ec)->emoji == __EC_UNICODE)
					__ec_print("u", "0x00000");
				__pemoji(lemoji[i]);

				break;	/* check next emoji */
			}
		}
		emoji_size++;	/* next emoji */
	}
}

/**
 * __pemoji - prints emoji based on current emoji mode
 *
 * @emoji: the emoji to print
 *
 * Return: return nothing
*/

void __pemoji(emoji_t emoji)
{
	if ((*__ec)->interf != EC_CLI)	/* TODO to be ammended */
		return;

	if ((*__ec)->emoji == __EC_UNICODE)	/* emoji mode is enabled */
	{
		attron(A_BOLD);
		__ec_print("u", emoji.unicode);

		/*
		 * handle wide character (Deprecated)
		 * move(getcury(stdscr), getcurx(stdscr) + 2);
		*/
		attroff(A_BOLD);
	}
	else if ((*__ec)->emoji == __EC_STRING)	/* long string mode enabled */
	{
		attron(A_BOLD);
		__ec_print("s", emoji.string);
		attroff(A_BOLD);
	}
	else if ((*__ec)->emoji == __EC_SSTRING)	/* short string mode */
	{
		attron(A_BOLD);
		__ec_print("s", "[");
		__ec_print("s", emoji.emoji);
		__ec_print("s", "]");
		attroff(A_BOLD);
	}
}
