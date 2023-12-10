#ifndef __ECRAFT_H
#define __ECRAFT_H

/*
 * variables, macros, and/or functions beginning with double underscore (__)
 * should be avoided by user programs
 *
 * types/typedefs/type definitions designed for the library alone are stated
 * within their documentation
*/

#define __ECRAFT ecraft_t *__ecraft

#define EC_NONE -1	/* none */

/* status */
#define EC_INIT 0	/* init */
#define EC_START 1	/* start */
#define EC_END 2	/* end */
#define EC_DEL 3	/* delete */
#define EC_POP 4	/* pop */
#define EC_FINAL 5	/* final */

/* interface */
#define EC_CLI 0	/* command line interface (index 0) TODO */
#define EC_CLI1 1	/* command line interface (index 1) TODO */
#define EC_CLI2 2	/* command line interface (index 2) TODO */
#define EC_CLI3 3	/* command line interface (index 3) TODO */

#define EC_GUI 4	/* graphical user interface (index 0) TODO */
#define EC_GUI1 5	/* graphical user interface (index 1) TODO */
#define EC_GUI2 6	/* graphical user interface (index 2) TODO */

/* more interface... */

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
 * @body: body content
 * @emoji: emoji
 * @cast: pointer to the cast of a craft
 * @next: pointer to the next meta information
 *
 * Description: this type is meant to be utilised by the library itself
 *		its usage should be avoided in a main program
*/

typedef struct meta_s
{
	char *body;
	char **emoji;
	cast_t *cast;
	struct meta_s *next;
} meta_t;

/**
 * struct craft_s - craft structure
 *
 * @__status: END, START, INIT, DEL
 * @__interface: NONE, CLI, CLI1, CLI2, CLI3, GUI, GUI2, etc
 * @__title: title of the craft
 * @__format: letter, story, chat-story, comic, etc
*/

typedef struct craft_s
{
	int __status, __interface;
	char *__title, *__format;
} craft_t;

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
	craft_t *craft;
	meta_t *meta;
	struct ecraft_s *next;
} ecraft_t;

extern ecraft_t *__ecraft;

void initcraft(void);
void freecraft(void);

craft_t *newcraft(char *title, char *format, int interface);
void startcraft(craft_t *craft);
void endcraft(craft_t *craft);
void popcraft(craft_t *craft);
void delcraft(craft_t *craft);

void pushcraft(craft_t *craft, cast_t *cast, char *buffer, char *emoji);
void pullcraft(craft_t *craft, char *format, char *filename);

void __nullcraft(cast_t *cast, char *buffer, char *emoji);
void __nullcast(craft_t *craft, char *buffer, char *emoji);

void sethead(craft_t *craft, char *header, char *body);
void unsethead(craft_t *craft, char *header);

cast_t *newcast(char *dname, char *fname, char *lname, char *altnames);

void setname(cast_t *cast, char *dname, char *fname, char *lname,
	char *altnames);
void setinfo(cast_t *cast, int height, int weight, int gender,
	char *complxn);

meta_t *__meta(cast_t *cast, char *buffer, char *emoji);

void __setcli(meta_t *meta);
void __setcli1(meta_t *meta);
void __setcli2(meta_t *meta);
void __setcli3(meta_t *meta);

void __setgui(meta_t *meta);
void __setgui1(meta_t *meta);
void __setgui2(meta_t *meta);

char **__tokenise(char *str, const char *delimiter);
int __vinterf(int interface);
void __setinterf(craft_t *craft, meta_t *meta);

#endif	/* __ECRAFT_H */
