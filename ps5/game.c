#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

void play_game(struct game* game) {
    while(game->state == PLAYING) {
        execute_command(game, parse_input(game->parser, "KONIEC"));
    }
};

struct game* create_game() {
    struct game* game = calloc(1, sizeof(struct game));
    struct parser* parser = create_parser();
    struct room* room = create_room("izba", "This is your startpoint, now - is time to explore..");
    struct container* world = create_container(NULL, ROOM, room);
    struct backpack* backpack = create_backpack(5);
    world->room = room;
    game->state = PLAYING;
    game->parser = parser;
    game->world = world;
    game->current_room = world->room;
    game->backpack = backpack;

    return game;
}

struct game* destroy_game(struct game* game) {
    if(game != NULL) {
        game->current_room = NULL;
        game->world = destroy_containers(game->world);
        game->parser = destroy_parser(game->parser);
        game->backpack = destroy_backpack(game->backpack);
        free(game);
    }

    return NULL;
}

void execute_command(struct game* game, struct command* command) {
    if(game != NULL && command != NULL) {
        struct command* new_command = create_command(command->name, command->description, NULL, 0);
        if(strcmp(new_command->name, "SEVER") == 0) {
            game->current_room = game->current_room->north;
        } else if(strcmp(new_command->name, "JUH") == 0) {
            game->current_room = game->current_room->south;
        } else if(strcmp(new_command->name, "ZAPAD") == 0) {
            game->current_room = game->current_room->west;
        } else if(strcmp(new_command->name, "VYCHOD") == 0) {
            game->current_room = game->current_room->east;
        } else if(strcmp(new_command->name, "RESTART") == 0) {
            game->state = RESTART;
        } else if(strcmp(new_command->name, "KONIEC") == 0) {
            game->state = GAMEOVER;
        } else if(strcmp(new_command->name, "ROZHLIADNI SA") == 0) {
            show_room(game->current_room);
        } else if(strcmp(new_command->name, "PRIKAZY") == 0) {
            struct container* pointer = game->parser->commands;
            while(pointer != NULL) {
                printf("%s - ", pointer->command->name);
                printf("%s\n", pointer->command->description);
                pointer = pointer->next;
            }
        } else if(strcmp(new_command->name, "VERZIA") == 0) {
            printf("First, and the last one :)");
        } else if(strcmp(new_command->name, "O HRE") == 0) {
            printf("It is my daily routine, so, nothing special..");
        } else if(strcmp(new_command->name, "VEZMI") == 0) {
            if(game->backpack->size < game->backpack->capacity) {
                add_item_to_backpack(game->backpack, NULL);
                delete_item_from_room(game->current_room, NULL);
            }
        } else if(strcmp(new_command->name, "POLOZ") == 0) {
            delete_item_from_backpack(game->backpack, NULL);
            add_item_to_room(game->current_room, NULL);
        } else if(strcmp(new_command->name, "INVENTAR") == 0) {
            struct container* pointer = game->backpack->items;
            while(pointer != NULL) {
                printf("%s", pointer->item->name);
                pointer = pointer->next;
            }
        } else if(strcmp(new_command->name, "POUZI") == 0) {

        } else if(strcmp(new_command->name, "PRESKUMAJ") == 0) {

        } else if(strcmp(new_command->name, "NAHRAJ") == 0) {

        } else if(strcmp(new_command->name, "ULOZ") == 0) {

        }

        destroy_command(new_command);
    }
};