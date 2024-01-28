#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "k.h"


bool is_game_won(const struct game game) {
    for (int row = 0; row < SIZE; row++) {
        for (int collumn = 0; collumn < SIZE; collumn++) {
            if (game.board[row][collumn] == 75) {
                return true;
            }
        }
    }
    return false;

}

bool is_move_possible(const struct game game) {

    for (int row = 0; row < SIZE; row++) {
        for (int collumn = 0; collumn < SIZE; collumn++) {
            if (game.board[row][collumn] == ' ') {
                return true;
            }
        }
    }


    for (int row = 0; row < SIZE; row++) {
        for (int collumn = 1; collumn < SIZE; collumn++) {
            if (game.board[row][collumn] == game.board[row][collumn - 1]) {
                return true;
            }
        }
    }

    for (int row = 1; row < SIZE; row++) {
        for (int collumn = 0; collumn < SIZE; collumn++) {
            if (game.board[row][collumn] == game.board[row - 1][collumn]) {
                return true;
            }
        }
    }

    for (int row = 0; row < SIZE; row++) {
        for (int collumn = 0; collumn < SIZE; collumn++) {
            if (game.board[row][collumn] == game.board[row + 1][collumn]) {
                return true;
            }
        }
    }


    for (int row = 0; row < SIZE; row++) {
        for (int collumn = 0; collumn < 3; collumn++) {
            if (game.board[row][collumn] == game.board[row][collumn + 1]) {
                return true;
            }
        }
    }

    return false;
}

int go_right(char *line, int *score);
int go_left(char* line, int *score);


bool update(struct game *game, int dy, int dx) {
    int smer = -1;


    if (dy == 0 && dx == 1) {
        smer = 1; // вправо
    } else if (dy == 0 && dx == -1) {
        smer = 2; // влево
    } else if (dy == 1 && dx == 0) {
        smer = 3; // вниз
    } else if (dy == -1 && dx == 0) {
        smer = 4; // вверх
    }

    int score = 0;
    int i, j;

    bool moved = false;

    if (smer == 1 || smer == 2) {
        for (i = 0; i < SIZE; i++) {
            char row[SIZE];

            for (j = 0; j < SIZE; j++) {
                row[j] = game->board[i][j];
            }

            if (smer == 1) {
                go_right(row, &score);
            }
            else {
                go_left(row, &score);
            }

            game->score += score;

            for (j = 0; j < SIZE; j++) {
                if (game->board[i][j] != row[j]) {
                    moved = true;
                }
                game->board[i][j] = row[j];
            }
        }
    } else if (smer == 3 || smer == 4) {
        for (i = 0; i < SIZE; i++) {
            char collumn[SIZE];

            for (j = 0; j < SIZE; j++) {
                collumn[j] = game->board[j][i];
            }

            if (smer == 3) {
                go_right(collumn, &score);
            }
            else {
                go_left(collumn, &score);
            }

            game->score += score;

            for (j = 0; j < SIZE; j++) {
                if (game->board[j][i] != collumn[j]) {
                    moved = true;
                }
                game->board[j][i] = collumn[j];
            }
        }
    }

    return moved;
}


void add_random_tile(struct game *game) {
    int row = rand() % SIZE;
    int collumn = rand() % SIZE;

    while (game->board[row][collumn] != ' ') {
        row = rand() % SIZE;
        collumn = rand() % SIZE;
    }

    game->board[row][collumn] = (rand() % 2 == 0) ? 'A' : 'B';
}


int go_right(char *line, int *score) {
    if (line[0] == ' ' && line[1] == ' ' && line[2] == ' ' && line[3] == ' ') {
        return -1;
    }

    bool moved = false;
    for (int i = SIZE - 2; i >= 0; i--) {
        if (line[i] != ' ') {
            int j = i + 1;
            while (j < SIZE && line[j] == ' ') {
                j++;
            }
            if (j < SIZE && line[i] == line[j]) {
                line[j]++;
                line[i] = ' ';
                *score += (int)pow(2, line[j] - 'A');
            } else if (j - 1 != i) {
                line[j - 1] = line[i];
                line[i] = ' ';
                moved = true;
            }
        }
    }
    return moved ? 0 : -1;
}

int go_left(char *line, int *score) {
    if (line[0] == ' ' && line[1] == ' ' && line[2] == ' ' && line[3] == ' ') {
        return -1;
    }
    bool moved = false;
    for (int i = 1; i < SIZE; i++) {
        if (line[i] != ' ') {
            int j = i - 1;
            while (j >= 0 && line[j] == ' ') {
                j--;
            }
            if (j >= 0 && line[i] == line[j]) {
                line[j]++;
                line[i] = ' ';
                *score += (int)pow(2, line[j] - 'A');
            } else if (j + 1 != i) {
                line[j + 1] = line[i];
                line[i] = ' ';
                moved = true;
            }
        }
    }
    return moved ? 0 : -1;
}
