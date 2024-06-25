#include <iostream>
#include "conio2.h"
#include "struct.h"

using namespace std;

void legend()
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
    cputs("- q:       quit the program");
    i++;
    i++;
    gotoxy(LX, i);
    cputs("- n:       start a new game");
    i++;
    i++;
    gotoxy(LX, i);
    cputs("- i:       place a stone on the board");
    i++;
    i++;
    gotoxy(LX, i);
    cputs("- s:       save the game state");
    i++;
    i++;
    gotoxy(LX, i);
    cputs("- l:       load the game state");
    i++;
    i++;
    gotoxy(LX, i);
    cputs("- f:       finish the game");
    i++;
    i++;
    gotoxy(LX, i);
    cputs("BLACK SCORE:");
    i++;
    gotoxy(LX, i);
    cputs("WHITE SCORE:");
    i++;
    i++;
    i++;
    gotoxy(LX, i);
    cputs("Pozycja: ");
}
void printnumber(int n)
{
    int number = n % 10;
    n = n /10;
    if(n > 0)
        printnumber(n);
    putch((char)(number+48));
}

void print_score(game_t game)
{
    textbackground(BLACK);
    textcolor(WHITE);
    int i = LY + 17;
    gotoxy(LX + SCOREPRINTX, i);
    cputs("       ");
    gotoxy(LX + SCOREPRINTX, i);
    printnumber(game.score.black);
    putch('.');
    putch('0');
    i++;
    gotoxy(LX + SCOREPRINTX, i);
    cputs("       ");
    gotoxy(LX + SCOREPRINTX, i);
    printnumber(game.score.white);
    putch('.');
    putch('5');
    i++;
    i++;
    gotoxy(LX + SCOREPRINTX, i);
    if(game.nowcolor == SBLACK)
        cputs("BLACK'S TURN");
    else
        cputs("WHITE'S TURN");
}

void build(game_t game, int SY, int SX)
{
    int size_of_board;

    if(game.size_of_board <= MAXDISPLAY)
        size_of_board = game.size_of_board;
    else
        size_of_board = MAXDISPLAY;

    textattr(NONE);
    for(int i = 0; i < size_of_board; i++)
    {
        gotoxy(game.startX,(game.startY+i));
        for(int j = 0; j < size_of_board; j++)
        {
            textattr(*(game.board_n + (j+SY)*game.size_of_board + i + SX));
            putch(*(game.board + (j+SY)*game.size_of_board + i+ SX));
            textattr(NONE);
            putch(' ');
        }
    }
    textattr(BORDER);
    for(int i = 0; i < size_of_board + 2; i++)
    {
        gotoxy(game.startX - 1, game.startY - 1 + i);
        putch('|');
    }
    for(int i = 0; i < size_of_board + 2; i++)
    {
        gotoxy(game.startX + (2*(size_of_board) - 1), game.startY - 1 + i);
        putch('|');
    }
    gotoxy(game.startX - 1, game.startY - 1);
    for(int j = 0; j < 2*(size_of_board+1) - 1; j++)
        putch('-');
    gotoxy(game.startX - 1, game.startY + size_of_board);
    for(int j = 0; j < 2*(size_of_board+1) - 1; j++)
        putch('-');

}

void position(cursor_t cursor)
{
    textbackground(BLACK);
    textcolor(WHITE);
    int i = LY + 22;
    gotoxy(LX, i);
    clreol();
    cputs("X: ");
    printnumber(cursor.x_b + 1);
    cputs("  Y: ");
    printnumber(cursor.y_b + 1);
}

void alert(const char s[60])
{
    textbackground(BLACK);
    textcolor(WHITE);
    int i = LY + 23;
    gotoxy(2, i);
    cputs(s);
}

void alert_clear()
{
    textbackground(BLACK);
    textcolor(WHITE);
    int i = LY + 23;
    gotoxy(2, i);
    clreol();
}
