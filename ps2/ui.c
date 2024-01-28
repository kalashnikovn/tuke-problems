#include <stdio.h>
#include "k.h"


void render(const struct game game){
    printf("score: %d\n", game.score);

    for(int row = 0; row < SIZE; row++){
        printf("+---+---+---+---+\n|");
        for(int collumn = 0; collumn < SIZE; collumn++){
            printf(" %c |", game.board[row][collumn]);
        }
        printf("\n");
    }




    printf("+---+---+---+---+\n");
}

