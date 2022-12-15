#ifndef CONSOLE_H
#define CONSOLE_H

#define UNX_ENTER 10
#define UNX_BKSP 127
#define WIN_ENTER 13
#define WIN_BKSP 8
#define TAB 8

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

struct termios oldattr, newattr;

int getch();
int getche();

int sure(const char *msg, bool repeat, bool wait);
int ask(const char *msg, const char *opt[], int opt_len, bool repeat);

char* input(const char *msg, int len, bool pass);

void printc(char ch, int repeat, bool nextLine);
void clrscr();
void press_enter();
void press_key();
void gotoxy(int x, int y);
void pok(const char *msg);
void perr(const char *msg);
void pwarn(const char *msg);
void pinfo(const char *msg);



#endif
