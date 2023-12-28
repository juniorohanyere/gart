#ifndef __ECRAFT_H
#define __ECRAFT_H

/*
 * Note: variables, macros, structs, unions, enums, and/or functions
 *	 beginning with double underscore (__) should be avoided by user
 *	 programs
 *	 tampering with __EC_INIT may break the library or introduce bugs
 *
 * Prefixing - variables, functions, macros, structs, unions, and/or enums
 *	       beginning with <prefix>_ or __<prefix>_ in the case of
 *	       library-only variables, or functions, or the likes, are
 *	       described below
 * ec_, __ec_: ecraft/e-craft/electronic craft
 *	       create a new craft usually of ecraft_t data type
 * s_, __s_: stage, stage/display an input buffer to a specified interface
 * c_, __c_: cast, create a new cast for a given craft
 * m_, __m_: meta, create/update a meta data for a given craft
*/

#ifndef _CRAFT
#define _CRAFT 0	/* ecraft => libecraft.* */
#endif	/* _CRAFT */

/* global variables */
#define __EC ec_t *__ec	/* pointer to a structure for flags and placeholders */

/* general */
#define EC_NONE 0	/* none */

#define EC_INIT 1	/* init */
#define EC_START 2	/* start */
#define EC_END 3	/* end */

#define EC_CLI 1	/* command line interface */
#define EC_GUI 2	/* graphical user interface */

/* emoji switch */
#define __EC_EMOJI 1	/* display real emoji */
#define __EC_LEMOJI 2	/* long string format of emoji */
#define __EC_SEMOJI 3	/* short string format of emoji */

#include <stdint.h>

#include <ncurses.h>

/**
 * struct __keymap_s - structure for key input
 *
 * @key: key input
 * @func: function to execute when @key is encountered
*/

typedef struct __keymap_s
{
	int key;
	int (*func)(char *buffer);
} keymap_t;

/**
 * struct elem_s - data structure for casts of a craft
 *
 * @__height: height of the element
 * @__weight: weight of the element
 * @__gender: gender of the element
 * @__dname: display name of the element
 * @__fname: first name of the element
 * @__lname: last name of the element
*/

typedef struct elem_s
{
	int __height, __weight, __gender;
	char *__dname, *__fname, *__lname;
} elem_t;

/**
 * struct __ecraft_s - data structure for crafts (placeholder)
 *
 * @nmemb: number of elem and/or emoji pointers to access/reference
 * @ref: reference number of content to re-echo to an interface
 * @string: content to be displayed onto a screen
 * @emoji: tripple pointer to emoji(s) to display
 * @elem: element responsible for @string
*/

typedef struct __ecraft_s
{
	int64_t nmemb, ref;
	char *string;
	char ***emoji;
	elem_t **elem;
} ecraft_t;

/**
 * struct __emoji_s - struture that defines emojis and their unicode
 *		    characters
 *
 * @emoji: the emoji
 * @unicode: the unicode representation of @emoji
 * @string: human readable/long string representation/format
*/

typedef struct __emoji_s
{
	char *emoji, *unicode, *string;
} emoji_t;

/**
 * union __scr_u - union for the interface of the chat story
 *
 * @gui: graphical user interface
 * @cli: command line interface
*/

typedef union __scr_u
{
	void *gui;	/* TODO */
	SCREEN *cli;
} scr_t;

/**
 * struct __ec_s - contains flags and placeholders for ecraft library
 *
 * @interf: interface of the craft
 * @status: return status of the craft at runtime
 * @tts: text to speech flag
 * @emoji: emoji flag
 * @top: integer value representing the top buffer position of a screen
 * @bottom: integer value representing the bottom buffer position of a
 *	    screen
 * @title: title for the craft
 * @subtitle: subtitle for the craft
 * @desc: description for the craft
 * @screen: screen to print to
 * @elem: pointer to elements of a craft
 * @ecraft: pointer to the meta data for a craft
 * @pmtscr: prompt screen
*/

typedef struct __ec_s
{
	int interf, status, tts, emoji;
	int64_t top, bottom;
	char *title, *subtitle, *desc;
	scr_t screen;
	elem_t **elem;
	ecraft_t **ecraft;
	WINDOW *pmtscr;
} ec_t;

/* externals */

extern ec_t *__ec;

/* include header file(s) for specific craft(s) */

#include <cstory.h>

void ec_init(const int interface);

/* enable text to speech mode */
void ec_tts(void);
/* disable text to speech mode */
void ec_ntts(void);

/* manipulate emoji modes */
void ec_emoji(const char *mode);

void ec_final(void);

/* TODO */
void ec_scroll(int spd, ...);
void ec_convert(const char *format, const char *filename);
void ec_local(const char *local);
void ec_lang(const char *lang);

/*
 * below function prototypes are meant for the library itself, so therefore, a
 * user should avoid the use of these functions
*/

void __ec_printf(const char *type, char *str);
void __ec_tts(char *tts_msg);

void __ec_interf(void);
char **__ec_split(char *str, const char *delim, int size);
void __ec_interrupt(char *tts_msg);
void __ec_pmtwin(void);

emoji_t *__ec_lemoji(void);
int __ec_nl(char *buffer);
keymap_t *__ec_keymap(void);
int __ec_getstr(WINDOW *win, char *buffer);

#endif	/* __ECRAFT_H */
