#include <string.h>
#include <assert.h>

#include <gart.h>

/**
 * __gemoji - validate emoji for a chat story
 *
 * @emoji: pointer to emoji to validate
 * @index: location of @emoji within an array of emojis
 *
 * Return: return nothing
*/

void __gemoji(char *emoji, int64_t index)
{
	int emoji_check;
	int64_t i, emoji_size = index + 1;
	emoji_t *lemoji = __emoji_list();

	if (emoji != NULL)
	{
		if (emoji_size > 3)
		{
			/* do some clean up at least */
			if ((*__art)->interf == GCLI)
			{
				gfinal();
				assert(emoji_size <= 3);
			}
		}
		for (i = 0; lemoji[i].emoji != NULL; i++)
		{
			emoji_check = strcmp(emoji, lemoji[i].emoji);
			/* end of dictionary, yet couldn't validate emoji */
			if (lemoji[i + 1].emoji == NULL && emoji_check != 0)
			{
				if ((*__art)->interf == GCLI)
				{
					gfinal();
					assert(emoji_check == 0);
				}
			}
			else if (emoji_check == 0)
			{
				if ((*__art)->emoji == __GUNICODE)
					__gprint("u", "0x00000");
				__pemoji(lemoji[i]);

				break;	/* check next emoji */
			}
		}
		emoji_size++;	/* next emoji */
	}
}

/**
 * __pemoji - print emoji based on current emoji style
 *
 * @emoji: the emoji to print
 *
 * Return: return nothing
*/

void __pemoji(emoji_t emoji)
{
	if ((*__art)->interf != GCLI)	/* TODO to be amended */
		return;

	if ((*__art)->emoji == __GUNICODE)	/* pictorial emoji style */
	{
		attron(A_BOLD);
		__gprint("u", emoji.unicode);

		/*
		 * handle wide character (deprecated)
		 * move (getcury(stdscr), getcurx(stdscr) + 2);
		*/
		attroff(A_BOLD);
	}
	else if ((*__art)->emoji == __GSTRING)	/* long string style enabled */
	{
		attron(A_BOLD);
		__gprint("s", "[");
		__gprint("s", emoji.string);
		__gprint("s", "]");
		attroff(A_BOLD);
		move(getcury(stdscr), getcurx(stdscr) - 1);
	}
	else if ((*__art)->emoji == __GSSTRING)	/* short string style */
	{
		attron(A_BOLD);
		__gprint("s", "[");
		__gprint("s", emoji.emoji);
		__gprint("s", "]");
		attroff(A_BOLD);
		move(getcury(stdscr), getcurx(stdscr) - 1);
	}
}
