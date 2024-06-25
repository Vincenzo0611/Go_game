#include<stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "display.h"
#include "finish.h"
#include "file_managment.h"
#include "game_state_editor.h"
#include "stones.h"
#include "variable_managment.h"
#include "struct.h"


using namespace std;

int main()
{
#ifndef __cplusplus
	Conio2_Init();
#endif
    settitle("Gra GO Vincenzo Piras");
    _setcursortype(_NOCURSOR);
    textmode(LASTMODE);
    _wscroll = 0;
    game_t game;
    cursor_t cursor;
    FILE *plik;

    game.size_of_board = ini_size();

    game.startX =  BX; //zdefiniowanie polozenia planszy
    game.startY = BY;

    cursor.x_b = CURSORSTARTX;
    cursor.y_b = CURSORSTARTY;
    cursor.x_d = game.startX + CURSORSTARTX;
    cursor.y_d = game.startY + CURSORSTARTY;
    cursor.xstart = CURSORSTARTX;
    cursor.ystart = CURSORSTARTY;
    game.fin = NOTFINISHED;


    //tworzenie tablic i wypisywanie na start
    game.board = (char *)malloc(game.size_of_board * game.size_of_board * sizeof(char));
    game.board_n = (int *)malloc(game.size_of_board * game.size_of_board * sizeof(int));
    game.board_lib = (int *)malloc(game.size_of_board * game.size_of_board * sizeof(int));
    game.board_visited = (char *)malloc(game.size_of_board * game.size_of_board * sizeof(char));
    game.board_KO = (int *)malloc(game.size_of_board * game.size_of_board * sizeof(int));

    if(game.board == NULL)
        return 0;
    if(game.board_n == NULL)
        return 0;
    if(game.board_lib == NULL)
        return 0;
    if(game.board_visited == NULL)
        return 0;
    if(game.board_KO == NULL)
        return 0;

    set_empty_board(&game);

    game.nowcolor = SBLACK; //czarne zaczynaja
    game_state_editor(&game, &cursor);

    //wypisywanie legendy i planszy
    legend();
    build(game, cursor.xstart, cursor.ystart);

    char zn;

    do
    {
        print_score(game);
        if(game.fin == NOTFINISHED)
        {
            gotoxy(cursor.x_d, cursor.y_d);
            textbackground(RED);
            textcolor(RED);
            putch(*(game.board + cursor.x_b*game.size_of_board + cursor.y_b));
            position(cursor);
        }
        zn = getch();
        alert_clear();
        if(zn == 'f' && game.fin == NOTFINISHED)
        {
            game.fin = FINISHED;
            build(game, cursor.xstart, cursor.ystart);
            finish(&game);
            if(game.score.white < game.score.black)
                alert("Black won! Click n to start new game or l to load another");
            else
                alert("White won! Click n to start new game or l to load another");

        }
        if(zn == 0 && game.fin == NOTFINISHED)
        {
            gotoxy(cursor.x_d, cursor.y_d);
            textattr(*(game.board_n + cursor.x_b*game.size_of_board + cursor.y_b));
            putch(*(game.board + cursor.x_b*game.size_of_board + cursor.y_b));
            if(arrows_cursor(&cursor, game.size_of_board))
                build(game, cursor.xstart, cursor.ystart);
        }
        if(zn == 'i' && game.fin == NOTFINISHED)
        {
            if(*(game.board_n + cursor.x_b*game.size_of_board + cursor.y_b) != NONE)
                alert("Cannot place stone here");
            else
            {
                if(check_suicide(&game, cursor.x_b, cursor.y_b))
                    alert("Cannot place stone here");
                else
                    place_stone_accept(&game, cursor);
            }
        }
        if(zn == 'n')
        {

            while(zn != ESC)
            {
                alert("Click ENTER - accept or ESC - cancel");
                zn = getch();
                if(zn == ENTER)
                {
                    clrscr();
                    set_empty_board(&game);
                    free(game.board);
                    free(game.board_n);
                    free(game.board_lib);
                    free(game.board_visited);
                    free(game.board_KO);

                    game.size_of_board = ini_size();

                    game.board = (char *)malloc(game.size_of_board * game.size_of_board * sizeof(char));
                    game.board_n = (int *)malloc(game.size_of_board * game.size_of_board * sizeof(int));
                    game.board_lib = (int *)malloc(game.size_of_board * game.size_of_board * sizeof(int));
                    game.board_visited = (char *)malloc(game.size_of_board * game.size_of_board * sizeof(char));
                    game.board_KO = (int *)malloc(game.size_of_board * game.size_of_board * sizeof(int));

                    if(game.board == NULL)
                        return 0;
                    if(game.board_n == NULL)
                        return 0;
                    if(game.board_lib == NULL)
                        return 0;
                    if(game.board_visited == NULL)
                        return 0;
                    if(game.board_KO == NULL)
                        return 0;


                    cursor.x_b = CURSORSTARTX;
                    cursor.y_b = CURSORSTARTY;
                    cursor.x_d = game.startX + CURSORSTARTX;
                    cursor.y_d = game.startY + CURSORSTARTY;
                    cursor.xstart = CURSORSTARTX;
                    cursor.ystart = CURSORSTARTY;
                    cursor.xstart = CURSORSTARTX;
                    cursor.ystart = CURSORSTARTY;
                    set_empty_board(&game);
                    game.nowcolor = SBLACK;
                    game.fin = NOTFINISHED;
                    game_state_editor(&game, &cursor);
                    build(game, cursor.xstart, cursor.ystart);
                    legend();
                    break;
                }
            }
            alert_clear();

        }
        if(zn == 's' && game.fin == NOTFINISHED)
        {
            char name[25];
            take_file_name_save(name);
            fopen_s(&plik, name,"w");
            if(plik != NULL)
            {
                fwrite(&game, sizeof(game_t), 1, plik);
                fwrite(game.board, game.size_of_board*game.size_of_board*sizeof(char), 1 ,plik);
                fwrite(game.board_n, game.size_of_board*game.size_of_board*sizeof(int), 1 ,plik);
                fwrite(game.board_lib, game.size_of_board*game.size_of_board*sizeof(int), 1 ,plik);
                fwrite(game.board_visited, game.size_of_board*game.size_of_board*sizeof(char), 1 ,plik);
                fwrite(game.board_KO, game.size_of_board*game.size_of_board*sizeof(int), 1 ,plik);
                fclose(plik);
            }
            legend();
            build(game, cursor.xstart, cursor.ystart);
        }
        if(zn == 'l')
        {
            char name[25];
            take_file_name_load(name);
            fopen_s(&plik, name,"r");
            if(plik != NULL)
            {
                free(game.board);
                free(game.board_n);
                free(game.board_lib);
                free(game.board_visited);
                free(game.board_KO);

                fread(&game, sizeof(game_t), 1 ,plik);

                game.board = (char *)malloc(game.size_of_board * game.size_of_board * sizeof(char));
                game.board_n = (int *)malloc(game.size_of_board * game.size_of_board * sizeof(int));
                game.board_lib = (int *)malloc(game.size_of_board * game.size_of_board * sizeof(int));
                game.board_visited = (char *)malloc(game.size_of_board * game.size_of_board * sizeof(char));
                game.board_KO = (int *)malloc(game.size_of_board * game.size_of_board * sizeof(int));

                if(game.board == NULL)
                    return 0;
                if(game.board_n == NULL)
                    return 0;
                if(game.board_lib == NULL)
                    return 0;
                if(game.board_visited == NULL)
                    return 0;
                if(game.board_KO == NULL)
                    return 0;

                fread(game.board, game.size_of_board*game.size_of_board*sizeof(char), 1 ,plik);
                fread(game.board_n, game.size_of_board*game.size_of_board*sizeof(int), 1 ,plik);
                fread(game.board_lib, game.size_of_board*game.size_of_board*sizeof(int), 1 ,plik);
                fread(game.board_visited, game.size_of_board*game.size_of_board*sizeof(char), 1 ,plik);
                fread(game.board_KO, game.size_of_board*game.size_of_board*sizeof(int), 1 ,plik);
            fclose(plik);
            }
            game.startX =  BX; //zdefiniowanie polozenia planszy
            game.startY = BY;
            cursor.x_b = CURSORSTARTX;
            cursor.y_b = CURSORSTARTY;
            cursor.x_d = game.startX + CURSORSTARTX;
            cursor.y_d = game.startY + CURSORSTARTY;
            cursor.xstart = CURSORSTARTX;
            cursor.ystart = CURSORSTARTY;
            legend();
            build(game, cursor.xstart, cursor.ystart);
        }
    }while(zn != 'q');


    free(game.board);
    free(game.board_n);
    free(game.board_lib);
    free(game.board_visited);
    free(game.board_KO);

    return 0;
}
