#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "container.h"

struct container* create_container(struct container* first, enum container_type type, void* entry) {
    if(entry != NULL) {
        if(first == NULL) {
            struct container* new_container = calloc(1, sizeof(struct container));
            new_container->type = type;
            switch(type) {
                case ROOM:
                    new_container->room = entry;
                case ITEM:
                    new_container->item = entry;
                case COMMAND:
                    new_container->command = entry;
                case TEXT:
                    new_container->text = entry;
            }

            return new_container;
        } else if(first->type == type) {
            struct container* pointer = first;
            struct container* new_container = calloc(1, sizeof(struct container));
            new_container->type = type;
            switch(type) {
                case ROOM:
                    new_container->room = entry;
                case ITEM:
                    new_container->item = entry;
                case COMMAND:
                    new_container->command = entry;
                case TEXT:
                    new_container->text = entry;
            }

            while(pointer->next != NULL) {
                pointer = pointer->next;
            }
            pointer->next = new_container;
            return new_container;
        }
    }

    return NULL;
}

struct container* destroy_containers(struct container* first) {
    if(first != NULL) {
        struct container* pointer = first;
        while(pointer != NULL) {
            struct container* copy = pointer->next;
            switch(first->type) {
                case ROOM:
                    pointer->room = destroy_room(pointer->room);
                case ITEM:
                    pointer->item = destroy_item(pointer->item);
                case COMMAND:
                    pointer->command = destroy_command(pointer->command);
                case TEXT:
                    free(pointer->text);
            }

            free(pointer);
            pointer = copy;
        }
    }

    return NULL;
}

void* get_from_container_by_name(struct container *first, const char *name) {
    if(first != NULL && name != NULL) {
        struct container* pointer = first;
        while(pointer != NULL) {
            switch(first->type) {
                case ROOM:
                    if(strcmp(pointer->room->name, name) == 0) {
                        return pointer->room;
                    }
                case ITEM:
                    if(strcmp(pointer->item->name, name) == 0) {
                        return pointer->item;
                    }
                case COMMAND:
                    if(strcmp(pointer->command->name, name) == 0) {
                        return pointer->command;
                    }
                case TEXT:
                    if(strcmp(pointer->text, name) == 0) {
                        return pointer->text;
                    }
            }

            pointer = pointer->next;
        }
    }

    return NULL;
}

struct container* remove_container(struct container *first, void *entry) {
    if(first != NULL) {
        struct container* pointer = first;

        if(pointer->room == entry
        || pointer->item == entry
        || pointer->command == entry
        || pointer->text == entry) {
            pointer = NULL;
            return NULL;
        }

        while(pointer->next != NULL) {
            switch(first->type) {
                case ROOM:
                    pointer->next = pointer->next->room == entry ? pointer->next->next : pointer->next;
                    return first;
                case ITEM:
                    pointer->next = pointer->next->item == entry ? pointer->next->next : pointer->next;
                    return first;
                case COMMAND:
                    pointer->next = pointer->next->command == entry ? pointer->next->next : pointer->next;
                    return first;
                case TEXT:
                    pointer->next = pointer->next->text == entry ? pointer->next->next : pointer->next;
                    return first;
                default:
                    pointer = pointer->next;
            }
        }
    }

    return first;
}
