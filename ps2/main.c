#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "k.h"
#include "ui.h"
#include "hof.h"

int main() {
    struct player *list = calloc(2, sizeof(struct player));

    struct player player = {
            .name = "dsdsdsdsdsdsd",
            .score = 5
    };

    list[0].score = 999;
    strcpy(list[0].name, "lmao");
    list[1].score = 777;
    strcpy(list[1].name, "amogus");


    int size = load(list);

    printf("%d\n", size);

    add_player(list, &size, player);
    save(list, size);

    printf("%s %d\n", list[0].name, list[0].score );
    printf("%s %d\n", list[1].name, list[1].score );




    struct game game = {
            .board = {
                    {'A', 'A', ' ', 'A'},
                    {'A', 'A', ' ', 'A'},
                    {'A', 'A', ' ', 'A'},
                    {'A', 'A', ' ', 'A'}
            },
            .score = 0
    };


    add_random_tile(&game);
    is_game_won(game);
    is_move_possible(game);

    render(game);

    update(&game, -1, 0);
    update(&game, -1, 0);
    update(&game, 0, 1);


    render(game);


    return 0;
}
