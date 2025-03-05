#ifndef main_h
#define main_h


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conio.h"

#define LINES 30
#define COLUMNS 62  // 146


typedef enum
{
    Ones        = 0,
    Twos        = 1,
    Threes      = 2,
    Fours       = 3,
    Fives       = 4,
    Sixes       = 5,

    Kind3       = 6,
    Kind4       = 7,
    FullHouse   = 8,
    smStr       = 9,
    lgStr       = 10,
    Kniffel     = 11,
    Chance      = 12,

    die1        = 13,
    die2        = 14,
    die3        = 15,
    die4        = 16,
    die5        = 17,
    roll        = 18,

    USum        = 19,
    Bonus       = 20,
    UTotal1     = 21,

    LTotal      = 22,
    UTotal2     = 23,
    Score       = 24,

} special;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
    DIE1,
    DIE2,
    DIE3,
    DIE4,
    DIE5,
    ROLL,
    ENTER,

} command;

struct gamestate {
    special currentSelection;
    int dice[5];
    int diceToggled[5];
    int rolls;
    int scores[25];

};

char map[LINES][COLUMNS] = {
    "+-------+ +-------+ +-------+ +-------+ +-------+         ",
    "|       | |       | |       | |       | |       |    0/3  ",
    "|       | |       | |       | |       | |       |         ",
    "|       | |       | |       | |       | |       |         ",
    "+-------+ +-------+ +-------+ +-------+ +-------+  Würfeln",
    "   (x)       ( )       ( )       ( )       ( )       ( )  ",
    "                                                          ",
    "( ) Einser         [  ]  |      |                         ",
    "( ) Zweier         [  ]  |      |                         ",
    "( ) Dreier         [  ]  |      |                         ",
    "( ) Vierer         [  ]  |      |                         ",
    "( ) Fuenfer        [  ]  |      |                         ",
    "( ) Sechser        [  ]  |      |                         ",
    "                         |                                ",
    "    Summe                |      |                         ",
    "    Bonus (+35)          |                                ",
    "    Gesamt oben          |                                ",
    "                         |                                ",
    "( ) Dreierpasch    [  ]  |      |                         ",
    "( ) Viererpasch    [  ]  |      |                         ",
    "( ) Full House     [  ]  |      |                         ",
    "( ) Kleine Strasse [  ]  |      |                         ",
    "( ) Grosse Strasse [  ]  |      |                         ",
    "( ) Kniffel        [  ]  |      |                         ",
    "( ) Chance         [  ]  |      |                         ",
    "                         |                                ",
    "    Gesamt unten         |                                ",
    "    Gesamt oben          |                                ",
    "    Erbegnis             |                                "
 };

special nextSelection[19][4] = {
    //              UP DOWN LEFT RIGHT
    /*Ones*/       {die1,Twos,Ones,Ones},
    /*Twos*/       {Ones,Threes,Twos,Twos},
    /*Threes*/     {Twos,Fours,Threes,Threes},
    /*Fours*/      {Threes,Fives,Fours,Fours},
    /*Fives*/      {Fours,Sixes,Fives,Fives},
    /*Sixes*/      {Fives,Kind3,Sixes,Sixes},
    /*Kind3*/      {Sixes,Kind4,Kind3,Kind3},
    /*Kind4*/      {Kind3,FullHouse,Kind4,Kind4},
    /*FullHouse*/  {Kind4,smStr,FullHouse,FullHouse},
    /*smStr*/      {FullHouse,lgStr,smStr,smStr},
    /*lgStr*/      {smStr,Kniffel,lgStr,lgStr},
    /*Kniffel*/    {lgStr,Chance,Kniffel,Kniffel},
    /*Chance*/     {Kniffel,Chance,Chance,Chance},
    /*die1*/       {die1,Ones,die1,die2},
    /*die2*/       {die2,Ones,die1,die3},
    /*die3*/       {die3,Ones,die2,die4},
    /*die4*/       {die4,Ones,die3,die5},
    /*die5*/       {die5,Ones,die4,roll},
    /*roll*/       {roll,Ones,die5,roll},
};

int coordsSelection[19][2] = {
    /*Ones*/       {7,1},
    /*Twos*/       {8,1},
    /*Threes*/     {9,1},
    /*Fours*/      {10,1},
    /*Fives*/      {11,1},
    /*Sixes*/      {12,1},
    /*Kind3*/      {18,1},
    /*Kind4*/      {19,1},
    /*FullHouse*/  {20,1},
    /*smStr*/      {21,1},
    /*lgStr*/      {22,1},
    /*Kniffel*/    {23,1},
    /*Chance*/     {24,1},
    /*die1*/       {5,4},
    /*die2*/       {5,14},
    /*die3*/       {5,24},
    /*die4*/       {5,34},
    /*die5*/       {5,44},
    /*roll*/       {5,54}
};  




#endif // main_h