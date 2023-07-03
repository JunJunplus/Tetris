#include "game.h"

void init_game()
{

    system("madplay ./music/Before.mp3 &");

    srand((unsigned int)time(NULL));
    main_screen_init();
    mutex_init();

    block_t blk;

    block_init(&blk);
    block_main = &blk;

    scene_arr_draw();
    pthread_t pid;
    pthread_t pid2;
    // block_main = &blk;
    pthread_create(&pid, NULL, touch_wait, block_main);
    pthread_create(&pid2, NULL, show_target_block, NULL);
    while (gameOpt != 6)
    {
        block_t blk2;
        blk2.bkt = BLK_T;
        block_init(&blk2);
        block_prev = &blk2;
        draw_prev_block(block_prev);
        while (gameOpt != 6)
        {

            if (isCrash(block_main))
            {
                pthread_mutex_lock(&mutex);

                block_main->x--;
                // usleep(1000 * 1000 / 2);
                pthread_mutex_unlock(&mutex);

                block_to_screen(block_main);
            }
            else
            {
                // pthread_mutex_lock(&mutex);
                // printf("2 block crash\n");
                block_to_arr(block_main);
                scene_arr_draw();
                pthread_mutex_unlock(&mutex);
                break;
            }
        }
        scene_arr_draw();
        if (is_game_over())
        {
            printf("game over\n");
            break;
        }
        pthread_mutex_lock(&mutex);
        memcpy(block_main,block_prev,sizeof(block_t));
        pthread_mutex_unlock(&mutex);
    }

    pthread_join(pid, NULL);
    pthread_join(pid2, NULL);
    system("killall -SIGKILL madplay");
    gameOpt = 0;
    // lcd_destory();
}