#ifndef finish_h
#define finish_h
#include "struct.h"

void finish(game_t *game);
void countscore(game_t *game, int x, int y);
void countscore_direction(game_t *game, int x, int y);
void change_none_teritory(game_t *game, int x, int y, int change_from, int change_to);
void change_none_teritory_direction(game_t *game, int x, int y, int change_from, int change_to);
void check_for_delete(game_t *game, int x, int y);
int count_lib_finish(game_t* game, int x, int y, int color);
void delete_stones_finish(game_t *game, int x, int y);
bool check_lib_oponent(game_t *game, int x, int y, int color);
bool check_lib_oponent_direction(game_t *game, int x, int y, int color);

#endif

