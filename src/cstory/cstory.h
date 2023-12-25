#ifndef __CSTORY_H
#define __CSTORY_H

#if _CRAFT == 1

#include <ecraft.h>

void ec_start(char *title, char *subtitle, char *description);

elem_t *ec_elem(char *dname, char *fname, char *lname);

int64_t ec_echo(elem_t **elem, char **emoji, char *string, int64_t nmemb);
int64_t ec_recho(elem_t **elem, char **emoji, char *string, int64_t nmemb,
	int64_t ref);

/* TODO */
void ec_add(elem_t **elem, int64_t nmemb);
/* TODO */
void ec_pop(elem_t **elem, int64_t nmemb);

/*
 * below function prototypes are meant for the library itself, so therefore, a
 * user should avoid the use of these functions
*/

void __cs_elem(elem_t *elem);
void __cs_delem(void);
void __cs_decraft(void);

int64_t __cs_load(elem_t **elem, char **emoji, char *string, int64_t nmemb,
	int64_t ref);
int64_t __cs_load_index(ecraft_t *ecraft, elem_t **elem, char **emoji,
	char *string, int64_t nmemb, int64_t ref);
void __cs_update_cli(ecraft_t *ecraft);

void __cs_emoji(char **emoji);
void __cs_pemoji(emoji_t emoji);

void __cs_heading(void);
void __cs_heading_cli(void);

#endif	/* _CRAFT */

#endif	/* __CSTORY_H */
