#ifndef stone_managment_h
#define stone_managment_h

#define LEGENDLEFT 1    //1 dla planszy na prawo, 0 dla planszy na lewo
//zdefiniowanie polozenia legendy

#if LEGENDLEFT == 0
    #define LX 2
    #define BX 43
#else
    #define LX 43
    #define BX 2
#endif

#define LY 1
#define BY 2

// kolor pozycji na planszy
#define SBLACK 0
#define SWHITE 255
#define NONE 103
#define NONECHAR '+'
#define STONECHAR '0'
#define BORDER 47
#define NOVISITED 0
#define VISITED 1
#define NONE_LIBERTY -1
#define ESC 27
#define ENTER 0x0d
#define SPACE 32
#define SCOREPRINTX 13
#define CURSORSTARTY 0
#define CURSORSTARTX CURSORSTARTY*2
#define NOKO -1
#define STARTKO 0
#define LEGENDCOLOR 15
#define MAXDISPLAY 19
#define NONETERITORY 1
#define NOTFINISHED 0
#define FINISHED 1
#define WHITESCORE 6
#define BLACKSCORE 0
#define BLACKSCOREHANDICAP 0
#define WHITESCOREHANDICAP 0

#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

typedef struct{
    int white;
    int black;
}score_t;


typedef struct{
    int size_of_board;
    int startX;
    int startY;
    char *board;
    int *board_n;
    int *board_lib;
    char *board_visited;
    int *board_KO;
    int nowcolor;
    score_t score;
    bool white_f;
    bool black_f;
    int sf;
    int fin;
}game_t;

typedef struct{
    int x_d;
    int y_d;
    int x_b;
    int y_b;
    int xstart;
    int ystart;
}cursor_t;

#endif
