#include "console.h"

int
getch() {
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}

int
getche() {
    int ch;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}

void
printc(char ch, int repeat, bool nextLine) {
    for (int i = 0; i < repeat; i++) {
        printf("%c", ch);
    }

    if (nextLine) {
        printf("\n");
    }
}

char *
input(const char *msg, int len, bool pass) {
    int i = 0;
    char *tmp = (char *) malloc(INT_MAX * sizeof(char)),
            *str, ch;

    if (tmp == NULL) {
        perror("Memory allocation failed.\n");
        exit(EXIT_SUCCESS);
    }

    printf("%s", msg);
    while (true) {
        if (i == len) {
            break;
        }

        ch = getch();
        if (ch == UNX_ENTER || ch == TAB) {
            break;
        } else if (ch == UNX_BKSP) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            *(tmp + i++) = ch;

            if (pass) {
                printf("* \b");
            } else {
                printf("%c", ch);
            }
        }
    }

    *(tmp + i) = '\0';

    str = (char *) malloc(i * sizeof(char));
    strncpy(str, tmp, i);

    free(tmp);
    printf("\n");

    return str;
}

void
clrscr() {
    system("clear");
}

void
press_enter() {
    printf("Press enter to continue!...");
    getchar();
}

void
press_key() {
    printf("Press any key to continue!...");
    getch();

    printf("\n");
}

int
sure(const char *msg, bool repeat, bool wait) {
    char *tmp = NULL, ch;
    int rs = 0;

    do {
        tmp = (char *) malloc(INT_MAX * sizeof(char));

        if (tmp == NULL) {
            perror("Memory allocation failed.\n");
            exit(EXIT_SUCCESS);
        }

        strcpy(tmp, msg);
        if (tmp[strlen(tmp) - 1] == '?') {
            strcat(tmp, " [Y/N]: ");
        } else {
            strcat(tmp, "? [Y/N]: ");
        }

        printf("%s", tmp);

        if (wait) {
            ch = getchar();
        } else {
            ch = getche();
        }

        printf("\n");

        if (ch == 'y') {
            rs = 1;
            break;
        } else if (ch == 'n') {
            rs = 0;
            break;
        } else {
            rs = -1;
        }
    } while (repeat);

    free(tmp);

    return rs;
}

int
ask(const char *msg, const char *opt[], int opt_len, bool repeat) {
    int i = 0;

    do {
        char *tmp = (char *) malloc(INT_MAX * sizeof(char)),
                *ans = (char *) malloc(INT_MAX * sizeof(char));

        if (tmp == NULL || ans == NULL) {
            perror("Memory allocation failed.\n");
            exit(EXIT_SUCCESS);
        }

        strcpy(tmp, msg);
        strcat(tmp, " [");

        for (i = 0; i < opt_len; i++) {
            strcat(tmp, opt[i]);

            if (i + 1 < opt_len) {
                strcat(tmp, ",");
            }
        }

        strcat(tmp, "]: ");

        printf("%s", tmp);
        fgets(ans, INT_MAX, stdin);

        /*delete new line char at the end */
        ans[strcspn(ans, "\n")] = 0;

        for (i = 0; i < opt_len; i++) {
            if (strcmp(opt[i], ans) == 0) {
                repeat = false;
                break;
            }
        }

        free(tmp);
        free(ans);
    } while (repeat);

    return i;
}


void
gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}

void
pok(const char *msg) {
    printf("%s%s%s\n", ANSI_COLOR_GREEN, msg, ANSI_COLOR_RESET);
}

void
perr(const char *msg) {
    char *tmp = (char *) malloc(INT_MAX * sizeof(char));

    if (tmp == NULL) {
        perror("Memory allocation failed.\n");
        exit(EXIT_SUCCESS);
    }

    strcpy(tmp, ANSI_COLOR_RED);
    strcat(tmp, msg);
    strcat(tmp, ANSI_COLOR_RESET);

    perror(tmp);
    free(tmp);
}

void
pwarn(const char *msg) {
    printf("%s%s%s\n", ANSI_COLOR_YELLOW, msg, ANSI_COLOR_RESET);
}

void
pinfo(const char *msg) {
    printf("%s%s%s\n", ANSI_COLOR_BLUE, msg, ANSI_COLOR_RESET);
}
