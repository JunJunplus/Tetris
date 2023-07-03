#include "touch.h"

typedef struct block block_t;

int touchFd;
struct input_event inEv;
touchEvInfo_t evInfo;
touchPos_t firstPos;
sys_mode_t sys_mode;
char acc[20];
char passwd[20];
font *f;
int num;
bool flag;

void touch_init()
{
    touchFd = open("/dev/input/event0", O_RDWR);
    if (touchFd == -1)
    {
        perror("open event0 fail");
        return;
    }
    // 初始化信息
    // ioctl(touchFd, FIONBIO);

    evInfo.endPos.x = evInfo.endPos.y = 0;
    evInfo.startPos.x = evInfo.startPos.y = 0;
    evInfo.startTime.tv_sec = evInfo.endTime.tv_sec = 0;
    evInfo.startTime.tv_nsec = evInfo.endTime.tv_nsec = 0;
    evInfo.evKind = NON;
    memset(acc, 0, 20);
    memset(passwd, 0, 20);
    num = 0;
    sys_mode = NON;
    flag = true;
    f = init_font(60);
    return;
}

void touch_destory()
{
    close(touchFd);
}

void start_press()
{
    // 无事件发生 && types:3 code:0 则存储开始x
    if (evInfo.evKind == NON && inEv.type == EV_ABS && inEv.code == ABS_X)
    {
        evInfo.startPos.x = inEv.value;
    }
    // 无事件发生 && types:3 code:1 则存储开始y
    if (evInfo.evKind == NON && inEv.type == EV_ABS && inEv.code == ABS_Y)
    {
        evInfo.startPos.y = inEv.value;
    }
    // 无事件发生 && types:1 code:330 value = 1 则按键被按下
    if (evInfo.evKind == NON && inEv.type == EV_KEY && inEv.code == BTN_TOUCH && inEv.value > 0)
    {
        evInfo.evKind = PRESS;
    }
}

void start_lossen()
{
    // 按键被按下 && types:3 code:0 value:326   则记录结束x
    if (evInfo.evKind == PRESS && inEv.type == EV_ABS && inEv.code == ABS_X)
    {
        evInfo.endPos.x = inEv.value;
    }
    // 按键被按下 && types:3 code:1 value:326   则记录结束y
    if (evInfo.evKind == PRESS && inEv.type == EV_ABS && inEv.code == ABS_Y)
    {
        evInfo.endPos.y = inEv.value;
    }
    // 按键被按下 && types:1 code:330 value:0    松开 记录结束时间
    if (evInfo.evKind == PRESS && inEv.type == EV_KEY && inEv.code == BTN_TOUCH && inEv.value == 0)
    {
        evInfo.evKind = LOOSEN;
    }
}

// 一次完整事件
bool complete_event()
{
    if (evInfo.evKind == LOOSEN)
    {
        if ((evInfo.endPos.x == 0 && evInfo.endPos.x == 0))
        {
            evInfo.evKind = CLICK;
            return true;
        }
    }
    return false;
}

int trigger_touch_event()
{
    evInfo.endPos.x = evInfo.endPos.y = 0;
    evInfo.startPos.x = evInfo.startPos.y = 0;
    evInfo.evKind = NON;
    while (1)
    {
        read(touchFd, &inEv, sizeof(inEv));
        start_press();
        start_lossen();
        if (complete_event())
        {
            break;
        }
    }
    return evInfo.evKind;
}

// void *login_touch(void *arg)
// {
//     while (1)
//     {
//         if (trigger_touch_event() == CLICK)
//         {
//             double x = evInfo.startPos.x * 800.0 / 1024.0;
//             double y = evInfo.startPos.y * 480.0 / 600.0;

//             if (x >= 0 && x < 160 && y >= 0 && y < 120)
//             {
//                 gameOpt = 1;
//             }
//             else if (x >= 0 && x < 160 && y > 120 && y < 240)
//             {
//                 gameOpt = 2;
//             }
//             else if (x >= 0 && x < 160 && y > 240 && y < 360)
//             {
//                 gameOpt = 3;
//             }
//             else if (x >= 0 && x < 160 && y > 360 && y < 480)
//             {
//                 gameOpt = 4;
//             }
//             else
//             {
//                 gameOpt = 0;
//             }
//             printf("gameOpt %d\n", gameOpt);
//         }
//     }
// }

void *touch_wait(void *arg)
{
    // 1、打开触摸屏文件
    // int fd = open("/dev/input/event0", O_RDWR);
    // if (fd == -1)
    // {
    //     perror("open error");
    //     return NULL;
    // }
    // 2、读取用手点击的触摸屏数据
    touchPos_t pos;
    while (1)
    {
        struct input_event info; // 存储触摸屏的数据
        read(touchFd, &info, sizeof(info));

        // 判断当前产生的时候触摸屏事件 ,进一步判断是X轴事件
        if (info.type == EV_ABS && info.code == ABS_X)
        {
            pos.x = info.value;
        }
        // 判断当前产生的时候触摸屏事件 ,进一步判断是Y轴事件
        if (info.type == EV_ABS && info.code == ABS_Y)
        {
            pos.y = info.value;
        }
        // 松开的时候
        if (info.type == EV_KEY && info.code == BTN_TOUCH && info.value == 0)
        {
            // 黑色屏幕坐标范围： X  0-1024  Y  0-600
            // 转换坐标范围
            pos.x = (pos.x) * 800 * 1.0 / 1024;
            pos.y = (pos.y) * 480 * 1.0 / 600;
            // 蓝色屏幕坐标范围： X  0-800  Y  0-480

            // printf("x:%d y:%d\n", pos.x, pos.y);
            if (pos.x >= 0 && pos.x < 140 && pos.y >= 0 && pos.y < 120)
            {
                if (is_move_l(block_main))
                {
                    pthread_mutex_lock(&mutex);
                    // clear_block_screen(block_main, 0);
                    printf("%d %d\n", block_main->x, block_main->y);
                    // clear_block_screen(&tempBlk, 0);
                    clear_nwhite_to_screen();
                    block_main->y--;
                    block_to_screen_imme(block_main);
                    pthread_mutex_unlock(&mutex);
                }
                gameOpt = 1;
            }
            else if (pos.x >= 0 && pos.x < 140 && pos.y > 120 && pos.y < 240)
            {
                if (is_move_r(block_main))
                {
                    pthread_mutex_lock(&mutex);
                    // clear_block_screen(block_main, 0);
                    //  clear_block_screen(&tempBlk, 0);
                    clear_nwhite_to_screen();
                    block_main->y++;
                    block_to_screen_imme(block_main);
                    pthread_mutex_unlock(&mutex);
                }
                gameOpt = 2;
            }
            else if (pos.x >= 0 && pos.x < 140 && pos.y > 240 && pos.y < 360)
            {
                pthread_mutex_lock(&mutex);
                is_rotate_wall_l(block_main);
                is_rotate_wall_r(block_main);
                printf("左旋转\n");
                if (is_rotate_crash_block_l(block_main))
                {
                    clear_nwhite_to_screen();
                    l_rotate(block_main);
                    block_to_screen_imme(block_main);
                }
                pthread_mutex_unlock(&mutex);
                gameOpt = 3;
            }
            else if (pos.x >= 0 && pos.x < 140 && pos.y > 360 && pos.y < 480)
            {
                pthread_mutex_lock(&mutex);
                is_rotate_wall_l(block_main);
                is_rotate_wall_r(block_main);
                if (is_rotate_crash_block_r(block_main))
                {
                    clear_nwhite_to_screen();
                    r_rotate(block_main);
                    block_to_screen_imme(block_main);
                }
                pthread_mutex_unlock(&mutex);
                gameOpt = 4;
            }
            else if (pos.x >= 140 && pos.x < 300 && pos.y > 360 && pos.y < 480)
            {
                pthread_mutex_lock(&mutex);
                block_down(block_main);
                pthread_mutex_unlock(&mutex);
                gameOpt = 5;
            }
            else if (pos.x >= 750 && pos.x < 800 && pos.y > 430 && pos.y < 480)
            {
                pthread_mutex_lock(&mutex);
                gameOpt = 6;
                score = 0;
                pthread_mutex_unlock(&mutex);
                pthread_cond_signal(&cond);

                break;
            }
            else if (pos.x >= 320 && pos.x < 420 && pos.y > 400 && pos.y < 450)
            {
                if (flag)
                {
                    system("killall -SIGSTOP madplay");
                    flag = false;
                }
                else
                {
                    system("killall -SIGCONT madplay");
                    flag = true;
                }
            }
            else
            {
                gameOpt = 0;
            }
            target_flag = true;

            pthread_cond_signal(&cond);
            printf("gameOpt %d\n", gameOpt);
        }
    }

    // 4、关闭触摸屏文件
    // close(fd);

    return NULL;
}

void *touch_wait_longin(void *arg)
{
    touchPos_t pos;
    while (sys_mode != SLOGIN)
    {
        struct input_event info; // 存储触摸屏的数据
        printf("touc 272 line \n");

        read(touchFd, &info, sizeof(info));

        // 判断当前产生的时候触摸屏事件 ,进一步判断是X轴事件
        if (info.type == EV_ABS && info.code == ABS_X)
        {
            pos.x = info.value;
        }
        // 判断当前产生的时候触摸屏事件 ,进一步判断是Y轴事件
        if (info.type == EV_ABS && info.code == ABS_Y)
        {
            pos.y = info.value;
        }
        // 松开的时候
        if (info.type == EV_KEY && info.code == BTN_TOUCH && info.value == 0)
        {
            // 黑色屏幕坐标范围： X  0-1024  Y  0-600
            // 转换坐标范围
            pos.x = (pos.x) * 800 * 1.0 / 1024;
            pos.y = (pos.y) * 480 * 1.0 / 600;
            // 蓝色屏幕坐标范围： X  0-800  Y  0-480
            // printf("pos.x : %d pos.y : %d\n", pos.x, pos.y);
            if (sys_mode == NON || sys_mode == SACC)
            {
                char c = touch_login(pos);
                if (c != ' ')
                {
                    if (num == 0)
                    {
                        acc_font(lcd_p, f, "", 70, 120);
                    }
                    if (c == 'c')
                    {
                        sys_mode = SPASSWD;
                        num = 0;
                        passwd_font(lcd_p, f, "", 70, 230);

                        printf("%s\n", acc);

                        return acc;
                    }
                    else if (c == 'd')
                    {
                        if (num > 0)
                        {
                            num--;
                            acc[num] = '\0';
                            acc_font(lcd_p, f, acc, 70, 120);
                        }
                    }
                    else
                    {
                        acc[num] = c;
                        acc_font(lcd_p, f, acc, 70, 120);
                        num++;
                    }
                }
            }
            else if (sys_mode == SPASSWD)
            {
                char c = touch_login(pos);
                if (c != ' ')
                {
                    if (c == 'c')
                    {
                        if (strcmp(acc, "123") == 0 && strcmp(passwd, "456") == 0)
                        {
                            sys_mode = SLOGIN;
                        }
                        else
                        {
                            num = 0;
                            sys_mode = SACC;
                            memset(acc, 0, 20);
                            memset(passwd, 0, 20);
                        }
                    }
                    else if (c == 'd')
                    {
                        if (num > 0)
                        {
                            num--;
                            passwd[num] = '\0';
                            passwd_font(lcd_p, f, passwd, 70, 230);
                        }
                    }
                    else
                    {
                        passwd[num] = c;
                        passwd_font(lcd_p, f, passwd, 70, 230);
                        num++;
                    }
                }
            }
        }
    }
    return acc;
}

char choose_mode_touch()
{
    touchPos_t pos;
    struct input_event info; // 存储触摸屏的数据
    printf("touc 272 line \n");

    read(touchFd, &info, sizeof(info));

    // 判断当前产生的时候触摸屏事件 ,进一步判断是X轴事件
    if (info.type == EV_ABS && info.code == ABS_X)
    {
        pos.x = info.value;
    }
    // 判断当前产生的时候触摸屏事件 ,进一步判断是Y轴事件
    if (info.type == EV_ABS && info.code == ABS_Y)
    {
        pos.y = info.value;
    }
    // 松开的时候
    if (info.type == EV_KEY && info.code == BTN_TOUCH && info.value == 0)
    {
        // 黑色屏幕坐标范围： X  0-1024  Y  0-600
        // 转换坐标范围
        pos.x = (pos.x) * 800 * 1.0 / 1024;
        pos.y = (pos.y) * 480 * 1.0 / 600;
        // 蓝色屏幕坐标范围： X  0-800  Y  0-480
        printf("pos.x : %d pos.y : %d------\n", pos.x, pos.y);

        if (pos.x > 10 && pos.x < 110 && pos.y > 10 && pos.y < 110)
        {
            return '1';
        }
        else if (pos.x > 110 && pos.x < 250 && pos.y > 10 && pos.y < 110)
        {
            return '2';
        }
        else if (pos.x > 700 && pos.x < 800 && pos.y > 10 && pos.y < 110)
        {
            return '3';
        }
        // else if (pos.x > 250 && pos.x < 350 && pos.y > 10 && pos.y < 110)
        // {
        //     return '4';
        // }
    }
}

char touch_login(touchPos_t temppos)
{
    touchPos_t pos;
    pos.x = temppos.y;
    pos.y = temppos.x;

    if (pos.x > 100 && pos.x < 180 && pos.y > 420 && pos.y < 510)
    {
        return '1';
    }
    else if (pos.x > 100 && pos.x < 180 && pos.y > 520 && pos.y < 610)
    {
        return '2';
    }
    else if (pos.x > 100 && pos.x < 180 && pos.y > 630 && pos.y < 720)
    {
        return '3';
    }
    else if (pos.x > 210 && pos.x < 280 && pos.y > 420 && pos.y < 510)
    {
        return '4';
    }
    else if (pos.x > 210 && pos.x < 280 && pos.y > 520 && pos.y < 610)
    {
        return '5';
    }
    else if (pos.x > 210 && pos.x < 280 && pos.y > 630 && pos.y < 720)
    {
        return '6';
    }
    else if (pos.x > 300 && pos.x < 360 && pos.y > 420 && pos.y < 510)
    {
        return '7';
    }
    else if (pos.x > 300 && pos.x < 360 && pos.y > 520 && pos.y < 610)
    {
        return '8';
    }
    else if (pos.x > 300 && pos.x < 360 && pos.y > 630 && pos.y < 720)
    {
        return '9';
    }
    else if (pos.x > 380 && pos.x < 430 && pos.y > 430 && pos.y < 550)
    {
        return 'd';
    }
    else if (pos.x > 380 && pos.x < 430 && pos.y > 600 && pos.y < 730)
    {
        return 'c';
    }
    else
    {
        return ' ';
    }
}

// void *touch_step_wait(void *arg)
// {
//     touchPos_t pos;
//     while (1)
//     {
//         struct input_event info; // 存储触摸屏的数据
//         read(touchFd, &info, sizeof(info));

//         // 判断当前产生的时候触摸屏事件 ,进一步判断是X轴事件
//         if (info.type == EV_ABS && info.code == ABS_X)
//         {
//             pos.x = info.value;
//         }
//         // 判断当前产生的时候触摸屏事件 ,进一步判断是Y轴事件
//         if (info.type == EV_ABS && info.code == ABS_Y)
//         {
//             pos.y = info.value;
//         }
//         // 松开的时候
//         if (info.type == EV_KEY && info.code == BTN_TOUCH && info.value == 0)
//         {
//             // 黑色屏幕坐标范围： X  0-1024  Y  0-600
//             // 转换坐标范围
//             pos.x = (pos.x) * 800 * 1.0 / 1024;
//             pos.y = (pos.y) * 480 * 1.0 / 600;
//             printf("pos.x %d pos.y : %d\n", pos.x, pos.y);
//             printf("black_pos.x %d black_pos.mx : %d\n", black_pos.x, black_pos.mx);
//             printf("black_pos.y %d black_pos.my : %d\n", black_pos.y, black_pos.my);
//             if (pos.x > black_pos.x && pos.x < black_pos.mx && pos.y > black_pos.y && pos.y < black_pos.my)
//             {
//                 printf("正确 %d\n",row_step);
//                 if (is_start == false)
//                 {
//                     is_start = true;
//                     row_step++;
//                     break;
//                 }
//                 row_step++;
//             }
//             else
//             {
//             }
//         }
//     }
// }
