#include "crash.h"

bool isCrash(block_t *blk)
{
    for (int k = 0; k < 4; k++)
    {
        for (int l = 0; l < 4; l++)
        {
            if (
                // (blk->block_arr[k][l] != COLOR_WHITE && blk->y + l == ARR_COL - 1)
                // || (blk->block_arr[k][l] != COLOR_WHITE && blk->y + l == 0) ||
                (blk->x + k < ARR_ROW) &&

                (blk->block_arr[k][l] != COLOR_WHITE && scene_arr[blk->x + k - 1][blk->y + l] != COLOR_WHITE))
            {
                //printf("blk->y + l : %d",blk->y + l);
                return false;
            }
        }
    }

    return true;
}

bool is_move_l(block_t *blk)
{
    for (int k = 0; k < 4; k++)
    {
        for (int l = 0; l < 4; l++)
        {
            if ((blk->block_arr[k][l] != COLOR_WHITE && blk->y + l == 0) || (blk->x + k < ARR_ROW) &&
                                                                                (scene_arr[blk->x + k][blk->y + l - 1] != COLOR_WHITE && blk->block_arr[k][l] != COLOR_WHITE))
            {
                return false;
            }
        }
    }

    return true;
}
bool is_move_r(block_t *blk)
{
    for (int k = 0; k < 4; k++)
    {
        for (int l = 0; l < 4; l++)
        {
            if ((blk->block_arr[k][l] != COLOR_WHITE && blk->y + l == ARR_COL - 1) || (blk->x + k < ARR_ROW) &&
                                                                                          (scene_arr[blk->x + k][blk->y + l + 1] != COLOR_WHITE && blk->block_arr[k][l] != COLOR_WHITE))
            {
                return false;
            }
        }
    }

    return true;
}

bool is_rotate_wall_l(block_t *temp)
{
    block_t blk;
    memcpy(&blk, temp, sizeof(block_t));
    l_rotate(&blk);
    for (int k = 0; k < 4; k++)
    {
        for (int l = 0; l < 4; l++)
        {
            if ((blk.block_arr[k][l] != COLOR_WHITE && blk.y + l + 1 == 0)
                //|| (blk.x + k < ARR_ROW)
                //&&(scene_arr[blk.x + k][blk.y + l - 1] != COLOR_WHITE && blk.block_arr[k][l - 1] != COLOR_WHITE)
            )
            {
                temp->y++;
                return false;
            }
        }
    }
    return true;
}

bool is_rotate_wall_r(block_t *temp)
{
    block_t blk;
    memcpy(&blk, temp, sizeof(block_t));
    l_rotate(&blk);

    for (int k = 0; k < 4; k++)
    {
        for (int l = 0; l < 4; l++)
        {
            if ((blk.block_arr[k][l] != COLOR_WHITE && blk.y + l - 1 == ARR_COL - 1)
                //|| (blk->x + k < ARR_ROW) &&
                //(scene_arr[blk->x + k][blk->y + l + 1] != COLOR_WHITE && blk->block_arr[k][l] != COLOR_WHITE))
            )
            {
                if (blk.bkt == BLK_I)
                {
                    temp->y--;
                }
                temp->y--;
                return false;
            }
        }
    }
    return true;
}

bool is_rotate_crash_block_l(block_t *temp)
{
    block_t blk;
    memcpy(&blk, temp, sizeof(block_t));
    l_rotate(&blk);
    for (int k = 0; k < 4; k++)
    {
        for (int l = 0; l < 4; l++)
        {
            if (
                // (blk->block_arr[k][l] != COLOR_WHITE && blk->y + l == ARR_COL - 1)
                // || (blk->block_arr[k][l] != COLOR_WHITE && blk->y + l == 0) ||
                (blk.x + k < ARR_ROW) &&
                (scene_arr[blk.x + k][blk.y + l] != COLOR_WHITE && blk.block_arr[k][l] != COLOR_WHITE))
            {
                return false;
            }
        }
    }
    return true;
}

bool is_rotate_crash_block_r(block_t *temp)
{

    block_t blk;
    memcpy(&blk, temp, sizeof(block_t));

    r_rotate(&blk);
    for (int k = 0; k < 4; k++)
    {
        for (int l = 0; l < 4; l++)
        {
            if (
                // (blk->block_arr[k][l] != COLOR_WHITE && blk->y + l == ARR_COL - 1)
                // || (blk->block_arr[k][l] != COLOR_WHITE && blk->y + l == 0) ||
                (blk.x + k < ARR_ROW) &&
                (scene_arr[blk.x + k][blk.y + l] != COLOR_WHITE && blk.block_arr[k][l] != COLOR_WHITE))
            {
                return false;
            }
        }
    }
    return true;
}
