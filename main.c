#include "console.h"

/*Created by darkDev9 */

int main() {
    char *arr = input("password: ", INT_MAX, false);
    printc('-', 40, true);

    printf("arr: %s\n", arr);
    printf("size of arr: %ld\n", strlen(arr));

    press_enter();
    press_key();

    printf("result: %d\n", sure("are you sure yo execute?", true, false));

    const char *opt[] = {
            "yes",
            "no",
            "sure"
    };

    printf("result: %d\n", ask("Select one option: ", opt, 3, true));
    gotoxy(50, 30);
    printf("i am here\n");

    perr("message");
    pok("message");
    pwarn("message");
    pinfo("message");

    free(arr);
    return 0;
}
