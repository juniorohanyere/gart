#ifndef __GCSTORY_H
#define __GCSTORY_H

#if _ART == __GCSTORY

#include <gart.h>

int64_t gstart(char *title, char *subtitle, char *description);

elem_t *gcreate(char *dname, char *fname, char *lname);

int64_t gload(elem_t *elem, char *emoji, char *string);
int64_t gtag(elem_t *elem, elem_t *tag, char *emoji, char *string);
void gfinal(void);
/*
 * int64_t gpack(elem_t **elemp, elem_t *elem, char *emoji);
 * int64_t gpop(elem_t **elemp, int64_t ref);
*/

/* library only function prototypes */
int64_t __gload(elem_t *elem, char *emoji, char *string);
int64_t __gload_1(gbuffer_t **gbuffer, elem_t *elem, char *emoji, char *string);
void __gload_2(gbuffer_t **gbuffer, char *string, int64_t ref);
void __gread(int ref);
void __gexec(char *cmd);
void __gadd(elem_t *elem);
void __delem(void);
void __dgbuffer(int64_t index);
void __gmvprint(const char *type, char *str, int x, int y);
void __gemoji(char *emoji, int64_t index);
void __pemoji(emoji_t emoji);
void __ghead(void);
void __gfinal(void);
void __key_up(void);

#endif	/* _ART */

#endif	/* __GCSTORY_H */
