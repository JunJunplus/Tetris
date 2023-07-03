#ifndef _CRASH_H
#define _CRASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "block.h"
#include "draw.h"
#include "lcd.h"

typedef enum direct_block dit_blk_t;

typedef enum block_kind block_kind_t;

typedef struct block block_t;

extern bool isCrash(block_t *blk);
extern bool is_move_l(block_t *blk);
extern bool is_move_r(block_t *blk);

extern bool is_rotate_wall_l(block_t *temp);

extern bool is_rotate_wall_r(block_t *temp);

extern bool is_rotate_crash_block_l(block_t *temp);

extern bool is_rotate_crash_block_r(block_t *temp);

#endif