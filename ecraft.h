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
 * struct echo_s - echo information structure for a craft
 *
 * @message: body to echo to an interface
 * @emoji: emoji
 * @cast: pointer to the cast of a craft
 *
 * Description: this type is meant to be utilised by the library itself
 *		its usage should be avoided in a main program
*/

typedef struct echo_s
{
	char *message;
	char **emoji;
	cast_t *cast;
} echo_t;

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
 * @echo: echo information for the craft
 * @next: pointer to the next craft
 *
 * Description: this type is meant to be utilised by the library itself
 *		its usage should be avoided in a main program
*/

typedef struct ecraft_s
{
	craft_t *craft;
	echo_t **echo;
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
	char *emoji;
	char *unicode;
} emoji_t;

extern ecraft_t *__ecraft;

craft_t *initcraft(char *title, char *format, int interface);

void endcraft(craft_t *craft);
void freecraft(void);

int echo(craft_t *craft, char *message, char *emoji, cast_t *cast);
void recho(craft_t *craft, char *format, char *filename);
echo_t **__echo(echo_t **echo, cast_t *cast, char *message, char *emoji);
void __delecho(echo_t **echo);

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

void __setcli(echo_t **echo);
void __setcli1(echo_t **echo);
void __setcli2(echo_t **echo);
void __setcli3(echo_t **echo);

void __setgui(echo_t **echo);
void __setgui1(echo_t **echo);
void __setgui2(echo_t **echo);

char **__tokenise(char *str, const char *delim, int size);
void __setinterf(craft_t *craft, echo_t **echo);

void __addcraft(ecraft_t *ecraft);
/* meta_t *__mupdate(meta_t *meta, meta_t *temp); */
void __interrupt(void);

#endif	/* __ECRAFT_H */
