#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "room.h"

struct room* create_room(char *name, char *description) {
    if(name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0) {
        return NULL;
    }

    struct room* new_room = calloc(1, sizeof(struct room));
    new_room->name = calloc(strlen(name) + 1, 1);
    strcpy(new_room->name, name);
    new_room->description = calloc(strlen(description) + 1, 1);
    strcpy(new_room->description, description);

    return new_room;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west) {
    if(room != NULL) {
        room->north = north;
        room->south = south;
        room->east = east;
        room->west = west;
    }
}

void show_room(const struct room* room) {
    printf("Now you are in - %s\n", room->name);
    printf("You can see:");
    struct container* pointer = room->items;
    while(pointer != NULL) {
        printf(" %s", pointer->item->name);
        pointer = pointer->next;
    }
    printf("Directions that are available:");
}

struct room* destroy_room(struct room* room) {
    if(room != NULL) {
        free(room->name);
        free(room->description);
        room->items = destroy_containers(room->items);
        free(room);
    }

    return NULL;
}

void add_item_to_room(struct room* room, struct item* item) {
    if(room != NULL && item != NULL) {
        if(room->items == NULL) {
            room->items = create_container(room->items, ITEM, item);
        } else {
            struct container* pointer = room->items;
            while(pointer->next != NULL) {
                pointer = pointer->next;
            }
            pointer->next = create_container(room->items, ITEM, item);
        }
    }
}

struct item* get_item_from_room(const struct room* room, const char* name) {
    if(room == NULL || name == NULL) {
        return NULL;
    }

    struct container* pointer = room->items;
    while(pointer != NULL) {
        if(strcmp(pointer->item->name, name) == 0) {
            return pointer->item;
        }
        pointer = pointer->next;
    }

    return NULL;
}

void delete_item_from_room(struct room* room, struct item* item) {
    if(room != NULL && item != NULL) {
        room->items = remove_container(room->items, item);
    }
}
