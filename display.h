#ifndef display_h
#define display_h
#include "struct.h"
void legend();
void printnumber(int size_of_board); //drukuje liczbe wieksza niz 9
void print_score(game_t game);
void build(game_t game, int SY, int SX); //drukuje plansze pusta
void position(cursor_t cursor);
void alert(const char s[60]);
void alert_clear();
#endif

