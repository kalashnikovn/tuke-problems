#include <stdio.h>
#include <stdlib.h>
#include "backpack.h"

struct backpack* create_backpack(const int capacity) {
    if(capacity <= 0) {
        return NULL;
    }

    struct backpack* backpack = calloc(1, sizeof(struct backpack));
    backpack->capacity = capacity;
    backpack->size = 0;
    backpack->items = NULL;

    return backpack;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item) {
    if(backpack != NULL && backpack->size > 0) {
        backpack->items = remove_container(backpack->items, item);
        backpack->size -= 1;
    }
}



bool add_item_to_backpack(struct backpack* backpack, struct item* item) {
    if(backpack == NULL
    || item == NULL
    || backpack->size >= backpack->capacity
    || !(item->properties & MOVABLE)) {
        return 0;
    }


    if(backpack->items == NULL) {
        backpack->items = create_container(backpack->items, ITEM, item);
    } else {
        struct container* pointer = backpack->items;
        while(pointer->next != NULL) {
            pointer = pointer->next;
        }

        pointer->next = create_container(backpack->items, ITEM, item);
    }

    backpack->size += 1;

    return 1;
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name) {
    if(backpack == NULL || name == NULL) {
        return NULL;
    }

    void* result = get_from_container_by_name(backpack->items, name);

    return result;
}

struct backpack* destroy_backpack(struct backpack* backpack) {
    if(backpack != NULL) {
        free(backpack);
        backpack = NULL;
    }

    return NULL;
}
