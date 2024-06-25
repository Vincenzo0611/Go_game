#include <iostream>
#include "conio2.h"
#include "display.h"
#include "stones.h"
#include "variable_managment.h"
#include "struct.h"

using namespace std;

void place_stone(game_t *game, cursor_t cursor, int color)
{
    if(color == SWHITE)
        *(game->board_n + cursor.x_b*game->size_of_board + cursor.y_b) = SWHITE;
    else
        *(game->board_n + cursor.x_b*game->size_of_board + cursor.y_b) = SBLACK;
    *(game->board + cursor.x_b*game->size_of_board + cursor.y_b) = STONECHAR;
    gotoxy(cursor.x_d, cursor.y_d);
    textattr(color);
    putch(*(game->board + cursor.x_b*game->size_of_board + cursor.y_b));
}

void place_stone_accept(game_t *game, cursor_t cursor)
{
    char zn = 1;
    while(zn != ESC)
    {
        textattr(game->nowcolor);
        gotoxy(cursor.x_d, cursor.y_d);
        putch(*(game->board + cursor.x_b*game->size_of_board + cursor.y_b));
        alert("Click ENTER - accept or ESC - cancel");
        zn = getch();
        if(zn == ENTER)
        {
            KO(game);
            place_stone(game, cursor, game->nowcolor);
            if(game->nowcolor == SWHITE)
                game->nowcolor = SBLACK;
            else
                game->nowcolor = SWHITE;

            //liberty(game, cursor.x_b, cursor.y_b, cursor);
            for(int i = 0; i < game->size_of_board; i++)
            {
                for(int j = 0; j < game->size_of_board; j++)
                {
                    set_empty_visited(game);
                    *(game->board_lib + j*game->size_of_board + i) = count_lib(game, j, i);
                }
            }
            for(int i = 0; i < game->size_of_board; i++)
            {
                for(int j = 0; j < game->size_of_board; j++)
                {
                    if(*(game->board_lib + j*game->size_of_board + i) == 0 && *(game->board_KO + j*game->size_of_board + i) == NOKO)
                    {
                        set_empty_visited(game);
                        delete_stones(game, j, i);
                        build(*game, cursor.xstart, cursor.ystart);
                    }
                }
            }
            break;
        }
    }
    alert_clear();

}

bool check_suicide(game_t *game,int x, int y)
{
    bool result = true;
    if(x-1 >= 0)
        if(!check_suicide_direction(game, x-1, y, x, y))
            return false;
    if(x+1 <= game->size_of_board - 1)
        if(!check_suicide_direction(game, x+1, y, x, y))
            return false;
    if(y-1 >= 0)
        if(!check_suicide_direction(game, x, y-1, x, y))
            return false;
    if(y+1 <= game->size_of_board - 1)
        if(!check_suicide_direction(game, x, y+1, x, y))
            return false;

    return result;
}

bool check_suicide_direction(game_t *game,int x, int y, int x_checking, int y_checking)
{
    bool result = true;
    if(*(game->board_n + x*game->size_of_board + y) != NONE)
    {
        if(*(game->board_n + x*game->size_of_board + y) == game->nowcolor)
        {
            if(*(game->board_lib + x*game->size_of_board + y) > 1)
                result = false;
        }
        else if(*(game->board_lib + x*game->size_of_board + y) == 1 && KO_check(game, x_checking, y_checking))//KO
        {
                *(game->board_KO + x_checking*game->size_of_board + y_checking) = STARTKO;
                result = false;
        }
    }
    else
        result = false;

    return result;
}

int count_lib(game_t* game, int x, int y)
{
    if(*(game->board_n + x*game->size_of_board + y) == NONE)
        return NONE_LIBERTY;
    int result = 0;
    *(game->board_visited + x*game->size_of_board + y) = VISITED;
    if(x-1 >= 0)
    {
        if(*(game->board_visited + (x-1)*game->size_of_board + y) == NOVISITED)
        {
             if(*(game->board_n + (x-1)*game->size_of_board + y) == NONE)
            {
                *(game->board_visited + (x-1)*game->size_of_board + y) = VISITED;
                result++;
            }
            else if(*(game->board_n + (x-1)*game->size_of_board + y) == *(game->board_n + x*game->size_of_board + y))
                result += count_lib(game, x-1, y);
        }
    }
    if(x+1 <= game->size_of_board - 1)
    {
        if(*(game->board_visited + (x+1)*game->size_of_board + y) == NOVISITED)
        {
            if(*(game->board_n + (x+1)*game->size_of_board + y) == NONE)
            {
                *(game->board_visited + (x+1)*game->size_of_board + y) = VISITED;
                result++;
            }
            else if(*(game->board_n + (x+1)*game->size_of_board + y) == *(game->board_n + x*game->size_of_board + y))
                result += count_lib(game, x+1, y);
        }
    }
    if(y-1 >= 0)
    {
        if(*(game->board_visited + x*game->size_of_board + y-1) == NOVISITED)
        {
            if(*(game->board_n + x*game->size_of_board + y-1) == NONE)
            {
                *(game->board_visited + x*game->size_of_board + y-1) = VISITED;
                result++;
            }
            else if(*(game->board_n + x*game->size_of_board + y-1) == *(game->board_n + x*game->size_of_board + y))
                result += count_lib(game, x, y-1);
        }

    }
    if(y+1 <= game->size_of_board - 1)
    {
        if(*(game->board_visited + x*game->size_of_board + y+1) == NOVISITED)
        {
            if(*(game->board_n + x*game->size_of_board + y+1) == NONE)
            {
                *(game->board_visited + x*game->size_of_board + y+1) = VISITED;
                result++;
            }
            else if(*(game->board_n + x*game->size_of_board + y+1) == *(game->board_n + x*game->size_of_board + y))
                result += count_lib(game, x, y+1);
        }
    }
    return result;
}

void delete_stones(game_t *game, int x, int y)
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
    *(game->board_KO + x*game->size_of_board + y) = NOKO;

}

void delete_stones_direction(game_t *game, int x, int y, int x_checking, int y_checking)
{
    if(*(game->board_visited + x*game->size_of_board + y) == NOVISITED)
    {
        if(*(game->board_n + x*game->size_of_board + y) == *(game->board_n + x_checking*game->size_of_board + y_checking))
            delete_stones(game, x, y);
    }
}

void KO(game_t *game)
{
    for(int i = 0; i < game->size_of_board; i++)
    {
        for(int j = 0; j < game->size_of_board; j++)
        {
            if(*(game->board_KO + j*game->size_of_board + i) > 0)
                *(game->board_KO + j*game->size_of_board + i) = NOKO;
            else if(*(game->board_KO + j*game->size_of_board + i) != NOKO)
                *(game->board_KO + j*game->size_of_board + i) +=1;
        }
    }
}

bool KO_check(game_t *game,int x, int y)
{
    if(x-1 >= 0)
        if(*(game->board_KO + (x-1)*game->size_of_board + y) != NOKO)
            return false;
    if(x+1 <= game->size_of_board - 1)
        if(*(game->board_KO + (x+1)*game->size_of_board + y) != NOKO)
            return false;
    if(y-1 >= 0)
        if(*(game->board_KO + x*game->size_of_board + y-1) != NOKO)
            return false;
    if(y+1 <= game->size_of_board - 1)
        if(*(game->board_KO + x*game->size_of_board + y+1) != NOKO)
            return false;

    return true;
}

