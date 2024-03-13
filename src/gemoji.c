#include <string.h>
#include <assert.h>

#include <gart.h>

/**
 * __emoji_list - list of emojis, their representation, and respective unicode
 *		  values
 *
 * Description: the emojis are arranged in chronological order
 *		the chronological order ranging from representation, to emoji,
 *		to unicode
 *
 * Return: return a pointer to the list of emojis
*/

emoji_t *__emoji_list(void)
{
	static emoji_t emoji[] = {	/* arrange in chronological order */
		{"b-f-w-s-e", "0x1F601", "beaming face with smiling eyes"},
		{"c-f", "0x1F622", "crying face"},
		{"f-b-a-k", "0x1F618", "face blowing a kiss"},
		{"f-s-f", "0x1F60B", "face savoring food"},
		{"f-w-h-o-m", "0x1F92D", "face with hand over mouth"},
		{"f-w-o-e-a-h-o-m", "0x1FAE2",
			"face with open eyes and hand over mouth"},
		{"f-w-p-e", "0x1FAE3", "face with peeking eye"},
		{"f-w-t", "0x1F61B", "face with tongue"},
		{"f-w-t-o-j", "0x1F602", "face with tears of joy"},
		{"g-f", "0x1F600", "grinning face"},
		{"g-f-w-b-e", "0x1F603", "grinning face with big eyes"},
		{"g-f-w-s", "0x1F605", "grinning face with sweat"},
		{"g-f-w-s-e", "0x1F604", "grinning face with smiling eyes"},
		{"g-s-f", "0x1F606", "grinning squinting face"},
		{"k-f", "0x1F617", "kissing face"},
		{"k-f-w-c-e", "0x1F61A", "kissing face with closed eyes"},
		{"k-f-w-s-e", "0x1F619", "kissing face with smiling eyes"},
		{"m-f", "0x1FAE0", "melting face"},
		{"m-m-f", "0x1F911", "money-mouth face"},
		{"r-o-t-f-l", "0x1F923", "rolling on the floor laughing"},
		{"s-f", "0x1FAE1", "saluting face"},
		{"s-F", "0x1F92B", "shushing face"},
		{"s-f-w-h", "0x1F607", "smiling face with halo"},
		{"s-f-w-H", "0x1F970", "smiling face with hearts"},
		{"s-f-w-h-e", "0x1F60D", "smiling face with heart-eyes"},
		{"s-f-w-o-h", "0x1F917", "smiling face with open hands"},
		{"s-f-w-s-e", "0x1F60A", "smiling face with smiling eyes"},
		{"s-f-w-t", "0x1F972", "smiling face with tear"},
		{"s-f-w-T", "0x1F61D", "squinting face with tongue"},
		{"s-s", "0x1F929", "star struck"},
		{"s-s-f", "0x1F642", "slightly smiling face"},
		{"t-f", "0x1F914", "thinking face"},
		{"u-d-f", "0x1F643", "upside-down face"},
		{"w-f", "0x1F609", "winking face"},
		{"w-f-w-t", "0x1F61C", "winking face with tongue"},
		{"z-f", "0x1F92A", "zany face"}, {NULL, NULL, NULL}
	};
	return (emoji);
}

/**
 * gemoji - switches emoji styles specified by the parameter passed to it
 *
 * @style: emoji style to use
 *
 * Description: style 'u' for pictorial style
 *		style 'n' for no emoji
 *		style 's' for long string format of emoji
 *		style 'ss' for short string format of emoji
 *
 *		passing wrong option causes the caller program to abort
 *		emoji is disabled by default
 *
 * Return: return nothing
*/

void gemoji(const char *style)
{
	if (strcmp(style, "u") == 0)
		(*__art)->emoji = __GUNICODE;
	else if (strcmp(style, "n") == 0)
		(*__art)->emoji = GNONE;
	else if (strcmp(style, "s") == 0)
		(*__art)->emoji = __GSTRING;
	else if (strcmp(style, "ss") == 0)
		(*__art)->emoji = __GSSTRING;
	else
	{
		gfinal();
		assert(!style);
	}
}
