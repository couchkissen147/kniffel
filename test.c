#include <stdio.h>
#include "conio.h"



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

} commands;

commands keypresses() {
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
            case 10:
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
}
int main(){

    while(1){
        commands ch = keypresses();
        // int ch = c_getch();
        
        printf("%d\n",ch);
        
    }
    return 0;
}

/*
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
*/
