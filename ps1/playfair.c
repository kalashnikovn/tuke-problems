#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 5

char* to_upper(const char *text);
char **create_pf_table(char *salt);
char* modify_text(const char *text);
void replace_letter(char* word, char to_replace, char replaced);
void search_coords(char **table, char letter, int *row, int *col);
char* encrypt(char* word, char **table);
char* decrypt(const char* word, char **table);
void free_table(char **table);
char* to_output(char* str);


char* playfair_encrypt(const char* key, const char* text){
    if (key == NULL || text == NULL) return NULL;

    for(int i=0; i < strlen(key); i++){
        if(key[i] < 'A' ||(key[i]>'Z' && key[i] < 'a') || key[i] >'z'){
            return 0;
        }
    }
    if (strlen(key) == 0 || strlen(text) == 0) return "";


    char* upped = to_upper(key);
    char **table = create_pf_table(upped);
    char* modified = modify_text(text);


    char *encrypted = encrypt(modified, table);

    char* final = to_output(encrypted);

    free(upped);
    free(encrypted);
    free(modified);
    free_table(table);

    return final;
}

char* playfair_decrypt(const char* key, const char* text){
    if (key == NULL || text == NULL) return NULL;

    for(int i=0; i < strlen(key); i++){
        if(key[i] < 'A' ||(key[i]>'Z' && key[i] < 'a') || key[i] >'z'){
            return 0;
        }
    }

    if (strlen(key) == 0 || strlen(text) == 0) return "";

    char* upped = to_upper(key);
    char **table = create_pf_table(upped);
    char* modified = modify_text(text);

    char *decrypted = decrypt(modified, table);

    free_table(table);
    free(modified);

    return decrypted;
}

char* encrypt(char* word, char **table) {
    int length = strlen(word);
    int index;

    char first, second;
    char* encrypted = malloc(sizeof(char) * (length + 1));

    int j = 0;
    for(index = 0; index < length; index += 2) {
        first = word[index];
        if (index + 1 < length) {
            second = word[index + 1];
        } else {
            second = 'X';
        }

        int first_row, sec_row;
        int first_col, sec_col;

        search_coords(table, first, &first_row, &first_col);
        search_coords(table, second, &sec_row, &sec_col);

        char first_symb;
        char sec_symb;

        if (first_row != sec_row && first_col != sec_col)
        {
            first_symb = table[first_row][sec_col];
            sec_symb = table[sec_row][first_col];
        }
        else
        {
            int row = (first_row == sec_row) ? first_row : (first_row + 1) % 5;
            int col = (first_col == sec_col) ? first_col : (first_col + 1) % 5;
            first_symb = table[row][col];

            row = (first_row == sec_row) ? sec_row : (sec_row + 1) % 5;
            col = (first_col == sec_col) ? sec_col : (sec_col + 1) % 5;
            sec_symb = table[row][col];
        }

        encrypted[j++] = first_symb;
        encrypted[j++] = sec_symb;
    }

    encrypted[j] = '\0';
    return encrypted;
}



char* decrypt(const char* word, char **table) {
    int length = strlen(word);
    int index;
    char first, second;
    char* decrypted = malloc(sizeof(char) * (length + 1));

    int j = 0;
    for(index = 0; index < length; index += 2) {
        first = word[index];
        second = word[index + 1];

        int first_row, sec_row;
        int first_col, sec_col;

        search_coords(table, first, &first_row, &first_col);
        search_coords(table, second, &sec_row, &sec_col);


        char first_symb = (first_row == sec_row)
                          ? table[first_row][(first_col + 4) % 5]
                          : (first_col == sec_col)
                            ? table[(first_row + 4) % 5][first_col]
                            : table[first_row][sec_col];

        char sec_symb = (first_row == sec_row)
                        ? table[sec_row][(sec_col + 4) % 5]
                        : (first_col == sec_col)
                          ? table[(sec_row + 4) % 5][sec_col]
                          : table[sec_row][first_col];

        decrypted[j++] = first_symb;
        decrypted[j++] = sec_symb;
    }

    decrypted[j] = '\0';
    return decrypted;
}


char* to_output(char* str) {
    int len = strlen(str);


    char* result = malloc(sizeof(char) * (len * 3 / 2 + 1));

    int i, j;
    for (i = 0, j = 0; i < len; i += 2, j += 3) {
        result[j] = str[i];
        result[j + 1] = str[i + 1];
        result[j + 2] = ' ';
    }

    result[j - 1] = '\0';

    return result;
}


void free_table(char **table) {
    for (int i = 0; i < SIZE; i++) {
        free(table[i]);
    }
    free(table);
}


void search_coords(char **table, char letter, int *row, int *col) {
    int i;
    int j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (table[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

char* modify_text(const char *text) {
    char* modified_text = (char*) malloc(sizeof(char) * (strlen(text) * 2 + 1)); // память под новый текст

    int index = 0;
    int count = 0; // для случаев с двумя Х

    char past_letter = '\0';

    while (*text != '\0') {
        char curr_letter = toupper(*text);

        if (curr_letter == ' ') {
            text++;
            continue; // пробельчики пропускаем
        }
        count++;

        if (curr_letter == past_letter && curr_letter != 'X' && count % 2 == 0) {
            modified_text[index++] = 'X'; // если два икса попалось
        }
        modified_text[index++] = curr_letter;
        past_letter = curr_letter;
        text++;
    }

    if (strlen(modified_text) % 2 != 0) {
        modified_text[index++] = 'X'; // в конец икс добавляем
    }

    modified_text[index] = '\0';
    replace_letter(modified_text, 'W', 'V');

    return modified_text;
}


void replace_letter(char* word, char to_replace, char replaced) {
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        if (word[i] == to_replace) {
            word[i] = replaced;
        }
    }
}


char* to_upper(const char *text) {
    int length = strlen(text);
    char *upped_str = (char*)malloc(length + 1);

    strcpy(upped_str, text);

    int index = 0;
    while (upped_str[index] != '\0') {
        upped_str[index] = toupper(upped_str[index]);
        index++;
    }

    return upped_str;
}


char **create_pf_table(char *salt) {
    char **table = (char**) malloc(SIZE * sizeof(char*)); // память под матрицу

    for (int i = 0; i < 5; i++) {
        table[i] = (char*) malloc(SIZE * sizeof(char));
    }

    int j = 0;
    int alpha[26] = {0}; // чисто массивчик под использованные чары

    for (int i = 0; i < strlen(salt); i++) {
        if (salt[i] == 'W') {
            salt[i] = 'V';
        }

        if (alpha[salt[i] - 'A'] == 0) {
            table[j / 5][j % 5] = salt[i];
            alpha[salt[i] - 'A'] = 1;
            j++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (alpha[i] == 0) {
            if (i == ('W' - 'A')) {
                continue;
            }
            table[j / 5][j % 5] = 'A' + i;
            j++;
        }
    }

    return table;
}



