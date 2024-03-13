#ifndef __GART_H
#define __GART_H

/*
 * Note: variables, macros, structs, unions, enums, and/or functions beginning
 *	 with double underscore (__) should be avoided by user programs
 *
 *	 tampering with GINIT may break library functionality or introduce
 *	 bugs
*/

#define __GART 0
#define __GCSTORY 1
#define __GSTORY 2
#define __GMUSIC 3

#ifndef _ART
#define _ART __GART	/* default to gart = libgart.so */
#endif	/* _ART */

/* global variables */
#define __ART art_t **__art	/* art descriptor table */

/* general */
#define GNONE 0	/* none */
#define GINIT 1	/* init */
#define GSTART 2	/* start */
#define GEND 3	/* end */

#define GCLI 1	/* command line interface  */
#define GGUI 2	/* graphical user interface */

/* emoji switch */
#define __GUNICODE 1	/* enable real/pictorial emoji */
#define __GSTRING 2	/* enable long string format of emoji */
#define __GSSTRING 3	/* enable short string format of emoji */

#define GBOLD A_BOLD
#define GNORMAL A_NORMAL
#define GUNDERLINE A_UNDERLINE

#include <stdint.h>

#include <ncurses.h>

/* struct __keymap_s - structure for key input
 *
 * @key: key input
 * @func: function to execute when @key is encountered
*/

typedef struct __keymap_s
{
	int key;
	int (*func)(WINDOW *, int, int);
} keymap_t;

/**
 * struct elem_s - data structure for elements of an art
 *
 * @__height: height element
 * @__weight: weight element
 * @__gender: gender element
 * @__dname: display name
 * @__fname: first name
 * @__lname: last name
*/

typedef struct elem_s
{
	int __height, __weight, __gender;
	char *__dname, *__fname, *__lname;
} elem_t;

/**
 * struct __gbuffer - data structure for screen buffer
 *
 * @attrs: attributes like color...
 * @tts: flag for text to speech
 * @ref: reference number of content to load to the interface/screen
 * @string: content to load to the interface/screen
 * @unicode: double pointer to emoji(s) to display
*/

typedef struct __gbuffer_s
{
	int attrs, tts;
	int64_t ref;
	char *string;
	char **unicode;
} gbuffer_t;

/**
 * struct __emoji_s - structure that defines emojis and their respective
 *		      unicode characters
 *
 * @emoji: the emoji
 * @unicode: the unicode representation of @emoji
 * @string: long string representation of @emoji
*/

typedef struct __emoji_s
{
	char *emoji, *unicode, *string;
} emoji_t;

/**
 * struct __art_s - structure for art descriptor table
 *
 * @interf: interface to use for the art
 * @status: return status of the art at runtime
 * @tts: text to speech flag
 * @emoji: emoji flag
 * @vertice: peak value of size of screen buffer
 * @elem_size: size of elem size to allocate
 * @top: integer value representing the top buffer position of the screen
 * @bottom: integer value representing the bottom buffer position of the screen
 * @ref: reference value of each loaded content
 * @title: title for a generative art
 * @subtitle: subtitle for the art
 * @desc: description for the art
 * @elem: pointer to the metadata/element of the generative art
 * @gbuffer: pointer to the screen buffer
 * @pmtwin: prompt window
*/

typedef struct __art_s
{
	int interf, status, tts, emoji;
	int64_t size, index, vertice, elem_size, top, bottom, ref;
	char *title, *subtitle, *desc;
	elem_t **elem;
	gbuffer_t **gbuffer;
	WINDOW *pmtwin;
} art_t;

/* external variables */
extern art_t **__art;

/* include header files for specific libraries */
#include <gcstory.h>

/* function prototypes */
void ginit(void);
void gtts(void);
void gntts(void);
void gemoji(const char *style);
void gfinal(void);
/*
 * void gscroll(int spd, ...);
 * void gconvert(const char *format, const char *filename);
 * void glocal(const char *local);
 * void glang(const char *lang);
*/

/* library only */
void __gtts(char *str);
void __ginterf(void);
char **__gsplit(char *str, const char *delim, int size);
void __prompt_win(void);
keymap_t *__keymap(void);
int __bkspace(WINDOW *win, char *buffer, int ch, int length);
int __gget(WINDOW *win, char *buffer);
void __gprint(const char *type, char *str);
void __gsignal(int signal);
void __scrollup(void);
void __scollup_cli(gbuffer_t *gbuffer);
void __scrolldown(void);
void __scrolldown_cli(gbuffer_t *gbuffer);
emoji_t *__emoji_list(void);
void __key_up(void);

#endif	/* __GART_H */
