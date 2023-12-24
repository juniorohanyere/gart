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
#define __EC_WEMOJI 2	/* word emoji */
#define __EC_SEMOJI 3	/* shortend string emoji */

#include <stdint.h>

#include <ncurses.h>

/**
 * struct elem_s - data structure for casts of a craft
 *
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
 * struct ecraft_s - data structure for crafts (placeholder)
 *
 * @__interface: interface of the craft
 * @__type: type of craft
 * @__interf: interface switch for the craft
 * @__cast: cast added to the craft
 * @__meta: metadata for a craft
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
 * @string: human readable string representation
*/

typedef struct __emoji_s
{
	char *emoji, *unicode, *string;
} emoji_t;

typedef union __scr_u
{
	void *gui;	/* TODO */
	SCREEN *cli;
} scr_t;

/**
 * struct __ec_s - contains flags and placeholders for ecraft library
 *
 * @title: title for the craft
 * @subtitle: subtitle for the craft
 * @tts: flag for text to speech
 * @emoji: flag for emoji
 * @ecraft: top level placeholder for ecraft
 * @pmtscr: prompt screen
*/

typedef struct __ec_s
{
	int interf, status, tts, emoji;
	int64_t top;
	char *title, *subtitle, *desc;
	scr_t screen;
	elem_t **elem;
	ecraft_t **ecraft;
	WINDOW *pmtscr;
} ec_t;

extern ec_t *__ec;

/* include header file(s) for specific craft(s) */

#if _CRAFT == 1	/* chat story or cstory => libcstory.* */
#include <cstory.h>
#endif	/* _CRAFT == 1 */

/*
 * some function prototypes are noted by commenting them out
 * they are marked with '...' as the only parameter
 * they can be found in header file(s) for some/a given craft(s)
*/

void ec_init(const int interface);
void ec_free(void);

/* void ec_start(...); */
/* void ec_create(...); */
void ec_end(void);

void ec_tts(void);	/* enable text to speech mode */
void ec_ntts(void);	/* disable text to speech mode */

void ec_emoji(const char *mode);	/* manipulate emoji modes */

void ec_scroll(int spd, ...);	/* TODO */

/* int64_t ec_echo(...); */
/* int64_t ec_recho(...); */

void ec_add(elem_t **elem, int64_t nmemb);
void ec_pop(elem_t **elem, int64_t nmemb);

void ec_update(void);

void ec_print(const char *format, const char *filename);

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

void __ec_cleanup(void);

#endif	/* __ECRAFT_H */
