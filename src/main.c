#include "login.h"
#include "game.h"
#include "rank.h"


int main()
{
    lcd_init();

    touch_init();
    printf("12\n");

    init_user();
    login_face();
    while (1)
    {
LABEL:        
        bmp_show("111.bmp");
        while (1)
        {
            char mode = choose_mode_touch();

            switch (mode)
            {
            case '1':
                init_game();
                goto LABEL;
                break;
            case '2':
                rank_sort_by_score();
                break;
            case '3':
                goto LABEL;
                break;
            // case '4':
            //     start_step_game();
            //     goto LABEL;
                break;
            default:
                break;
            }
        }
    }

    return 0;
}
