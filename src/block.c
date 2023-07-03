#include "block.h"

int score;
void block_init(block_t *blk)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            blk->block_arr[i][j] = COLOR_WHITE;
        }
    }

    blk->bkt = rand() % 7;
    // blk->bkt = BLK_T;
    switch (blk->bkt)
    {
    case BLK_T:
        blk->block_arr[1][0] = COLOR_YELLOW;
        blk->block_arr[1][1] = COLOR_YELLOW;
        blk->block_arr[1][2] = COLOR_YELLOW;
        blk->block_arr[0][1] = COLOR_YELLOW;
        blk->x = ARR_ROW - 1;
        blk->y = ARR_COL / 2 - 1;
        blk->direct = DUP;
        break;
    case BLK_I:
        blk->block_arr[0][1] = COLOR_CYAN;
        blk->block_arr[1][1] = COLOR_CYAN;
        blk->block_arr[2][1] = COLOR_CYAN;
        blk->block_arr[3][1] = COLOR_CYAN;
        blk->x = ARR_ROW - 1;
        blk->y = ARR_COL / 2 - 1;
        blk->direct = DUP;
        break;
    case BLK_O:
        blk->block_arr[0][0] = COLOR_PURPLE;
        blk->block_arr[0][1] = COLOR_PURPLE;
        blk->block_arr[1][0] = COLOR_PURPLE;
        blk->block_arr[1][1] = COLOR_PURPLE;
        blk->x = ARR_ROW - 1;
        blk->y = ARR_COL / 2 - 1;
        blk->direct = DUP;
        break;
    case BLK_S:
        blk->block_arr[0][0] = COLOR_RED;
        blk->block_arr[0][1] = COLOR_RED;
        blk->block_arr[1][1] = COLOR_RED;
        blk->block_arr[1][2] = COLOR_RED;
        blk->x = ARR_ROW - 1;
        blk->y = ARR_COL / 2 - 1;
        blk->direct = DUP;
        break;
    case BLK_Z:
        blk->block_arr[0][1] = COLOR_GREEN;
        blk->block_arr[0][2] = COLOR_GREEN;
        blk->block_arr[1][0] = COLOR_GREEN;
        blk->block_arr[1][1] = COLOR_GREEN;
        blk->x = ARR_ROW - 1;
        blk->y = ARR_COL / 2 - 1;
        blk->direct = DUP;
        break;
    case BLK_L:
        blk->block_arr[1][0] = COLOR_ORANGE;
        blk->block_arr[1][1] = COLOR_ORANGE;
        blk->block_arr[1][2] = COLOR_ORANGE;
        blk->block_arr[2][2] = COLOR_ORANGE;
        blk->x = ARR_ROW - 1;
        blk->y = ARR_COL / 2 - 1;
        blk->direct = DUP;
        break;
    case BLK_J:
        blk->block_arr[1][0] = COLOR_BLUE;
        blk->block_arr[0][0] = COLOR_BLUE;
        blk->block_arr[0][1] = COLOR_BLUE;
        blk->block_arr[0][2] = COLOR_BLUE;
        blk->x = ARR_ROW - 1;
        blk->y = ARR_COL / 2 - 1;
        blk->direct = DUP;
        break;
    default:
        break;
    }
}

void block_move_down(block_t *blk)
{
    if (isCrash(blk))
    {
        printf("move left\n");
        blk->x--;
    }
}

void l_rotate(block_t *blk)
{
    // clear_block_screen(blk, 0);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            blk->block_arr[i][j] = COLOR_WHITE;
        }
    }
    if (blk->bkt == BLK_T)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[1][0] = COLOR_YELLOW;
            blk->block_arr[0][1] = COLOR_YELLOW;
            blk->block_arr[1][1] = COLOR_YELLOW;
            blk->block_arr[2][1] = COLOR_YELLOW;
            blk->direct = DLEFT;
            break;
        case DLEFT:
            blk->block_arr[1][0] = COLOR_YELLOW;
            blk->block_arr[1][1] = COLOR_YELLOW;
            blk->block_arr[1][2] = COLOR_YELLOW;
            blk->block_arr[2][1] = COLOR_YELLOW;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[0][1] = COLOR_YELLOW;
            blk->block_arr[1][1] = COLOR_YELLOW;
            blk->block_arr[2][1] = COLOR_YELLOW;
            blk->block_arr[1][2] = COLOR_YELLOW;
            blk->direct = DRIGHT;
            break;
        case DRIGHT:
            blk->block_arr[1][0] = COLOR_YELLOW;
            blk->block_arr[1][1] = COLOR_YELLOW;
            blk->block_arr[1][2] = COLOR_YELLOW;
            blk->block_arr[0][1] = COLOR_YELLOW;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_I)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[1][0] = COLOR_CYAN;
            blk->block_arr[1][1] = COLOR_CYAN;
            blk->block_arr[1][2] = COLOR_CYAN;
            blk->block_arr[1][3] = COLOR_CYAN;
            blk->direct = DLEFT;
            break;
        case DLEFT:
            blk->block_arr[0][1] = COLOR_CYAN;
            blk->block_arr[1][1] = COLOR_CYAN;
            blk->block_arr[2][1] = COLOR_CYAN;
            blk->block_arr[3][1] = COLOR_CYAN;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[1][0] = COLOR_CYAN;
            blk->block_arr[1][1] = COLOR_CYAN;
            blk->block_arr[1][2] = COLOR_CYAN;
            blk->block_arr[1][3] = COLOR_CYAN;
            blk->direct = DRIGHT;
            break;
        case DRIGHT:
            blk->block_arr[0][1] = COLOR_CYAN;
            blk->block_arr[1][1] = COLOR_CYAN;
            blk->block_arr[2][1] = COLOR_CYAN;
            blk->block_arr[3][1] = COLOR_CYAN;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_O)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[0][0] = COLOR_PURPLE;
            blk->block_arr[0][1] = COLOR_PURPLE;
            blk->block_arr[1][0] = COLOR_PURPLE;
            blk->block_arr[1][1] = COLOR_PURPLE;
            blk->direct = DLEFT;
            break;
        case DLEFT:
            blk->block_arr[0][0] = COLOR_PURPLE;
            blk->block_arr[0][1] = COLOR_PURPLE;
            blk->block_arr[1][0] = COLOR_PURPLE;
            blk->block_arr[1][1] = COLOR_PURPLE;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[0][0] = COLOR_PURPLE;
            blk->block_arr[0][1] = COLOR_PURPLE;
            blk->block_arr[1][0] = COLOR_PURPLE;
            blk->block_arr[1][1] = COLOR_PURPLE;
            blk->direct = DRIGHT;
            break;
        case DRIGHT:
            blk->block_arr[0][0] = COLOR_PURPLE;
            blk->block_arr[0][1] = COLOR_PURPLE;
            blk->block_arr[1][0] = COLOR_PURPLE;
            blk->block_arr[1][1] = COLOR_PURPLE;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_S)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[0][1] = COLOR_RED;
            blk->block_arr[1][1] = COLOR_RED;
            blk->block_arr[1][0] = COLOR_RED;
            blk->block_arr[2][0] = COLOR_RED;
            blk->direct = DLEFT;
            break;
        case DLEFT:
            blk->block_arr[0][0] = COLOR_RED;
            blk->block_arr[0][1] = COLOR_RED;
            blk->block_arr[1][1] = COLOR_RED;
            blk->block_arr[1][2] = COLOR_RED;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[0][1] = COLOR_RED;
            blk->block_arr[1][1] = COLOR_RED;
            blk->block_arr[1][0] = COLOR_RED;
            blk->block_arr[2][0] = COLOR_RED;
            blk->direct = DRIGHT;
            break;
        case DRIGHT:
            blk->block_arr[0][0] = COLOR_RED;
            blk->block_arr[0][1] = COLOR_RED;
            blk->block_arr[1][1] = COLOR_RED;
            blk->block_arr[1][2] = COLOR_RED;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_Z)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[0][1] = COLOR_GREEN;
            blk->block_arr[1][1] = COLOR_GREEN;
            blk->block_arr[1][2] = COLOR_GREEN;
            blk->block_arr[2][2] = COLOR_GREEN;
            blk->direct = DLEFT;
            break;
        case DLEFT:
            blk->block_arr[0][1] = COLOR_GREEN;
            blk->block_arr[0][2] = COLOR_GREEN;
            blk->block_arr[1][0] = COLOR_GREEN;
            blk->block_arr[1][1] = COLOR_GREEN;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[0][1] = COLOR_GREEN;
            blk->block_arr[1][1] = COLOR_GREEN;
            blk->block_arr[1][2] = COLOR_GREEN;
            blk->block_arr[2][2] = COLOR_GREEN;
            blk->direct = DRIGHT;
            break;
        case DRIGHT:
            blk->block_arr[0][1] = COLOR_GREEN;
            blk->block_arr[0][2] = COLOR_GREEN;
            blk->block_arr[1][0] = COLOR_GREEN;
            blk->block_arr[1][1] = COLOR_GREEN;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_L)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[0][0] = COLOR_ORANGE;
            blk->block_arr[1][0] = COLOR_ORANGE;
            blk->block_arr[2][0] = COLOR_ORANGE;
            blk->block_arr[0][1] = COLOR_ORANGE;
            blk->direct = DLEFT;
            break;
        case DLEFT:
            blk->block_arr[0][1] = COLOR_ORANGE;
            blk->block_arr[1][1] = COLOR_ORANGE;
            blk->block_arr[2][1] = COLOR_ORANGE;
            blk->block_arr[2][0] = COLOR_ORANGE;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[0][0] = COLOR_ORANGE;
            blk->block_arr[1][0] = COLOR_ORANGE;
            blk->block_arr[1][1] = COLOR_ORANGE;
            blk->block_arr[1][2] = COLOR_ORANGE;
            blk->direct = DRIGHT;
            break;
        case DRIGHT:
            blk->block_arr[1][0] = COLOR_ORANGE;
            blk->block_arr[1][1] = COLOR_ORANGE;
            blk->block_arr[1][2] = COLOR_ORANGE;
            blk->block_arr[2][2] = COLOR_ORANGE;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_J)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[0][0] = COLOR_BLUE;
            blk->block_arr[1][0] = COLOR_BLUE;
            blk->block_arr[2][0] = COLOR_BLUE;
            blk->block_arr[2][1] = COLOR_BLUE;
            blk->direct = DLEFT;
            break;
        case DLEFT:
            blk->block_arr[1][0] = COLOR_BLUE;
            blk->block_arr[1][1] = COLOR_BLUE;
            blk->block_arr[1][2] = COLOR_BLUE;
            blk->block_arr[0][2] = COLOR_BLUE;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[0][0] = COLOR_BLUE;
            blk->block_arr[0][1] = COLOR_BLUE;
            blk->block_arr[1][1] = COLOR_BLUE;
            blk->block_arr[2][1] = COLOR_BLUE;
            blk->direct = DRIGHT;
            break;
        case DRIGHT:
            blk->block_arr[1][0] = COLOR_BLUE;
            blk->block_arr[0][0] = COLOR_BLUE;
            blk->block_arr[0][1] = COLOR_BLUE;
            blk->block_arr[0][2] = COLOR_BLUE;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
}

void r_rotate(block_t *blk)
{
    // clear_block_screen(blk, 0);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            blk->block_arr[i][j] = COLOR_WHITE;
        }
    }
    if (blk->bkt == BLK_T)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[0][1] = COLOR_YELLOW;
            blk->block_arr[1][1] = COLOR_YELLOW;
            blk->block_arr[2][1] = COLOR_YELLOW;
            blk->block_arr[1][2] = COLOR_YELLOW;
            blk->direct = DRIGHT;
            break;
        case DRIGHT:
            blk->block_arr[1][0] = COLOR_YELLOW;
            blk->block_arr[1][1] = COLOR_YELLOW;
            blk->block_arr[1][2] = COLOR_YELLOW;
            blk->block_arr[2][1] = COLOR_YELLOW;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[1][0] = COLOR_YELLOW;
            blk->block_arr[0][1] = COLOR_YELLOW;
            blk->block_arr[1][1] = COLOR_YELLOW;
            blk->block_arr[2][1] = COLOR_YELLOW;
            blk->direct = DLEFT;
            break;
        case DLEFT:
            blk->block_arr[1][0] = COLOR_YELLOW;
            blk->block_arr[1][1] = COLOR_YELLOW;
            blk->block_arr[1][2] = COLOR_YELLOW;
            blk->block_arr[0][1] = COLOR_YELLOW;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_I)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[1][0] = COLOR_CYAN;
            blk->block_arr[1][1] = COLOR_CYAN;
            blk->block_arr[1][2] = COLOR_CYAN;
            blk->block_arr[1][3] = COLOR_CYAN;
            blk->direct = DRIGHT;

            break;
        case DLEFT:
            blk->block_arr[0][1] = COLOR_CYAN;
            blk->block_arr[1][1] = COLOR_CYAN;
            blk->block_arr[2][1] = COLOR_CYAN;
            blk->block_arr[3][1] = COLOR_CYAN;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[1][0] = COLOR_CYAN;
            blk->block_arr[1][1] = COLOR_CYAN;
            blk->block_arr[1][2] = COLOR_CYAN;
            blk->block_arr[1][3] = COLOR_CYAN;
            blk->direct = DLEFT;
            break;
        case DRIGHT:
            blk->block_arr[0][1] = COLOR_CYAN;
            blk->block_arr[1][1] = COLOR_CYAN;
            blk->block_arr[2][1] = COLOR_CYAN;
            blk->block_arr[3][1] = COLOR_CYAN;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_O)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[0][0] = COLOR_PURPLE;
            blk->block_arr[0][1] = COLOR_PURPLE;
            blk->block_arr[1][0] = COLOR_PURPLE;
            blk->block_arr[1][1] = COLOR_PURPLE;
            blk->direct = DRIGHT;

            break;
        case DLEFT:
            blk->block_arr[0][0] = COLOR_PURPLE;
            blk->block_arr[0][1] = COLOR_PURPLE;
            blk->block_arr[1][0] = COLOR_PURPLE;
            blk->block_arr[1][1] = COLOR_PURPLE;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[0][0] = COLOR_PURPLE;
            blk->block_arr[0][1] = COLOR_PURPLE;
            blk->block_arr[1][0] = COLOR_PURPLE;
            blk->block_arr[1][1] = COLOR_PURPLE;
            blk->direct = DLEFT;
            break;
        case DRIGHT:
            blk->block_arr[0][0] = COLOR_PURPLE;
            blk->block_arr[0][1] = COLOR_PURPLE;
            blk->block_arr[1][0] = COLOR_PURPLE;
            blk->block_arr[1][1] = COLOR_PURPLE;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_S)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[0][1] = COLOR_RED;
            blk->block_arr[1][1] = COLOR_RED;
            blk->block_arr[1][0] = COLOR_RED;
            blk->block_arr[2][0] = COLOR_RED;
            blk->direct = DRIGHT;
            break;
        case DLEFT:
            blk->block_arr[0][0] = COLOR_RED;
            blk->block_arr[0][1] = COLOR_RED;
            blk->block_arr[1][1] = COLOR_RED;
            blk->block_arr[1][2] = COLOR_RED;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[0][1] = COLOR_RED;
            blk->block_arr[1][1] = COLOR_RED;
            blk->block_arr[1][0] = COLOR_RED;
            blk->block_arr[2][0] = COLOR_RED;
            blk->direct = DLEFT;
            break;
        case DRIGHT:
            blk->block_arr[0][0] = COLOR_RED;
            blk->block_arr[0][1] = COLOR_RED;
            blk->block_arr[1][1] = COLOR_RED;
            blk->block_arr[1][2] = COLOR_RED;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_Z)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[0][1] = COLOR_GREEN;
            blk->block_arr[1][1] = COLOR_GREEN;
            blk->block_arr[1][2] = COLOR_GREEN;
            blk->block_arr[2][2] = COLOR_GREEN;
            blk->direct = DRIGHT;
            break;
        case DLEFT:
            blk->block_arr[0][1] = COLOR_GREEN;
            blk->block_arr[0][2] = COLOR_GREEN;
            blk->block_arr[1][0] = COLOR_GREEN;
            blk->block_arr[1][1] = COLOR_GREEN;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[0][1] = COLOR_GREEN;
            blk->block_arr[1][1] = COLOR_GREEN;
            blk->block_arr[1][2] = COLOR_GREEN;
            blk->block_arr[2][2] = COLOR_GREEN;
            blk->direct = DLEFT;
            break;
        case DRIGHT:
            blk->block_arr[0][1] = COLOR_GREEN;
            blk->block_arr[0][2] = COLOR_GREEN;
            blk->block_arr[1][0] = COLOR_GREEN;
            blk->block_arr[1][1] = COLOR_GREEN;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_L)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[0][0] = COLOR_ORANGE;
            blk->block_arr[1][0] = COLOR_ORANGE;
            blk->block_arr[1][1] = COLOR_ORANGE;
            blk->block_arr[1][2] = COLOR_ORANGE;
            blk->direct = DRIGHT;

            break;
        case DLEFT:
            blk->block_arr[0][1] = COLOR_ORANGE;
            blk->block_arr[1][1] = COLOR_ORANGE;
            blk->block_arr[2][1] = COLOR_ORANGE;
            blk->block_arr[2][0] = COLOR_ORANGE;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[0][0] = COLOR_ORANGE;
            blk->block_arr[1][0] = COLOR_ORANGE;
            blk->block_arr[2][0] = COLOR_ORANGE;
            blk->block_arr[0][1] = COLOR_ORANGE;
            blk->direct = DLEFT;
            break;
        case DRIGHT:
            blk->block_arr[1][0] = COLOR_ORANGE;
            blk->block_arr[1][1] = COLOR_ORANGE;
            blk->block_arr[1][2] = COLOR_ORANGE;
            blk->block_arr[2][2] = COLOR_ORANGE;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
    else if (blk->bkt == BLK_J)
    {
        switch (blk->direct)
        {
        case DUP:
            blk->block_arr[0][0] = COLOR_BLUE;
            blk->block_arr[0][1] = COLOR_BLUE;
            blk->block_arr[1][1] = COLOR_BLUE;
            blk->block_arr[2][1] = COLOR_BLUE;
            blk->direct = DRIGHT;

            break;
        case DLEFT:
            blk->block_arr[1][0] = COLOR_BLUE;
            blk->block_arr[1][1] = COLOR_BLUE;
            blk->block_arr[1][2] = COLOR_BLUE;
            blk->block_arr[0][2] = COLOR_BLUE;
            blk->direct = DDOWN;
            break;
        case DDOWN:
            blk->block_arr[0][0] = COLOR_BLUE;
            blk->block_arr[1][0] = COLOR_BLUE;
            blk->block_arr[2][0] = COLOR_BLUE;
            blk->block_arr[2][1] = COLOR_BLUE;
            blk->direct = DLEFT;
            break;
        case DRIGHT:
            blk->block_arr[1][0] = COLOR_BLUE;
            blk->block_arr[0][0] = COLOR_BLUE;
            blk->block_arr[0][1] = COLOR_BLUE;
            blk->block_arr[0][2] = COLOR_BLUE;
            blk->direct = DUP;
            break;
        default:
            break;
        }
    }
}

void block_down(block_t *blk)
{
    
    block_t *blk2 = block_main;
    for (;;)
    {
        if (isCrash(blk2))
        {
            blk2->x--;
        }
        else
        {
            break;
        }
    }
}

void *block_while_down(void *arg)
{
    printf("new block\n");
    
    block_t blk2;
    pthread_mutex_lock(&mutex);
    memcpy(&blk2, block_main, sizeof(block_t));
    pthread_mutex_unlock(&mutex);

    for (;;)
    {
        if (isCrash(&blk2))
        {
            pthread_mutex_lock(&mutex);
            blk2.x--;
            pthread_mutex_unlock(&mutex);

            //block_to_screen(&blk2);
        }
        else
        {
            pthread_mutex_lock(&mutex);
            //printf("2 block crash\n");
            block_to_arr(&blk2);
            scene_arr_draw();
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    scene_arr_draw();
}
