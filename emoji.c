#include "ecraft.h"

/**
 * __emojilist - list of emojis, their representation, and unicode values
 *
 * Return: return a pointer to the list of emojis
*/

emoji_t *__emojilist(void)
{
	static emoji_t emoji[] = {
		{"g-f", "0x1F600", "[grinning face]"},
		{"g-f-w-b-e", "0x1F603", "[grinning face with big eyes]"},
		{"g-f-w-s-e", "0x1F604", "[grinning face with smiling eyes]"},
		{"b-f-w-s-e", "0x1F601", "[beaming face with similing eyes]"},
		{"g-s-f", "0x1F606", "[grinning squinting face]"},
		{"g-f-w-s", "0x1F605", "[grinning face with sweat]"},
		{"r-o-t-f-l", "0x1F923", "[rolling on the floor laughing]"},
		{"f-w-t-o-j", "0x1F602", "[face with tears of joy]"},
		{"s-s-f", "0x1F642", "[slightly smiling face]"},
		{"u-d-f", "0x1F643", "[upside-down face]"},
		{"m-f", "0x1FAE0", "[melting face]"},
		{"w-f", "0x1F609", "[winking face]"},

		{"c-f", "0x1F622", "[crying face]"},

		{NULL, NULL, NULL}
	};

	return (emoji);
}
