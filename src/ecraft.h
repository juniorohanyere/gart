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

/* global variables */
#define __EC ec_t *__ec	/* pointer to a structure for flags and placeholders */

/* general */
#define EC_NONE 0	/* none */

#define __EC_INIT 1	/* init */

/* emoji switch */
#define __EC_NEMOJI 0
#define __EC_EMOJI 1	/* display real emoji */
#define __EC_WEMOJI 2	/* word emoji */
#define __EC_SEMOJI 3	/* shortend string emoji */

/* interfaces */
#define EC_CLI 1
#define EC_GUI 2

#include <termbox.h>
#include <ncurses.h>

/**
 * union __interf_u - union for interfaces
 *
 * @cli: command line interface
 * @gui: graphical user interface
*/

typedef union __interf_u
{
	SCREEN *cli;
	void *gui;
} interf_t;

/**
 * struct cast_s - data structure for casts of a craft
 *
 * @__dname: display name
 * @__fname: first name
 * @__lname: last name
 * @__altnames: alternate names
*/

typedef struct cast_s
{
	/* int height, weight, gender, ... */
	char *__dname, *__fname, *__lname, *__altnames;
} cast_t;

/**
 * struct __meta_s - data structure for meta data for a given craft
 *
 * @nmemb: number of cast member to reference
 * @message: message body
 * @emoji: mode at which @message is based upon
 * @cast: cast responsible for @message
*/

typedef struct __meta_s
{
	int nmemb;
	char *message;
	char ***emoji;
	cast_t **cast;
} meta_t;

/**
 * struct ecraft_s - data structure for crafts (placeholder)
 *
 * @__interface: interface of the craft
 * @__title: title for the craft
 * @__subtitle: subtitle for the craft
 * @__type: type of craft
 * @__interf: interface switch for the craft
 * @__cast: cast added to the craft
 * @__meta: metadata for a craft
*/

typedef struct ecraft_s
{
	int __interface;
	char *__title, *__subtitle, *__description, *__type;
	interf_t __interf;
	cast_t **__cast;
	meta_t **__meta;
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

/**
 * struct __ec_s - contains flags and placeholders for ecraft library
 *
 * @cli: flag for command line interface
 * @gui: flag for graphical user interface
 * @tts: flag for text to speech
 * @emoji: flag for emoji
 * @ecraft: top level placeholder for ecraft
 * @pmtscr: prompt screen
*/

typedef struct __ec_s
{
	int cli, gui, tts, emoji;
	ecraft_t **ecraft;
	WINDOW *pmtscr;
} ec_t;

extern ec_t *__ec;

void ec_init(void);
void ec_free(void);

void ec_tts(void);	/* enable text to speech mode */
void ec_ntts(void);	/* disable text to speech mode */
void ec_emoji(const char *option);	/* manipulate emoji modes */

void ec_scroll(...);	/* TODO */

ecraft_t *ec_cstory(char *title, char *subtitle, char *description,
	int interface);
int s_cstory(ecraft_t *cstory, cast_t **cast, char **emoji, char *message,
	int nmemb);
cast_t *c_cstory(ecraft_t *cstory, char *dname, char *fname, char *lname,
	char *altnames);
void cstory_a(ecraft_t *cstory, int h, int e, int b);	/* TODO */
void c_cstory_a(cast_t *cast, int height, int  weight, int gender, ...);
void c_cstory_v(cast_t *cast, int ascent, int tone, int pitch, ...);

/* yet to be implemented */
ecraft_t *ec_story(char *title, char *subtitle, char *description,
	int interface);	/* TODO */
int s_story(ecraft_t *story, ...);	/* TODO */
cast_t *c_story(ecraft_t *story, char *dname, char *fname, char *lname, ...);
void story_a(ecraft_t *story, ...);	/* TODO */
void c_story_a(cast_t *cast, ...);	/* TODO */

/*
 * below functions are meant for the library itself, so therefore, a user
 * should avoid the use of these functions
*/

void __ec_printf(SCREEN *screen, const char *type, char *str);
void __ec_tts(char *str);

void __set_interf(ecraft_t *craft);
char **__tokenise(char *str, const char *delim, int size);
void __interrupt(SCREEN *screen, char *tts_msg);
void __free_craft(ecraft_t *craft);
void __prompt_win(void);
emoji_t *__emoji_list(void);
void __scr_cleanup(void);

void __c_add_cstory(ecraft_t *cstory, cast_t *cast);
void __c_del_cstory(cast_t **cast);

void __s_cstory(ecraft_t *cstory, meta_t *meta, int ncast);
void __s_cli_cstory(ecraft_t *cstory, meta_t *meta, int ncast);
void __emoji_cstory(SCREEN *screen, char **emoji);
void __emode_cstory(SCREEN *screen, emoji_t emoji);

void __m_del_cstory(meta_t **meta);
meta_t **__m_add_cstory(meta_t **meta, cast_t **cast, char **emoji,
	char *message, int nmemb);

void __h_cstory(ecraft_t *cstory);
void __free_cstory(ecraft_t *cstory);

#endif	/* __ECRAFT_H */
