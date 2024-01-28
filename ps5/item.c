#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

struct item* create_item(char* name, char* description, unsigned int properties) {
    if(name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0) {
        return NULL;
    }

    struct item* new_item = calloc(1, sizeof(struct item));
    new_item->name = calloc(strlen(name) + 1, 1);
    strcpy(new_item->name, name);
    new_item->description = calloc(strlen(description) + 1, 1);
    strcpy(new_item->description, description);
    new_item->properties = properties;

    return new_item;
}

struct item* destroy_item(struct item* item) {
    if(item != NULL) {
        free(item->name);
        free(item->description);
        free(item);
    }

    return NULL;
}