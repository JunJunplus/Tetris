#ifndef _DRAW_H
#define _DRAW_H

#include "block.h"
#include "lcd.h"
#include "crash.h"
#include "rank.h"
#include "bmp.h"
#define SIDELEN 32
#define ARR_ROW 21
#define ARR_COL 11

typedef enum direct_block dit_blk_t;

typedef enum block_kind block_kind_t;

typedef struct block block_t;

int scene_arr[ARR_ROW][ARR_COL];

extern  bool target_flag;

extern int difficultyValue;


extern void main_screen_init();

extern void pos_square_draw(int x, int y, int color);

extern void l_block_draw(int x, int y, dit_blk_t direct);

extern void scene_arr_draw();

extern void block_to_arr(block_t *blk);

extern void block_to_screen(block_t *blk);

extern void clear_block_screen(block_t *blk, int s);

extern void block_to_screen_imme(block_t *blk);

extern void clear_nwhite_to_screen();

extern void  *show_target_block(void *blk);

extern bool is_game_over();

extern void draw_prev_block(block_t *prev);

#endif