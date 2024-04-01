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
#define __ART gart_t **__art	/* art descriptor table */

/* general */
#define GNONE 0	/* none */
#define GINIT 1	/* init */
#define GSTART 2	/* start */
#define GEND 3	/* end */

/* interfaces */
#define __GCLI 1	/* command line interface  */
#define __GGUI 2	/* graphical user interface */

#ifndef _INTERFACE
#define _INTERFACE GNONE	/* outputs a .g.json file */
#endif	/* _INTERFACE */

/* emoji switch */
#define __GUNICODE 1	/* enable real/pictorial emoji */
#define __GSTRING 2	/* enable long string format of emoji */
#define __GSSTRING 3	/* enable short string format of emoji */

/* text attributes */
#define GBOLD A_BOLD
#define GNORMAL A_NORMAL
#define GUNDERLINE A_UNDERLINE

/* dump buffer */
#ifndef _DBUFFER
#define _DBUFFER 1024
#endif	/* _DBUFFER */

#include <stdint.h>

#include <ncurses.h>

/* struct __gkey_s - structure for key input
 *
 * @key: key input
 * @func: function to execute when @key is encountered
*/

typedef struct __gkey_s
{
	int key;
	int (*func)(WINDOW *, int, int);
} gkey_t;

/**
 * struct glbl_s - data structure for labels of an art
 *
 * @__height: height of label
 * @__weight: weight of label
 * @__gender: gender of label
 * @__dname: display name of label
 * @__fname: first name of label
 * @__lname: last name of label
*/

typedef struct __glbl_s
{
	int __height, __weight, __gender;
	char *__dname, *__fname, *__lname;
} glbl_t;

/**
 * struct __gscr - screen descriptor table
 *
 * @attrs: attributes like color...
 * @tts: flag for text to speech
 * @ref: reference number of content to load to the interface/screen
 * @string: content to load to the interface/screen
 * @unicode: double pointer to emoji(s) to display
*/

typedef struct __gscr_s
{
	int size, ts;
	int *attrs, *tts;
	int64_t id;
	char **string, **emoji;
} gscr_t;

/**
 * struct __gemoji_s - structure that defines emojis and their respective
 *		      unicode characters
 *
 * @emoji: the emoji
 * @unicode: the unicode representation of @emoji
 * @string: long string representation of @emoji
*/

typedef struct __gemoji_s
{
	char *emoji, *unicode, *string;
} gemoji_t;

/**
 * struct __gart_s - structure for art descriptor table
 *
 * @interf: interface to use for the art
 * @status: return status of the art at runtime
 * @tts: text to speech flag
 * @emoji: emoji flag
 * @size: array size
 * @index: current array index being accessed
 * @lbl_size: array size of @lbl to allocate
 * @dbuf: dump buffer
 * @sbuf: screen buffer
 * @lbl: pointer to array of labels of the generative art
 * @pmtwin: prompt window
 * @vertice: peak value of size of screen buffer
 * @top: integer value representing the top buffer position of the screen
 * @bottom: integer value representing the bottom buffer position of the screen
 * @ref: reference value of each loaded content
 * @title: title for a generative art
 * @subtitle: subtitle for the art
 * @desc: description for the art
 * @scr: pointer to the screen buffer
*/

typedef struct __gart_s
{
	/* assigned to only index 0 of (__gart_s **) for optimization */
	int interf, status, tts, emoji;
	int64_t size, index, lbl_size;
	char *dbuf, sbuf;
	glbl_t **lbl;
	WINDOW *pmtwin;

	/* assigned to any index of (__gart_s **) */
	int64_t vertice, top, bottom, ref;
	char *title, *subtitle, *desc;
	gscr_t **scr;
} gart_t;

/* external variables */
extern gart_t **__art;

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
char **__gwsplit(char *str, const char *delim, int size);
void __gpmtwin(void);
gkey_t *__gkey(void);
int __gbkspace(WINDOW *win, char *buffer, int ch, int length);
int __gget(WINDOW *win, char *buffer);
void __gprint(const char *type, char *str);
void __gsignal(int signal);
void __gscrlup(void);
void __gscrlup_cli(gscr_t *scr);
void __gscrldown(void);
void __gscrldown_cli(gscr_t *scr);
gemoji_t *__glemoji(void);
void __gkey_up(void);

#endif	/* __GART_H */
