#include <iostream>
#include "conio2.h"
#include "struct.h"

using namespace std;

void take_file_name_save(char name[])
{
    char zn;
    int i = 0;
    clrscr();

    for(int j = 0; j < 25; j++)
        name[j] = '\0';

    gotoxy(1,1);
    cputs("Give save name (max 20 character) or click ESC to cancel:\n");
    gotoxy(1, 2);
    zn = getch();
    if(zn == ESC)
        return;
    while((int)zn != SPACE && (int)zn != ENTER)
    {
        if(i == 20)
        {
            gotoxy(1,1);
            cputs("\nToo long name, try again        \n");
            break;
        }
        putch(zn);
        name[i] = zn;
        i++;
        zn = getch();
        if(zn == ESC)
        {
            clrscr();
            for(int j = 0; j < 25; j++)
                name[j] = '\0';
            return;
        }
    }
    name[i] = '.';
    i++;
    name[i] = 'b';
    i++;
    name[i] = 'i';
    i++;
    name[i] = 'n';
    i++;
    name[i] = '\0';
    clrscr();
}

void take_file_name_load(char name[])
{
    char zn;
    int i;
    clrscr();
    gotoxy(1,1);
    cputs("Give save name (max 20 character):\n");
    while(1)
    {
        i = 0;
        for(int j = 0; j < 25; j++)
            name[j] = '\0';
        gotoxy(1, 2);
        zn = getch();
        if(zn == ESC)
            break;
        while((int)zn != SPACE && (int)zn != ENTER)
        {
            if(i == 20)
            {
                gotoxy(1,1);
                cputs("\nToo long name, try again        \n");
                break;
            }
            putch(zn);
            name[i] = zn;
            i++;
            zn = getch();
            if(zn == ESC)
            {
                clrscr();
                for(int j = 0; j < 25; j++)
                    name[j] = '\0';
                return;
            }
        }
        name[i] = '.';
        i++;
        name[i] = 'b';
        i++;
        name[i] = 'i';
        i++;
        name[i] = 'n';
        i++;
        name[i] = '\0';
        FILE* plik;
        fopen_s(&plik, name, "r");
        if(plik == NULL)
        {
            clrscr();
            gotoxy(1,1);
            cputs("File with this name do not exist, try again or click ESC to cancel\n");
        }
        else
        {
            fclose(plik);
            break;
        }
    }
    clrscr();
}
