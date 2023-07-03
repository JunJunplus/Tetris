#pragma once

#include "block.h"
#include "draw.h"
#include "lcd.h"
#include "crash.h"
#include "touch.h"

int step_arr[2][4][4];
int lcdbuf[2][800 * 480];

int row_step;

typedef struct _step_pos
{
    int x;
    int y;
    int mx;
    int my;
} step_pos;
extern step_pos black_pos;
extern bool is_start;

extern void init_step_arr();

extern void start_step_game();
