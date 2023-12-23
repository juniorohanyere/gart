#ifndef __CSTORY_H
#define __CSTORY_H

#include <ecraft.h>

void ec_start(char *title, char *subtitle, char *description);

void ec_create(elem_t *elem, char *dname, char *fname, char *lname);

int64_t ec_echo(elem_t **elem, char **emoji, char *string, int64_t nmemb);
int64_t ec_recho(elem_t **elem, char **emoji, char *string, int64_t nmemb,
	int64_t ref);

/*
 * below function prototypes are meant for the library itself, so therefore, a
 * user should avoid the use of these functions
*/

int64_t __cs_update(elem_t **elem, char **emoji, char *string, int64_t nmemb,
	int64_t ref);
void __cs_display(ecraft_t *ecraft);
void __cs_display_cli(ecraft_t *ecraft);

void __cs_emoji(char **emoji);
void __cs_pemoji(emoji_t emoji);

void __cs_heading(void);
void __cs_heading_cli(void);

#endif	/* __CSTORY_H */
