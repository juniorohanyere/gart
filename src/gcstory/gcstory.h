#ifndef __GCSTORY_H
#define __GCSTORY_H

#if _ART == __GCSTORY

#include <gart.h>

int64_t gstart(char *title, char *subtitle, char *description);

int64_t glabel(char *dname, char *fname, char *lname);

void gdump(const char *str);
int64_t gload(int64_t lbl, const char *str, int ts);
int64_t gtag(int64_t lbl, int64_t tag, char *emoji, char *string);

void gfinal(void);
/*
 * int64_t gpack(elem_t **elemp, elem_t *elem, char *emoji);
 * int64_t gpop(elem_t **elemp, int64_t ref);
*/

/* library only function prototypes */
int64_t __gload(glbl_t *lbl, char *emoji, char *string);
int64_t __gload_1(gscr_t **scr, glbl_t *lbl, char *emoji, char *string);
void __gload_2(gscr_t **scr, char *string, int64_t ref);
void __gread(int ref);
void __gexec(char *cmd);
int64_t __gadd(glbl_t *lbl);
void __glbl_free(void);
void __gscr_free(int64_t index);
void __gmvprint(const char *type, char *str, int x, int y);
void __gemoji(char *emoji, int64_t index);
void __gpemoji(gemoji_t emoji);
void __ghead(void);
void __gfinal(void);
void __gkey_up(void);

#endif	/* _ART */

#endif	/* __GCSTORY_H */
