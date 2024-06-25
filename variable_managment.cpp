#include <iostream>
#include "conio2.h"
#include "struct.h"

using namespace std;

int ini_size()
{
    int size_of_board;
    char zn;
    gotoxy(1,1);
    cputs("Choose size of the board:\n");
    cputs("Click 1 for 9x9 board size:\n");
    cputs("Click 2 for 13x13 board size:\n");
    cputs("Click 3 for 19x19 board size:\n");
    cputs("Click 4 for another board size:\n");

    zn = getch();

    while(zn < '1' || zn > '4')
    {
        cputs("Wrong number, try again:\n");
        zn = getch();
    }

    clrscr();

    if(zn == '1')
        return 9;
    if(zn == '2')
        return 13;
    if(zn == '3')
        return 19;
    gotoxy(1,1);
    cputs("Size of the board and click enter to confirm:\n");
    while(1)
    {
        size_of_board = 0;
        zn = getch();
        while((int)zn != SPACE && (int)zn != ENTER)
        {
            if(zn >= '0' && zn <= '9')
            {
                putch(zn);
                size_of_board = size_of_board * 10;
                size_of_board += (int)(zn - 48);
                zn = getch();
            }
            else
            {
                size_of_board = 0;
                break;
            }
        }
        if(size_of_board > 1)
            break;
        cputs("\nWrong number, try again: \n");
    }
    clrscr();
    return size_of_board;

}

void set_empty_board(game_t *game)
{
    for (int i = 0; i < game->size_of_board; i++)
      for (int j = 0; j < game->size_of_board; j++)
      {
         *(game->board + i*game->size_of_board + j) = NONECHAR;
         *(game->board_n + i*game->size_of_board + j) = NONE;
         *(game->board_lib + i*game->size_of_board + j) = NONE_LIBERTY;
         *(game->board_KO + i*game->size_of_board + j) = NOKO;
      }
}

void set_empty_visited(game_t *game)
{
    for (int i = 0; i < game->size_of_board; i++)
      for (int j = 0; j < game->size_of_board; j++)
         *(game->board_visited + i*game->size_of_board + j) = NOVISITED;
}
bool arrows_cursor(cursor_t *cursor, int size_of_board)
{
    char zn;
    zn = getch();
    bool result = false;
    if(zn == UP) //up
    {
        if(cursor->y_b > 0)
        {
            cursor->y_b -= 1;
            if(cursor->y_b < cursor->ystart)
            {
                cursor->ystart -= 1;
                result = true;
            }
            else
                cursor->y_d -= 1;
        }
    }
    else if(zn == DOWN) //down
    {
        if(cursor->y_b < size_of_board - 1)
        {
            cursor->y_b += 1;
            if(cursor->y_b >= MAXDISPLAY + cursor->ystart)
            {
                cursor->ystart += 1;
                result = true;
            }
            else
                cursor->y_d += 1;
        }
    }
    else if(zn == LEFT) //left
    {
        if(cursor->x_b > 0)
        {
            cursor->x_b -= 1;
            if(cursor->x_b < cursor->xstart)
            {
                cursor->xstart -= 1;
                result = true;
            }
            else
                cursor->x_d -= 2;
        }
    }
    else if(zn == RIGHT) //right
    {
        if(cursor->x_b < size_of_board-1)
        {
            cursor->x_b += 1;
            if(cursor->x_b >= MAXDISPLAY + cursor->xstart)
            {
                cursor->xstart += 1;
                result = true;
            }
            else
                cursor->x_d += 2;
        }
    }
    return result;
}
