#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

struct command* destroy_command(struct command* command) {
    if(command != NULL) {
        free(command->name);
        free(command->description);
        free(command);
    }

    return NULL;
}

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch) {
    if(name == NULL || description ==  NULL || strlen(name) == 0 || strlen(description) == 0) {
        return NULL;
    }

    struct command* new_command = calloc(1, sizeof(struct command));
    new_command->name = calloc(strlen(name) + 1, 1);
    strcpy(new_command->name, name);
    new_command->description = calloc(strlen(description) + 1, 1);
    strcpy(new_command->description, description);
    new_command->nmatch = nmatch;

    return new_command;
}