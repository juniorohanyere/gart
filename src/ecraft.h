#ifndef __ECRAFT_H
#define __ECRAFT_H

#define __ECRAFT ecraft_t **__ecraft

#define __EC_CLI int __cli
#define __EC_GUI int  __gui

#define EC_NONE -1
#define __EC_INIT 0

#define EC_CLI 1
#define EC_GUI 2

#include <ncurses.h>
#include <stdarg.h>

typedef union __interf_u
{
	SCREEN *cli;
	void *gui;
} interf_t;

typedef struct cast_s
{
	/* int height, weight, gender, ... */
	char *__dname, *__fname, *__lname, *__altnames;
} cast_t;

typedef struct __meta_s
{
	char *message;
	char **emoji;
	cast_t *cast;
} meta_t;

typedef struct ecraft_s
{
	int __interface;
	char *__title, *__subtitle, *__type;
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
 *
 * Description: this type definition is meant to be utilised by the library
 *		itself its usage should be avoided by the user's program
*/

typedef struct __emoji_s
{
	char *rep, *unicode, *emoji;
} emoji_t;

extern ecraft_t **__ecraft;

extern int __cli;
extern int __gui;

ecraft_t *ec_cstory(char *title, char *subtitle, int interface);
void __set_interf(ecraft_t *craft);
int stage(...);

void __c_add_cstory(ecraft_t *cstory, cast_t *cast);
char **__tokenise(char *str, const char *delim, int size);
meta_t **__m_add_cstory(meta_t **meta, cast_t *cast, char *message,
	char *emoji);
void __s_cstory(ecraft_t *cstory, meta_t *meta);
void __s_cli_cstory(ecraft_t *cstory, meta_t *meta);
emoji_t *__emoji_list(void);
void __ec_printf(SCREEN *screen, const char *type, char *str);
void __interrupt(SCREEN *screen);
void freecraft(void);
cast_t *c_cstory(ecraft_t *cstory, char *dname, char *fname, char *lname,
	char *altnames);
int s_cstory(ecraft_t *cstory, cast_t *cast, char *message, char *emoji);
void __m_del_cstory(meta_t **meta);
void __c_del_cstory(cast_t **cast);
void __freecraft(ecraft_t *craft);

/* int stage(cast_t *cast, */

#endif	/* __ECRAFT_H */
