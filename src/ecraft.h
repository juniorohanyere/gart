#ifndef __ECRAFT_H
#define __ECRAFT_H

/*
 * Note: variables, macros, structs, unions, enums, and/or functions
 *	 beginning with double underscore (__) should be avoided by user
 *	 programs
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
#define __ECRAFT ecraft_t **__ecraft	/* placeholder */

#define __PMTSCR WINDOW *__pmtscr	/* prompt screen */

#define __EC_CLI int __cli	/* flag for command line interface */
#define __EC_GUI int  __gui	/* flag for graphical user interface */

/* general */
#define EC_NONE -1	/* none */
#define __EC_INIT 0	/* init */

#define __PMT_HEIGHT 1	/* prompt window height */

/* Note: tampering with __EC_INIT may break the library or introduce bugs */

/* interfaces */
#define EC_CLI 1
#define EC_GUI 2

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
 * @message: message body
 * @emoji: mode at which @message is based upon
 * @cast: cast responsible for @message
*/

typedef struct __meta_s
{
	char *message;
	char **emoji;
	cast_t *cast;
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
 * @rep: end user representation of the emoji
 * @unicode: the unicode representation of @emoji
 * @emoji: the emoji
*/

typedef struct __emoji_s
{
	char *rep, *unicode, *emoji;
} emoji_t;

extern ecraft_t **__ecraft;

extern int __cli;
extern int __gui;

extern WINDOW *__pmtscr;

ecraft_t *ec_cstory(char *title, char *subtitle, char *description,
	int interface);
void ec_free(void);

int s_cstory(ecraft_t *cstory, cast_t *cast, char *message, char *emoji);
cast_t *c_cstory(ecraft_t *cstory, char *dname, char *fname, char *lname,
	char *altnames);

/*
 * below functions are meant for the library itself, so therefore, a user
 * should avoid the use of these functions
*/

void __ec_printf(SCREEN *screen, const char *type, char *str);
void __set_interf(ecraft_t *craft);
char **__tokenise(char *str, const char *delim, int size);
void __interrupt(SCREEN *screen);
void __free_craft(ecraft_t *craft);
void __prompt_win(void);

void __c_add_cstory(ecraft_t *cstory, cast_t *cast);
void __c_del_cstory(cast_t **cast);
void __s_cstory(ecraft_t *cstory, meta_t *meta);
void __s_cli_cstory(ecraft_t *cstory, meta_t *meta);
void __m_del_cstory(meta_t **meta);
meta_t **__m_add_cstory(meta_t **meta, cast_t *cast, char *message,
	char *emoji);
void __free_cstory(ecraft_t *cstory);

emoji_t *__emoji_list(void);

#endif	/* __ECRAFT_H */
