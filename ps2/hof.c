#include <stdio.h>
#include <string.h>
#include "hof.h"


#define MAX_PLAYERS 10


int load(struct player list[]) {
    int count = 0;

    FILE *file = fopen("HOF_FILE", "r");
    if (file == NULL) {
        return -1;
    }


    while (count < 10 && fscanf(file, "%s %d\n", list[count].name, &(list[count].score)) == 2 && list[count].score != 0) {
        count++;
    }
    fclose(file);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (list[j].score > list[i].score) {
                struct player temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    return count;
}

bool save(const struct player list[], const int size) {
    if (list == NULL || size <= 0) {
        return false;
    }

    FILE *file = fopen("HOF_FILE", "w");
    if (file == NULL) {
        return false;
    }

    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
            fprintf(file, "%s%s%d", list[i].name, DELIMITER, list[i].score);
        } else {
            fprintf(file, "%s%s%d\n", list[i].name, DELIMITER, list[i].score);
        }

    }

    fclose(file);
    return true;


}

bool add_player(struct player list[], int* size, const struct player player) {
    if (list == NULL || size == NULL || (*size) < 0 || (*size) > 10)
    {
        return false;
    }

    for (int i = 0; i < *size; i++)
    {
        if (player.score >= list[i].score) {
            for (int j = MAX_PLAYERS - 1; j > i; j--) {
                list[j] = list[j - 1];
            }

            list[i] = player;
            if ((*size) < 10) {
                (*size)++;
            }
            return true;
        }
    }

    if ((*size) < 10) {
        list[*size] = player;
        (*size)++;
        return true;
    }

    return false;
}