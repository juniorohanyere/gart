#ifndef __ECRAFT_H
#define __ECRAFT_H

#define __EC_CSTORY ec_cstory_t **__ec_cstory

#include <ncurses.h>

typedef struct __ec_cstory_s
{
	int interface;
	char *title, subtitle;
} ec_cstory_t;

typedef struct __ecraft_s
{
	int cstory, story, comic;
} ecraft_t;

extern ec_cstory_t **__ec_cstory;

void ec_init(void);
int ec_cstory(char *title, char *subtitle, interface);

#endif	/* __ECRAFT_H */
