#include "rank.h"

void init_user()
{
    int fd = open("user.txt", O_RDWR | O_CREAT, S_IRWXU);
    if (fd == -1)
    {
        perror("open error");
        return;
    }
    struct stat st;
    stat("user.txt", &st);
    int size = st.st_size;

    rank_head = malloc(sizeof(struct list_head));
    if (rank_head == NULL)
    {
        perror("malloc---------------- error\n");
        return;
    }
    INIT_LIST_HEAD(rank_head);

    for (size_t i = 0; i < size / sizeof(user_rank); i++)
    {
        user_rank *us = malloc(sizeof(user_rank));
        int ret = read(fd, us, sizeof(user_rank));
        if (ret == -1)
        {
            perror("read error\n");
            return;
        }
        list_add_tail(&(us->list), rank_head);
        printf("us-name:%s\n", us->name);
        printf("us-score:%d\n", us->score);
    }

    close(fd);
}

void rank_sort_by_score()
{
    user_rank *pos;
    int max = 0;
    int temp = 9999;
    char buf[1024];
    memset(buf, 0, 1024);

    // while (max <= temp)
    // {
    int user_count = 0;
    user_rank *poss;
    list_for_each_entry(poss, rank_head, list)
    {
        user_count++;
    }
    int perv = 999;
    strcat(buf, "                   排行榜\n");
    strcat(buf, "排名    姓名    分数\n");
    int num = 0;
    for (int j = 0; j < user_count; j++)
    {
        max = 0;

        list_for_each_entry(pos, rank_head, list)
        {
            if (pos->score >= max && pos->score < perv)
            {
                max = pos->score;
                poss = pos;
            }
        }
        num++;
        perv = max;
        char scoreStr[10];
        sprintf(scoreStr, "%d         ", num);
        strcat(buf, scoreStr);

        strcat(buf, poss->name);
        strcat(buf, "         ");

        sprintf(scoreStr, "%d", poss->score);
        strcat(buf, scoreStr);
        strcat(buf, "\n");
    }

    score_font(lcd_p, f, buf, 0, 0);

    //     temp = max;
    // }
}

void add_user(char *name)
{

    user_rank *pos;

    list_for_each_entry(pos, rank_head, list)
    {
        if (strcmp(pos->name, name) == 0)
        {
            return;
        }
    }
    printf("保存用户\n");
    user_rank *user = malloc(sizeof(user_rank));

    memset(user, 0, sizeof(user_rank));
    strcpy(user->name, name);
    printf("user->name : %s\n", user->name);
    list_add_tail(&(user->list), rank_head);
}

void save_user()
{
    int fd = open("user.txt", O_RDWR | O_CREAT, S_IRWXU);
    if (fd == -1)
    {
        perror("open error");
        return;
    }
    user_count = 0;

    user_rank *pos;
    list_for_each_entry(pos, rank_head, list)
    {
        if (strcmp(pos->name, acc) == 0)
        {
            if (score > pos->score)
                pos->score = score;
            printf("保存分数：%d\n", pos->score);
        }
    }

    user_rank *poss;
    list_for_each_entry(poss, rank_head, list)
    {
        user_count++;
        write(fd, poss, sizeof(user_rank));
    }
    close(fd);
}