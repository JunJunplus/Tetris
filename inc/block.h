#ifndef _BLOCK_H
#define _BLOCK_H

#include <string.h>

#include "lcd.h"
#include "crash.h"
#include "mutex.h"

   
extern int score;
typedef enum direct_block
{
    DUP,
    DLEFT,
    DDOWN,
    DRIGHT
} dit_blk_t;

typedef enum block_kind
{
    BLK_O,
    BLK_I,
    BLK_S,
    BLK_Z,
    BLK_L,
    BLK_J,
    BLK_T,
} block_kind_t;

typedef struct block
{
    block_kind_t bkt;
    dit_blk_t direct;
    int block_arr[4][4];
    int x;
    int y;
} block_t;

block_t *block_main;
block_t *block_prev;
block_t tempBlk;

extern void block_init(block_t *blk);

extern void l_rotate(block_t *blk);

extern void r_rotate(block_t *blk);

extern void block_down(block_t *blk);

extern void *block_while_down(void *arg);

#endif