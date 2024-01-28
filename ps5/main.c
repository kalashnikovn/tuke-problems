#include <stdio.h>
#include "backpack.h"
#include "command.h"
#include "container.h"
#include "game.h"
#include "item.h"
#include "parser.h"
#include "room.h"
#include "world.h"

int main() {

    struct container* world = create_world();
    add_room_to_world(world, NULL);
    get_room(world, NULL);
    destroy_world(world);

    struct game* game = create_game();
    play_game(game);
    execute_command(game, NULL);
    destroy_game(game);

    struct backpack* backpack = create_backpack(5);
    add_item_to_backpack(backpack, NULL);
    delete_item_from_backpack(backpack, NULL);
    get_item_from_backpack(backpack, NULL);
    destroy_backpack(backpack);

    struct command* command = create_command(NULL, NULL, NULL, 1);
    destroy_command(command);

    struct container* container = create_container(NULL, 1, NULL);
    get_from_container_by_name(container, NULL);
    remove_container(container, NULL);
    destroy_containers(container);

    struct item* item = create_item("new item", "this is a test item", 0);
    destroy_item(item);

    struct parser* parser = create_parser();
    parse_input(parser, NULL);
    destroy_parser(parser);

    struct room* test_room = create_room("start", "startpoint");
    set_exits_from_room(test_room, NULL, NULL, NULL, NULL);
    show_room(test_room);
    delete_item_from_room(test_room, NULL);

    add_item_to_room(test_room, item);
    printf("\n%s\n", get_item_from_room(test_room, "new item")->name);
    destroy_room(test_room);

    return 0;
}