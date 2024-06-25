#include <iostream>
#include "conio2.h"
#include "variable_managment.h"
#include "finish.h"
#include "stones.h"
#include "struct.h"

using namespace std;

void finish(game_t *game)
{
    set_empty_visited(game);
    for(int i = 0; i < game->size_of_board; i++)
    {
        for(int j = 0; j < game->size_of_board; j++)
        {
            game->black_f = false;
            game->white_f = false;
            game->sf = 0;
            if(*(game->board_n + j*game->size_of_board + i) == NONE && *(game->board_visited + j*game->size_of_board + i) == NOVISITED)
            {
                countscore(game, j, i);
                if((game->black_f && game->white_f))
                {
                    change_none_teritory(game, j, i, NONE, NONETERITORY);
                }
            }
        }
    }
    set_empty_visited(game);
    for(int i = 0; i < game->size_of_board; i++)
    {
        for(int j = 0; j < game->size_of_board; j++)
        {
            set_empty_visited(game);
            *(game->board_lib + j*game->size_of_board + i) = count_lib_finish(game, j, i, *(game->board_n + j*game->size_of_board + i));
        }
    }
    for(int i = 0; i < game->size_of_board; i++)
    {
        for(int j = 0; j < game->size_of_board; j++)
        {
            set_empty_visited(game);
            if(*(game->board_lib + j*game->size_of_board + i) == 0)
            {
                check_for_delete(game, j, i);
            }
        }
    }
    set_empty_visited(game);
    for(int i = 0; i < game->size_of_board; i++)
    {
        for(int j = 0; j < game->size_of_board; j++)
        {
            if(*(game->board_n + j*game->size_of_board + i) == NONETERITORY)
                change_none_teritory(game, j, i, NONETERITORY, NONE);
        }
    }
    set_empty_visited(game);
    for(int i = 0; i < game->size_of_board; i++)
    {
        for(int j = 0; j < game->size_of_board; j++)
        {
            game->black_f = false;
            game->white_f = false;
            game->sf = 0;
            if(*(game->board_n + j*game->size_of_board + i) == NONE && *(game->board_visited + j*game->size_of_board + i) == NOVISITED)
            {
                countscore(game, j, i);
                if(!(game->black_f && game->white_f))
                {
                    if(game->black_f)
                        game->score.black += game->sf;
                    else if(game->white_f)
                        game->score.white += game->sf;
                }
            }
        }
    }
}

void countscore(game_t *game, int x, int y)
{
    *(game->board_visited + x*game->size_of_board + y) = VISITED;
    game->sf++;
    if(x-1 >= 0)
        countscore_direction(game, x-1, y);
    if(x+1 <= game->size_of_board - 1)
        countscore_direction(game, x+1, y);
    if(y-1 >= 0)
        countscore_direction(game, x, y-1);
    if(y+1 <= game->size_of_board - 1)
        countscore_direction(game, x, y+1);
}

void countscore_direction(game_t *game, int x, int y)
{
    if(*(game->board_visited + x*game->size_of_board + y) == NOVISITED)
    {
        if(*(game->board_n + x*game->size_of_board + y) == NONE)
            countscore(game, x, y);
        else
        {
            if(*(game->board_n + x*game->size_of_board + y) == SBLACK)
                game->black_f = true;
            else
                game->white_f = true;
        }
    }
}

void change_none_teritory(game_t *game, int x, int y, int change_from, int change_to)
{
    *(game->board_visited + x*game->size_of_board + y) = NOVISITED;
    *(game->board_n + x*game->size_of_board + y) = change_to;
    if(x-1 >= 0)
        change_none_teritory_direction(game, x-1, y, change_from, change_to);
    if(x+1 <= game->size_of_board - 1)
        change_none_teritory_direction(game, x+1, y, change_from, change_to);
    if(y-1 >= 0)
        change_none_teritory_direction(game, x, y-1, change_from, change_to);
    if(y+1 <= game->size_of_board - 1)
        change_none_teritory_direction(game, x, y+1, change_from, change_to);
    *(game->board_visited + x*game->size_of_board + y) = VISITED;
}

void change_none_teritory_direction(game_t *game, int x, int y, int change_from, int change_to)
{
    if(*(game->board_visited + x*game->size_of_board + y) == VISITED)
    {
        if(*(game->board_n + x*game->size_of_board + y) == change_from)
            change_none_teritory(game, x, y, change_from, change_to);
    }
}


void check_for_delete(game_t *game, int x, int y)
{
   if(*(game->board_lib + x*game->size_of_board + y) == 0 && *(game->board_visited + x*game->size_of_board + y) == NOVISITED)
   {
       if(*(game->board_n + x*game->size_of_board + y) != NONE && *(game->board_n + x*game->size_of_board + y) != NONETERITORY)
       {
            if(check_lib_oponent(game, x, y, *(game->board_n + x*game->size_of_board + y)))
                delete_stones_finish(game, x, y);
       }
   }
}

int count_lib_finish(game_t* game, int x, int y, int color)
{
    int result = 0;
    *(game->board_visited + x*game->size_of_board + y) = VISITED;
    if(x-1 >= 0)
    {
        if(*(game->board_n + (x-1)*game->size_of_board + y) == NONE)
        {
            result++;
        }
        else if((*(game->board_n + (x-1)*game->size_of_board + y) == color && *(game->board_visited + (x-1)*game->size_of_board + y) == NOVISITED) || (*(game->board_n + (x-1)*game->size_of_board + y) == NONETERITORY) && *(game->board_visited + (x-1)*game->size_of_board + y) == NOVISITED)
            result += count_lib_finish(game, x-1, y, color);
    }
    if(x+1 <= game->size_of_board - 1)
    {
        if(*(game->board_n + (x+1)*game->size_of_board + y) == NONE)
        {
            result++;
        }
        else if((*(game->board_n + (x+1)*game->size_of_board + y) == color && *(game->board_visited + (x+1)*game->size_of_board + y) == NOVISITED) || (*(game->board_n + (x+1)*game->size_of_board + y) == NONETERITORY) && *(game->board_visited + (x+1)*game->size_of_board + y) == NOVISITED)
            result += count_lib_finish(game, x+1, y, color);
    }
    if(y-1 >= 0)
    {
        if(*(game->board_n + x*game->size_of_board + y-1) == NONE)
        {
            result++;
        }
        else if((*(game->board_n + x*game->size_of_board + y-1) == color && *(game->board_visited + x*game->size_of_board + y-1) == NOVISITED) || (*(game->board_n + x*game->size_of_board + y-1) == NONETERITORY && *(game->board_visited + x*game->size_of_board + y-1) == NOVISITED))
            result += count_lib_finish(game, x, y-1, color);
    }
    if(y+1 <= game->size_of_board - 1)
    {
        if(*(game->board_n + x*game->size_of_board + y+1) == NONE)
        {
            result++;
        }
        else if((*(game->board_n + x*game->size_of_board + y+1) == color && *(game->board_visited + x*game->size_of_board + y+1) == NOVISITED) || (*(game->board_n + x*game->size_of_board + y+1) == NONETERITORY && *(game->board_visited + x*game->size_of_board + y+1) == NOVISITED))
            result += count_lib_finish(game, x, y+1, color);
    }
    return result;
}

void delete_stones_finish(game_t *game, int x, int y)
{
    *(game->board_visited + x*game->size_of_board + y) = VISITED;

    if(x-1 >= 0)
        delete_stones_direction(game, x-1, y, x, y);
    if(x+1 <= game->size_of_board - 1)
        delete_stones_direction(game, x+1, y, x, y);
    if(y-1 >= 0)
        delete_stones_direction(game, x, y-1, x, y);
    if(y+1 <= game->size_of_board - 1)
        delete_stones_direction(game, x, y+1, x, y);

    if(*(game->board_n + x*game->size_of_board + y) == SWHITE)
        game->score.black++;
    else if(*(game->board_n + x*game->size_of_board + y) == SBLACK)
        game->score.white++;

    *(game->board_lib + x*game->size_of_board + y) = NONE_LIBERTY;
    *(game->board_n + x*game->size_of_board + y) = NONE;
    *(game->board + x*game->size_of_board + y) = NONECHAR;

}

bool check_lib_oponent(game_t *game, int x, int y, int color)
{
    bool result = false;
     *(game->board_visited + x*game->size_of_board + y) = VISITED;
    if(x-1 >= 0)
    {
        if(check_lib_oponent_direction(game, x-1, y, color))
            result = true;
    }
    if(x+1 <= game->size_of_board - 1)
    {
        if(check_lib_oponent_direction(game, x+1, y, color))
            result = true;
    }
    if(y-1 >= 0)
    {
        if(check_lib_oponent_direction(game, x, y-1, color))
            result = true;
    }
    if(y+1 <= game->size_of_board - 1)
    {
        if(check_lib_oponent_direction(game, x, y+1, color))
            result = true;
    }
    return result;
}

bool check_lib_oponent_direction(game_t *game, int x, int y, int color)
{
    if((*(game->board_n + x*game->size_of_board + y) == color || *(game->board_n + x*game->size_of_board + y) == NONETERITORY)&& *(game->board_visited + x*game->size_of_board + y) == NOVISITED)
        return check_lib_oponent(game, x, y, color);
    else if(*(game->board_n + x*game->size_of_board + y) != NONE)
    {
        if(*(game->board_lib + x*game->size_of_board + y) > 0)
            return true;
        else
            return false;
    }
}

