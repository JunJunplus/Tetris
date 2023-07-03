#include "login.h"


void login_face()
{
    char loginFileName[30] = "000.bmp";
    bmp_show(loginFileName);
    printf("login.c 9 line \n");

    touch_wait_longin(NULL);
    printf("login.c 11 line \n");

    add_user(acc);

    save_user();
}