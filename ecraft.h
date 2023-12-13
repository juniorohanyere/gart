#ifndef __ECRAFT_H
#define __ECRAFT_H

/*
 * variables, macros, and/or functions beginning with double underscore (__)
 * should be avoided by user programs
 *
 * types/typedefs/type definitions designed for the library alone are stated
 * within their documentation
*/

/* global variables */
#define __ECRAFT ecraft_t *__ecraft
#define __EC_CLI int __cli
#define __EC_GUI int __gui

/* general */
#define EC_NONE -1	/* none */
#define __EC_INIT 0	/* init */

/* interfaces */
#define EC_CLI 1	/* command line interface TODO */
#define EC_GUI 2	/* graphical user interface TODO */

#include <ncurses.h>

/**
 * struct cast_s - cast structure for a craft
 *
 * @__height: height of the cast
 * @__weight: weight of the cast
 * @__gender: gender of the cast
 * @__dname: display name of the cast
 * @__fname: first name of the cast
 * @__lname: last name of the cast
 * @__altnames: alternate names of the cast
 * @__cmplxn: complexion of the cast
 *
 * Description: contains information for a cast (attributes and/or actions)
*/

typedef struct cast_s
{
	int __height, __weight, __gender;
	char *__dname, *__fname, *__lname, *__altnames, *__cmplxn;
} cast_t;

/**
 * struct meta_s - meta information structure for a craft
 *
 * @message: message to echo to an interface
 * @emoji: emoji
 * @cast: pointer to the cast of a craft
 *
 * Description: this type is meant to be utilised by the library itself
 *		its usage should be avoided in a main program
*/

typedef struct meta_s
{
	char *message;
	char **emoji;
	cast_t *cast;
} meta_t;

/**
 * struct craft_s - craft structure
 *
 * @__interface: NONE, CLI, CLI1, CLI2, CLI3, GUI, GUI2, etc
 * @__title: title of the craft
 * @__format: letter, story, chat-story, comic, etc
*/

typedef struct craft_s
{
	int __interface;
	char *__title, *__format;
} craft_t;

/**
 * union interf_u - type definition for an interface union
 *
 * @cli: command line interface
 * @gui: graphical user interface
 *
*/

typedef union interf_u
{
	SCREEN *cli;
	void *gui;	/* TODO: not yet implemeted, need to focus on cli */
} interf_t;

/**
 * struct ecraft_s - placeholder struct for crafts
 *
 * @craft: pointer to a craft
 * @meta: meta information for the craft
 * @next: pointer to the next craft
 *
 * Description: this type is meant to be utilised by the library itself
 *		its usage should be avoided in a main program
*/

typedef struct ecraft_s
{
	interf_t interf;
	craft_t *craft;
	meta_t **meta;
	struct ecraft_s *next;
} ecraft_t;

/**
 * struct emoji_s - struture that defines emojis and their unicode
 *		    characters
 *
 * @emoji: the emoji
 * @unicode: the unicode representation of @emoji
 *
*/

typedef struct emoji_s
{
	char *rep, *unicode, *emoji;
} emoji_t;

extern ecraft_t *__ecraft;
extern int __cli;
extern int __gui;

craft_t *initcraft(char *title, char *format, int interface);

void endcraft(craft_t *craft);
void freecraft(void);

int stage(craft_t *craft, char *message, char *emoji, cast_t *cast);
void rstage(craft_t *craft, char *format, char *filename);
meta_t **__meta(meta_t **meta, cast_t *cast, char *message, char *emoji);
void __delmeta(meta_t **meta);

void __nullcraft(cast_t *cast, char *message, char *emoji);
void __nullcast(craft_t *craft, char *message, char *emoji);

void sethead(craft_t *craft, char *header, char *message);
void unsethead(craft_t *craft, char *header);

cast_t *newcast(char *dname, char *fname, char *lname, char *altnames);
void __delcast(cast_t *cast);

void setname(cast_t *cast, char *dname, char *fname, char *lname,
	char *altnames);
void setinfo(cast_t *cast, int height, int weight, int gender,
	char *complxn);

void __stage(ecraft_t *ecraft);
void __stagecli(ecraft_t *ecraft);
void __stagegui(ecraft_t *ecraft);

char **__tokenise(char *str, const char *delim, int size);
void __setinterf(ecraft_t *ecraft);

void __ecprintf(SCREEN *screen, char *type, char *str);
void __interrupt(SCREEN *screen);

void __addcraft(ecraft_t *ecraft);

#endif	/* __ECRAFT_H */
