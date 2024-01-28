#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

struct parser* create_parser() {
    struct parser* new_parser = calloc(1, sizeof(struct parser));
    struct command* command_save = create_command("ULOZ", "Príkaz uloží stav rozohratej hry na disk. Voliteľným parametrom je cesta k súboru.", "SAVE", 1);
    struct command* command_load = create_command("NAHRAJ", "Príkaz zabezpečí nahratie uloženej pozície hry z disku. Voliteľným parametrom je cesta k súboru.", "LOAD", 1);
    struct command* command_research = create_command("PRESKUMAJ", "Vypíše opis predmetu, ktorý sa musí nachádzať v miestnosti alebo batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný alebo sa nenájde v batohu alebo v miestnosti, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš preskúmať.).", NULL, 0);
    struct command* command_use = create_command("POUZI", "Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš použiť.).", NULL, 0);
    struct command* command_inventory = create_command("INVENTAR", "Zobrazí obsah hráčovho batohu.", "I", 1);
    struct command* command_put = create_command("POLOZ", "Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš položiť.)", NULL, 0);
    struct command* command_take = create_command("VEZMI", "Vloží predmet z miestnosti do batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš vziať.).", NULL, 0);
    struct command* command_about = create_command("O HRE", "Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý začiatok sa javí známy text: Kde bolo tam bolo…", "ABOUT", 1);
    struct command* command_restart = create_command("RESTART", "Znovu spustí hru od začiatku. Zmení stav hry na požadovaný.", NULL, 0);
    struct command* command_version = create_command("VERZIA", "Príkaz zobrazí číslo verzie hry, ľubovoľný sprievodný text a meno a priezvisko autora s kontaktom (e-mailová adresa, webová stránka).", NULL, 0);
    struct command* command_help = create_command("PRIKAZY", "Príkaz vypíše na obrazovku zoznam všetkých príkazov, ktoré hra poskytuje.", "HELP, POMOC", 2);
    struct command* command_info = create_command("ROZHLIADNI SA", "Príkaz vypíše aktuálne informácie o miestnosti, v ktorej sa hráč práve nachádza.", NULL, 0);
    struct command* command_west = create_command("ZAPAD", "Presun do miestnosti nachádzajúcej sa na západ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "Z", 1);
    struct command* command_east = create_command("VYCHOD", "Presun do miestnosti nachádzajúcej sa na východ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "V", 1);
    struct command* command_south = create_command("JUH", "Presun do miestnosti nachádzajúcej sa na juh od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "J", 1);
    struct command* command_north = create_command("SEVER", "Presun do miestnosti nachádzajúcej sa na sever od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "S", 1);
    struct command* command_end = create_command("KONIEC", "Príkaz ukončí rozohratú hru. Nastaví príslušný stav hry.", "QUIT, EXIT", 2);

    // add commands
    new_parser->commands = create_container(NULL, COMMAND, command_end);
    create_container(new_parser->commands, COMMAND, command_north);
    create_container(new_parser->commands, COMMAND, command_south);
    create_container(new_parser->commands, COMMAND, command_east);
    create_container(new_parser->commands, COMMAND, command_west);
    create_container(new_parser->commands, COMMAND, command_info);
    create_container(new_parser->commands, COMMAND, command_help);
    create_container(new_parser->commands, COMMAND, command_version);
    create_container(new_parser->commands, COMMAND, command_restart);
    create_container(new_parser->commands, COMMAND, command_about);
    create_container(new_parser->commands, COMMAND, command_take);
    create_container(new_parser->commands, COMMAND, command_put);
    create_container(new_parser->commands, COMMAND, command_inventory);
    create_container(new_parser->commands, COMMAND, command_use);
    create_container(new_parser->commands, COMMAND, command_research);
    create_container(new_parser->commands, COMMAND, command_load);
    create_container(new_parser->commands, COMMAND, command_save);

    return new_parser;
}

struct parser* destroy_parser(struct parser* parser) {
    if(parser != NULL) {
        parser->history = destroy_containers(parser->history);
        parser->commands = destroy_containers(parser->commands);
        free(parser);
    }

    return NULL;
}

struct command* parse_input(struct parser* parser, char* input) {
    if(parser != NULL && input != NULL && strlen(input) > 0) {
        char* string = calloc(strlen(input) + 1, 1);
        strcpy(string, input);
        for(int i = 0; i < strlen(string); i++) {
            string[i] = islower(string[i]) ? (char) toupper(string[i]) : string[i];
         }

        struct container* pointer = parser->commands;
        while(pointer != NULL) {
            if(strstr(string, pointer->command->name) != NULL) {
                free(string);
                return pointer->command;
            }
            pointer = pointer->next;
        }
        free(string);
    }

    return NULL;
}