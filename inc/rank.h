#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "kernel_list.h"
#include "font.h"
#include "lcd.h"
#include "touch.h"

typedef struct _user_rank
{
    char name[20];
    int score;
    struct list_head list;
} user_rank;

struct list_head *rank_head ;


int user_count;

extern void init_user();

extern void rank_sort_by_score();

extern void add_user(char *name);
