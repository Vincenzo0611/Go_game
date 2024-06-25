#ifndef stones_h
#define stones_h
#include "struct.h"

void place_stone(game_t *game, cursor_t cursor, int color);
void place_stone_accept(game_t *game, cursor_t cursor);
bool check_suicide(game_t *game, int x, int y);
bool check_suicide_direction(game_t *game,int x, int y, int x_checking, int y_checking);
int count_lib(game_t *game, int x, int y);
void delete_stones(game_t *game, int x, int y);
void delete_stones_direction(game_t *game, int x, int y, int x_checking, int y_checking);
void KO(game_t *game);
bool KO_check(game_t *game,int x, int y);

#endif


