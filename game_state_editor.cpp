#include <iostream>
#include "conio2.h"
#include "game_state_editor.h"
#include "display.h"
#include "variable_managment.h"
#include "stones.h"
#include "struct.h"

using namespace std;

void game_state_editor(game_t *game, cursor_t* cursor)
{
    char zn;
    gotoxy(1,1);
    cputs("Do you want to introduce a handicap(y/n):\n");

    zn = getch();
    while(zn != 'y' && zn != 'n')
    {
        cputs("Wrong character, try again\n");
        zn = getch();
    }

    clrscr();

    if(zn == 'n')
    {
        game->score.white = WHITESCORE;
        game->score.black = BLACKSCORE;
        return;
    }
    if(zn == 'y')
        legend_gse();
        build(*game, cursor->xstart, cursor->ystart);
        while(zn != 'a')
        {
            gotoxy(cursor->x_d, cursor->y_d);
            textbackground(RED);
            textcolor(RED);
            putch(*(game->board + cursor->x_b*game->size_of_board + cursor->y_b));
            position(*cursor);
            zn = getch();
            if(zn == 0)
            {
                gotoxy(cursor->x_d, cursor->y_d);
                textattr(*(game->board_n + cursor->x_b*game->size_of_board + cursor->y_b));
                putch(*(game->board + cursor->x_b*game->size_of_board + cursor->y_b));
                if(arrows_cursor(cursor, game->size_of_board))
                    build(*game, cursor->xstart, cursor->ystart);
            }
            if(zn == 'i')
            {
                if(*(game->board_n + cursor->x_b*game->size_of_board + cursor->y_b) != NONE)
                    alert("Cannot place stone here");
                else
                {
                    while(zn != ESC)
                    {
                        textattr(game->nowcolor);
                        gotoxy(cursor->x_d, cursor->y_d);
                        putch(*(game->board + cursor->x_b*game->size_of_board + cursor->y_b));
                        alert("Click ENTER - accept or ESC - cancel");
                        zn = getch();
                        if(zn == ENTER)
                        {
                            place_stone(game, *cursor, game->nowcolor);
                            break;
                        }
                    }
                    alert_clear();
                    game->score.white = WHITESCOREHANDICAP;
                    game->score.black = BLACKSCOREHANDICAP;
                }
            }
        }
    clrscr();
}
void legend_gse()
{
    textattr(LEGENDCOLOR);
    int i = LY;
    gotoxy(LX, i);
    cputs("       Vincenzo Piras s193218");
    i++;
    i++;
    gotoxy(LX, i);
    cputs("- arrows:  moving the cursor");
    i++;
    gotoxy(LX, i);
    cputs("           over the board");
    i++;
    i++;
    gotoxy(LX, i);
    cputs("- i:       place a stone on the board");
    i++;
    i++;
    gotoxy(LX, i);
    cputs("- a:       accept and start the game");
    i = i + 14;
    gotoxy(LX, i);
    cputs("Pozycja: ");
}
