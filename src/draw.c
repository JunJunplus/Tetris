#include "draw.h"

/**
 * @brief 俄罗斯方块游戏初始化
 */

bool target_flag;
int difficultyValue;

void main_screen_init()
{
    difficultyValue = 2;
    score = 0;
    target_flag = false;
    // 主游戏场景数组初始化背景白色
    for (int i = 0; i < ARR_ROW; i++)
    {
        for (int j = 0; j < ARR_COL; j++)
        {
            scene_arr[i][j] = COLOR_WHITE;
        }
    }

    for (int j = 0; j < SCR_HEIGHT; j++)
    {
        for (int i = 0; i < SCR_WIDTH; i++)
        {
            lcd_p[SCR_WIDTH * j + i] = COLOR_WHITE;
        }
    }
    // 场景黑色分割线
    for (int j = 4 * SIDELEN; j < SCR_WIDTH; j++)
    {
        lcd_p[SCR_WIDTH * 352 + j] = COLOR_BLACK;
    }
    for (int j = 0; j < SCR_HEIGHT; j++)
    {
        lcd_p[SCR_WIDTH * j + 4 * SIDELEN - 1] = COLOR_BLACK;
    }
    // 五个操作框
    // for (int j = 0; j < 4 * SIDELEN; j++)
    // {
    //     lcd_p[SCR_WIDTH * 120 + j] = COLOR_BLACK;
    //     lcd_p[SCR_WIDTH * 120 * 2 + j] = COLOR_BLACK;
    //     lcd_p[SCR_WIDTH * 120 * 3 + j] = COLOR_BLACK;
    // }
    bmp_show_size("ml.bmp", 0, 0);
    bmp_show_size("mr.bmp", 0, 120);
    bmp_show_size("l.bmp", 0, 240);
    bmp_show_size("r.bmp", 0, 360);
    bmp_show_size("down.bmp", 128, 360);
    bmp_show_size("music.bmp", 350, 360);

    show_score(score);
}

/**
 * @brief 像素点颜色绘制(已废弃)
 * @param x
 * @param y
 * @param color
 */
void pos_square_draw(int x, int y, int color)
{
    for (int j = 0; j < SCR_HEIGHT; j++)
    {
        for (int i = 0; i < SCR_WIDTH; i++)
        {
            if (i > x * 32 && i < x * 32 + SIDELEN && j > y * 32 && j < y * 32 + SIDELEN)
            {
                lcd_p[SCR_WIDTH * j + i] = color;
            }
        }
    }
}

/**
 * @brief L型俄罗斯方块的绘制
 * @param x 要绘制在屏幕位置的横坐标
 * @param y 要绘制在屏幕位置的纵坐标
 * @param direct 俄罗斯方块的方向
 */
void l_block_draw(int x, int y, dit_blk_t direct)
{
    switch (direct)
    {
    case DUP:
        scene_arr[x][y] = COLOR_BLUE;
        scene_arr[x][y + 1] = COLOR_BLUE;
        scene_arr[x + 1][y] = COLOR_BLUE;
        scene_arr[x + 2][y] = COLOR_BLUE;
        // pos_square_draw(x, y, COLOR_BLUE);
        // pos_square_draw(x, y + 1, COLOR_BLUE);
        // pos_square_draw(x + 1, y, COLOR_BLUE);
        // pos_square_draw(x + 2 * 1, y, COLOR_BLUE);
        break;
    case DDOWN:
        scene_arr[x][y + 1] = COLOR_BLUE;
        pos_square_draw(x, y + 1, COLOR_BLUE);
        pos_square_draw(x + 1, y + 1, COLOR_BLUE);
        pos_square_draw(x + 2, y + 1, COLOR_BLUE);
        pos_square_draw(x + 2, y, COLOR_BLUE);
        break;
    case DLEFT:
        pos_square_draw(x, y, COLOR_BLUE);
        pos_square_draw(x + 1, y, COLOR_BLUE);
        pos_square_draw(x + 1, y + 1, COLOR_BLUE);
        pos_square_draw(x + 1, y + 2, COLOR_BLUE);
        break;
    case DRIGHT:
        pos_square_draw(x, y, COLOR_BLUE);
        pos_square_draw(x, y + 1, COLOR_BLUE);
        pos_square_draw(x, y + 2, COLOR_BLUE);
        pos_square_draw(x + 1, y + 2, COLOR_BLUE);
        break;
    default:
        break;
    }
}

void scence_block_remove(int row)
{
    score++;

    show_score(score);
    for (int i = row; i < ARR_ROW - 1; i++)
    {
        for (int j = 0; j < ARR_COL; j++)
        {
            scene_arr[i][j] = scene_arr[i + 1][j];
        }
    }
}

/**
 * @brief 场景数组转化为屏幕输出(内部函数)
 * @param x 场景数组x
 * @param y 场景数组y
 */
void arr_pixel_to_screen(int x, int y)
{

    for (int i = x * SIDELEN; i < x * SIDELEN + SIDELEN - 1; i++)
    {
        for (int j = y * SIDELEN; j < y * SIDELEN + SIDELEN - 1; j++)
        {
            lcd_p[SCR_WIDTH * j + 4 * SIDELEN + i] = scene_arr[x][y];
            // scene_arr[x][y] = COLOR_WHITE;
        }
    }
}

/**
 * @brief 场景数组全部输出到屏幕
 */
void scene_arr_draw()
{
    int row = -1;
    int tempArr[ARR_COL];
    int count = 0;
    for (int i = ARR_ROW - 1; i >= 0; i--)
    {
        count = 0;

        for (int j = 0; j < ARR_COL; j++)
        {
            if (scene_arr[i][j] != COLOR_WHITE)
            {
                count++;
            }
            if (count == ARR_COL)
            {
                row = i;
                printf("row : %d\n", row);
                scence_block_remove(row);
                // memcpy(tempArr, scene_arr[i], ARR_COL * sizeof(int));
            }
        }
    }
    // if (row != -1)
    // {
    //     for (int j = 0; j < ARR_COL; j++)
    //     {
    //         scene_arr[row][j] = COLOR_WHITE;
    //         arr_pixel_to_screen(row, j);
    //         usleep(1000 * 1000 / 2);
    //     }

    //     scence_block_remove(row);
    // }

    for (int i = 0; i < ARR_ROW; i++)
    {
        for (int j = 0; j < ARR_COL; j++)
        {
            arr_pixel_to_screen(i, j);
        }
    }
}

void block_to_arr(block_t *blk)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (blk->x + i < ARR_ROW && blk->y + j < ARR_COL && blk->block_arr[i][j] != COLOR_WHITE)
                scene_arr[blk->x + i][blk->y + j] = blk->block_arr[i][j];
        }
    }
}

void block_to_screen(block_t *blk)
{
    clear_nwhite_to_screen();

    target_flag = true;

    pthread_cond_signal(&cond);

    pthread_mutex_lock(&mutex);
    block_t *temp = malloc(sizeof(block_t));
    memcpy(temp, blk, sizeof(block_t));
    int x = blk->x;
    int y = blk->y;

    for (int k = 0; k < 4; k++)
    {
        for (int p = 0; p < 4; p++)
        {
            for (int i = x * SIDELEN + k * SIDELEN; i < x * SIDELEN + SIDELEN - 1 + k * SIDELEN; i++)
            {
                for (int j = y * SIDELEN + p * SIDELEN; j < y * SIDELEN + SIDELEN - 1 + p * SIDELEN; j++)
                {
                    if (blk->block_arr[k][p] < COLOR_WHITE && (blk->x + k < ARR_ROW))
                    {
                        lcd_p[SCR_WIDTH * j + 4 * SIDELEN + i] = blk->block_arr[k][p];
                    }
                }
            }
        }
    }
    pthread_mutex_unlock(&mutex);

    // 1000 * 1000 / 2
    usleep(1000 * 1000 / difficultyValue);
    // clear_block_screen(temp, 1000 * 1000 / 2);
}

void clear_block_screen(block_t *blk, int s)
{
    usleep(s);
    int x = blk->x;
    int y = blk->y;
    for (int k = 0; k < 4; k++)
    {
        for (int p = 0; p < 4; p++)
        {
            for (int i = x * SIDELEN + k * SIDELEN; i < x * SIDELEN + SIDELEN - 1 + k * SIDELEN; i++)
            {
                for (int j = y * SIDELEN + p * SIDELEN; j < y * SIDELEN + SIDELEN - 1 + p * SIDELEN; j++)
                {
                    if (blk->block_arr[k][p] < COLOR_WHITE && (blk->x + k < ARR_ROW))
                    {
                        lcd_p[SCR_WIDTH * j + 4 * SIDELEN + i] = COLOR_WHITE;
                    }
                }
            }
        }
    }
    free(blk);
    // clear_nwhite_to_screen();
}

void block_to_arr_imme(block_t *blk)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (blk->x + i < ARR_ROW && blk->y + j < ARR_COL && blk->block_arr[i][j] != COLOR_WHITE)
                scene_arr[blk->x + i][blk->y + j] = blk->block_arr[i][j];
        }
    }
}

void block_to_screen_imme(block_t *blk)
{
    int x = blk->x;
    int y = blk->y;

    for (int k = 0; k < 4; k++)
    {
        for (int p = 0; p < 4; p++)
        {
            for (int i = x * SIDELEN + k * SIDELEN; i < x * SIDELEN + SIDELEN - 1 + k * SIDELEN; i++)
            {
                for (int j = y * SIDELEN + p * SIDELEN; j < y * SIDELEN + SIDELEN - 1 + p * SIDELEN; j++)
                {
                    if (blk->block_arr[k][p] < COLOR_WHITE && (blk->x + k < ARR_ROW) && (blk->y + p < ARR_COL))
                    {
                        lcd_p[SCR_WIDTH * j + 4 * SIDELEN + i] = blk->block_arr[k][p];
                    }
                }
            }
        }
    }
}

void clear_nwhite_to_screen()
{
    for (int i = 0; i < ARR_ROW; i++)
    {
        for (int j = 0; j < ARR_COL; j++)
        {
            if (scene_arr[i][j] == COLOR_WHITE)
                arr_pixel_to_screen(i, j);
        }
    }
}
void *show_target_block(void *blk)
{
    while (gameOpt != 6)
    {
        pthread_mutex_lock(&cond_mutex);
        while (target_flag == false && gameOpt != 6)
        {
            pthread_cond_wait(&cond, &cond_mutex);
        }

        target_flag = false;
        // pthread_mutex_lock(&mutex);
        memcpy(&tempBlk, block_main, sizeof(block_t));
        // pthread_mutex_unlock(&mutex);
        printf("draw blk\n");
        for (;;)
        {
            if (isCrash(&tempBlk))
            {
                tempBlk.x--;
            }
            else
            {
                // printf("2 block crash\n");
                // clear_nwhite_to_screen();
                for (int k = 0; k < 4; k++)
                {
                    for (int p = 0; p < 4; p++)
                    {
                        for (int i = tempBlk.x * SIDELEN + k * SIDELEN; i < tempBlk.x * SIDELEN + SIDELEN - 1 + k * SIDELEN; i++)
                        {
                            for (int j = tempBlk.y * SIDELEN + p * SIDELEN; j < tempBlk.y * SIDELEN + SIDELEN - 1 + p * SIDELEN; j++)
                            {
                                if ((tempBlk.block_arr[k][p] < COLOR_WHITE) && ((i == tempBlk.x * SIDELEN + k * SIDELEN) || (j == tempBlk.y * SIDELEN + p * SIDELEN) || (i == tempBlk.x * SIDELEN + SIDELEN - 1 + k * SIDELEN - 1) || (j == tempBlk.y * SIDELEN + SIDELEN - 1 + p * SIDELEN - 1)) && (tempBlk.x + k < ARR_ROW) && (tempBlk.y + p < ARR_COL)

                                )
                                {
                                    lcd_p[SCR_WIDTH * j + 4 * SIDELEN + i] = COLOR_MAGENTA;
                                }
                            }
                        }
                    }
                }
                break;
            }
        }
        pthread_mutex_unlock(&cond_mutex);
    }
}

bool is_game_over()
{
    save_user();
    for (int i = 0; i < ARR_COL; i++)
    {
        if (scene_arr[ARR_ROW - 1][i] != COLOR_WHITE)
        {
            return true;
        }
    }
    return false;
}

// void preview_block_to_screen(block_t *blk)
// {
//     for (size_t i = 0; i < count; i++)
//     {
//         /* code */
//     }

//     arr_pixel_to_screen();
// }

void show_score(int num)
{

    int n = num;
    int result, temp, i = 0, j = 0, k, m;
    int numbers[3] = {0, 0, 0};

    // 分割每一位数字并分别导入数组（逆序）
    for (int i = 0; i < 3; i++)
    {
        result = n % 10;
        numbers[i] = result;
        n = n / 10;
    }

    // 统计位数
    j = 3;
    // 调整 为正序
    for (k = 0; k < 1; k++)
    {
        temp = numbers[k];
        numbers[k] = numbers[j - 1 - k];
        numbers[j - 1 - k] = temp;
    }
    for (m = 0; m < 3; m++)
    {
        printf("%d ", numbers[m]);
    }
    printf("\n");
    int bitN = 0;
    for (int i = 0; i < 3; i++)
    {
        bitN = numbers[i];
        switch (bitN)
        {
        case 0:
            bmp_show_size("0.bmp", 650, 366 + i * 34);
            break;
        case 1:
            bmp_show_size("1.bmp", 650, 366 + i * 34);
            break;
        case 2:
            bmp_show_size("2.bmp", 650, 366 + i * 34);
            break;
        case 3:
            bmp_show_size("3.bmp", 650, 366 + i * 34);
            break;
        case 4:
            bmp_show_size("4.bmp", 650, 366 + i * 34);
            break;
        case 5:
            bmp_show_size("5.bmp", 650, 366 + i * 34);
            break;
        case 6:
            bmp_show_size("6.bmp", 650, 366 + i * 34);
            break;
        case 7:
            bmp_show_size("7.bmp", 650, 366 + i * 34);
            break;
        case 8:
            bmp_show_size("8.bmp", 650, 366 + i * 34);
            break;
        case 9:
            bmp_show_size("9.bmp", 650, 366 + i * 34);
            break;
        default:
            break;
        }
    }
}

void draw_prev_block(block_t *prev)
{
    int x = 380;
    int y = 380;

    for (int k = 0; k < 4; k++)
    {
        for (int p = 0; p < 4; p++)
        {
            for (int i = x + k * SIDELEN; i < x + SIDELEN - 1 + k * SIDELEN; i++)
            {
                for (int j = y + p * SIDELEN; j < y + SIDELEN - 1 + p * SIDELEN; j++)
                {
                    lcd_p[SCR_WIDTH * j + 4 * SIDELEN + i] = COLOR_WHITE;
                }
            }
        }
    }

    for (int k = 0; k < 4; k++)
    {
        for (int p = 0; p < 4; p++)
        {
            for (int i = x + k * SIDELEN; i < x + SIDELEN - 1 + k * SIDELEN; i++)
            {
                for (int j = y + p * SIDELEN; j < y + SIDELEN - 1 + p * SIDELEN; j++)
                {
                    if (prev->block_arr[k][p] < COLOR_WHITE)
                    {
                        lcd_p[SCR_WIDTH * j + 4 * SIDELEN + i] = prev->block_arr[k][p];
                    }
                }
            }
        }
    }
}