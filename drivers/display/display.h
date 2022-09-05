#ifndef __DISPLAY_H
#define __DISPLAY_H

void set_cursor_p(int x, int y);
void putch(char c);
void print(const char *str);
void clear_screen(void);

#endif