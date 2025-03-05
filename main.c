# include "main.h"

command getkey() {
    switch(c_getch()) {
        case 'q':
            return QUIT;
            break;
        case 'r':
            return ROLL;
            break;
        case '1':
            return DIE1;
            break;
        case '2':   
            return DIE2;
            break;
        case '3':
            return DIE3;
            break;
        case '4':
            return DIE4;
            break;
        case '5':
            return DIE5;
            break;
        case 'h':
            return LEFT;
            break;
        case 'j':
            return DOWN;
            break;
        case 'k':
            return UP;
            break;
        case 'l':
            return RIGHT;
            break;
        case 10:    // "Enter" pressed
            return ENTER;
            break;
        case ' ':
            return ENTER;
            break;
        case '\033': // if the first value is esc
            c_getch(); // skip the [
            switch(c_getch()) { // the real value
                case 'A':
                    return UP;
                    break;
                case 'B':
                    return DOWN;
                    break;
                case 'C':
                    return RIGHT;
                    break;
                case 'D':
                    return LEFT;
                    break;
            break;
        }
    }
    return -1;
}

void mapSetSelection(special s) {
    int i = coordsSelection[s][0];
    int j = coordsSelection[s][1];
    map[i][j] = 'x';
}

void mapClearSelection(special s) {
    int i = coordsSelection[s][0];
    int j = coordsSelection[s][1];
    map[i][j] = ' ';
}

void changeSelection(struct gamestate* game, command dir) {
    special selection = game->currentSelection;
    mapClearSelection(selection);
    special next = nextSelection[selection][dir];
    mapSetSelection(next);
    game->currentSelection = next;
}

void hideDie(int die) {

    for(int i=1;i<=3;i++) {
        for(int j=1;j<=7;j++) {
            map[i][j+die*10] = ' ';
        }
    }
}

void showDie(int die, int value) {
    int off = die*10;
    if(value == 0) {
        hideDie(die);
        return;
    }
    if(value >= 4) {
        map[1][2+off] = 'o';
        map[3][6+off] = 'o';
    }
    if(value %2 == 1) {
        map[2][4+off] = 'o';
    }
    if(value > 1) {
        map[1][6+off] = 'o';
        map[3][2+off] = 'o';
    }
    if(value == 6) {
        map[2][2+off] = 'o';
        map[2][6+off] = 'o';
    }
}

void toggleDie(struct gamestate* game,command key) {
    int die = key-5;
    game->diceToggled[die] ^= 1;
    if(game->diceToggled[die] == 1) {
        int value = game->dice[die];
        showDie(die, value);
    } else {
        hideDie(die);
    }
}

void showRolls(struct gamestate* game) {
    map[1][53] = '0' + game->rolls;
}

int getScore(int d[5], special field) {
    int ret = 0;
    int p[6] = {0,0,0,0,0,0};
    for(int i=0;i<5;i++) {
        p[d[i]-1]++;
    }
    switch(field) {
        case Ones:
            ret = p[0]*1;
            break;
        case Twos:
            ret = p[1]*2;
            break;
        case Threes:
            ret = p[2]*3;
            break;
        case Fours:
            ret = p[3]*4;
            break;
        case Fives:
            ret = p[4]*5;
            break;
        case Sixes:
            ret = p[5]*6;
            break;
        case Kind3:
            if(p[0]>=3 || p[1]>=3 || p[2]>=3 || p[3]>=3 || p[4]>=3 || p[5]>=3) {
                for(int i=0;i<5;i++) 
                        ret += d[i];
            }
            break;
        case Kind4:
            if(p[0]>=4 || p[1]>=4 || p[2]>=4 || p[3]>=4 || p[4]>=4 || p[5]>=4) {
                for(int i=0;i<5;i++) 
                        ret += d[i];
            }
            break;
        case FullHouse:
            if(p[0]==5 || p[1]==5 || p[2]==5 || p[3]==5 || p[4]==5 || p[5]==5) {
                ret = 25;
                break;
            }
            if((p[0]==3 || p[1]==3 || p[2]==3 || p[3]==3 || p[4]==3 || p[5]==3) && (p[0]==2 || p[1]==2 || p[2]==2 || p[3]==2 || p[4]==2  || p[5]==2)) {
                ret = 25;
            }
            break;
        case smStr:
            if((p[0]>=1 && p[1]>=1 && p[2]>=1 && p[3]>=1) || (p[1]>=1 && p[2]>=1 && p[3]>=1 && p[4]>=1) || (p[2]>=1 && p[3]>=1 && p[4]>=1 && p[5]>=1)) {
                ret = 30;
            }
            break;
        case lgStr:
            if((p[0]==1 && p[1]==1 && p[2]==1 && p[3]==1 && p[4]==1) || (p[1]>=1 && p[2]==1 && p[3]==1 && p[4]==1 && p[5]==1)) {
                ret = 40;
            }
            break;
        case Kniffel:
            if(p[0]==5 || p[1]==5 || p[2]==5 || p[3]==5 || p[4]==5 || p[5]==5) {
                ret = 50;
            }
            break;
        case Chance:
            ret = d[0]+d[1]+d[2]+d[3]+d[4];
    }
    return ret;
}

void showPossibleScores(struct gamestate* game) {
    
    for(int i=0;i<13;i++) {
        int s = getScore(game->dice,i);
        if(i<=5) {
            int tmp = s/10;
            map[i+7][20] = tmp +'0';
            map[i+7][21] = s%10 +'0';
        } else {
            int tmp = s/10;
            map[i+12][20] = tmp +'0';
            map[i+12][21] = s%10 +'0';
        }
    }
    
}

void rollDice(struct gamestate* game) {
    if(game->diceToggled[0]+game->diceToggled[1]+game->diceToggled[2]+game->diceToggled[3]+game->diceToggled[4] == 5) {
        return;
    }
    srandom(time(NULL));
    game->rolls++;
    showRolls(game);
    for(int i=0;i<5;i++) {
        if(game->diceToggled[i] == 0) {
            int ran = (random()%6) +1;
            game->dice[i] = ran;
            toggleDie(game, i+5);
        }
    }
    showPossibleScores(game);
}

void enterScore(struct gamestate* game, special field) {
    int s = getScore(game->dice, field);
    game->scores[field] = s;
}

void confirmSelection(struct gamestate* game) {
    special selection = game->currentSelection;
    if(selection == roll){
            rollDice(game);
    }
    else if(selection >= 13 && game->rolls < 3 && game->rolls > 0) {  // Die selected
        switch(selection){
            case die1:
                toggleDie(game,DIE1);
                break;
            case die2:
                toggleDie(game,DIE2);
                break;
            case die3:
                toggleDie(game,DIE3);
                break;
            case die4:
                toggleDie(game,DIE4);
                break;
            case die5:
                toggleDie(game,DIE5);
                break;
            case roll:
                rollDice(game);
                break;
        }
    } else if(game->rolls > 0){
        switch(selection) {
            case Ones:
                enterScore(game,Ones);
                break;
            case Twos:
                enterScore(game,Twos);
                break;
            case Threes:
                enterScore(game,Threes);
                break;
            case Fours:
                enterScore(game,Fours);
                break;
            case Fives:
                enterScore(game,Fives);
                break;
            case Sixes:
                enterScore(game,Sixes);
                break;
            case Kind3:
                enterScore(game,Kind3);
                break;
            case Kind4:
                enterScore(game,Kind4);
                break;
            case FullHouse:
                enterScore(game,FullHouse);
                break;
            case smStr:
                enterScore(game,smStr);
                break;
            case lgStr:
                enterScore(game,lgStr);
                break;
            case Kniffel:
                enterScore(game,Kniffel);
                break;
            case Chance:
                enterScore(game,Chance);
                break;
        }
    }

}

struct gamestate initGamestate() {
    struct gamestate game = {
                                die1,
                                {0,0,0,0,0},
                                {0,0,0,0,0},
                                0,
                                {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                            };
    return game;
}

struct gamestate init() {
    struct gamestate game = initGamestate();
    
    return game;
}

void showScores(struct gamestate* game) {
    int off = 0;
    for(int i=0;i<25;i++) {
        int s = game->scores[i];
        if(i <= 5) {
            off = 7;
        } else if(i <= 12){
            off = 12;
        } else if(i <= 18) {
            off = 0;
        } else if(i <= 21) {
            off = -5;
        } else {
            off = 4;
        }
        if(off != 0) {
            if(s == -1) {
                map[i+off][28] = ' ';
                map[i+off][29] = ' ';
            } else if(s <= 100) {
                int tmp = s/10;
                map[i+off][28] = tmp +'0';
                map[i+off][29] = s%10 +'0';    
            } else {
                int tmp = s/10;
                int tmp2= s/100;
                map[i+off][27] = tmp2 + '0';
                map[i+off][28] = tmp +'0';
                map[i+off][29] = s%10 +'0'; 
            }
        }
    }
}

void printMap(struct gamestate* game) {
    showScores(game);
    printf("\033[H\033[J\033[H");
    for(int i=0;i<LINES;i++) {
            printf("%s\n",map[i]);
    }
    fflush(stdout);
}

int main() {
    struct gamestate game = init();
    printMap(&game);

    while(1) {
        command key = getkey();

        if(key <= 3) {  // Arrowkey
            changeSelection(&game, key);
        } 
        else if(key == QUIT) {
            printf("\033[H\033[J");
            return 0;
        }
        else if(key <= 9 && game.rolls < 3 && game.rolls > 0) { // Number 1-5
            toggleDie(&game, key);
        }
        else if(key == ROLL && game.rolls < 3) {
            rollDice(&game);
        }
        else if(key == ENTER) {
            confirmSelection(&game);
        }

        


        printMap(&game);
    }
    return 0;
}