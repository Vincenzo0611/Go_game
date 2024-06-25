#ifndef variable_managment_h
#define variable_managment_h
#include "struct.h"

int ini_size();  //pobiera rozmiar planszy od gracza
void set_empty_board(game_t *game); //czysci wszystkie tablice
void set_empty_visited(game_t *game);  //czysci tablice odwiedzonych
bool arrows_cursor(cursor_t *cursor, int size_of_board); //poruszanie kursorem

#endif


