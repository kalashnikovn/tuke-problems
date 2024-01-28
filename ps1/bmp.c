#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"


unsigned char* bmp_encrypt(const char* key, const char* text){
    char* reversed = reverse(text);
    char* vig_encrypted = vigenere_encrypt(key,reversed);
    unsigned char* bit_encrypted = bit_encrypt(vig_encrypted);


    free(reversed);
    free(vig_encrypted);
    return bit_encrypted;
}

unsigned char* bit_encrypt(const char* text) {
    if (text == NULL) {
        return NULL;
    }
    if (strlen(text) == 0) return NULL;

    int length = strlen(text);

    unsigned char* encrypted = malloc(length + 1);
    encrypted[length] = '\0';

    unsigned char bits[8];

    for (int count = 0; count < length; count++) {

        int symbol = text[count]; // кодируем символ в нули и единички
        int index_of_byte = 7;

        while (symbol != 1) {
            if (symbol % 2 == 0) {
                bits[index_of_byte] = 0;
            } else {
                bits[index_of_byte] = 1;
            }

            index_of_byte--;
            symbol /= 2;
        }

        bits[index_of_byte] = 1;
        index_of_byte--;
        for (int j = index_of_byte; j > -1; j--) {
            bits[j] = 0;
        }

        for (int index = 0; index < 3; index += 2) {
            bits[index] += bits[index + 1];
            bits[index + 1] = bits[index] - bits[index + 1];
            bits[index] = bits[index] - bits[index + 1];

            bits[index + 4] = bits[index] ^ bits[index + 4];
            bits[index + 5] = bits[index + 1] ^ bits[index + 5];
        }

        int final = 0;

        for (int i = 0; i < 8; i++) {
            final |= (bits[i] << (7 - i));
        }
        encrypted[count] = final;
    }

    return encrypted;
}


char* reverse(const char* text) {
    if (text == NULL) return NULL;
    if (*text == '\0') return NULL;

    int len = strlen(text);
    char* rvs_string = (char*) malloc((len + 1) * sizeof(char));
    if (rvs_string == NULL) return NULL;

    for (int i = 0; i < len; i++) {
        rvs_string[i] = toupper(text[i]);
    }
    rvs_string[len] = '\0';

    char *a = rvs_string, *b = rvs_string + len - 1;

    while (b > a) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;

        ++a;
        --b;
    }

    return rvs_string;
}

char* vigenere_encrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL) return NULL;

    size_t k_length = strlen(key);
    size_t t_length = strlen(text);


    for (size_t i = 0; i < k_length; i++) {
        if (!isalpha(key[i])) {
            return NULL;
        }
    }

    if (k_length == 0 || t_length == 0) {
        return NULL;
    }

    char* encrypted_text = (char*)malloc((t_length + 1) * sizeof(char));
    if (encrypted_text == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < t_length; i++) {
        if (isalpha(text[i]))
        {
            char dunno = toupper(key[j % k_length]) - 'A';

            char symb = toupper(text[i]);

            symb = 'A' + ((symb - 'A' + dunno) % 26);

            encrypted_text[i] = symb;
            j++;
        }
        else
        {
            encrypted_text[i] = text[i];
        }
    }

    encrypted_text[t_length] = '\0';

    return encrypted_text;
}


char* vigenere_decrypt(const char* key, const char* text) {
    if (key == NULL || text == NULL) {
        return NULL;
    }

    int key_len = strlen(key);
    for(int i = 0; i < key_len; i++) {
        if (!isalpha(key[i])) {
            return NULL;
        }
    }

    int text_len = strlen(text);
    if (key_len == 0 || text_len == 0) {
        char* empty = (char*)malloc(sizeof(char));
        *empty = '\0';
        return empty;
    }

    char* word1 = (char*)malloc((text_len + 1) * sizeof(char));
    if (word1 == NULL) {
        return NULL;
    }
    strcpy(word1, text);

    char* word2 = (char*)malloc((key_len + 1) * sizeof(char));
    if (word2 == NULL) {
        free(word1);
        return NULL;
    }
    strcpy(word2, key);

    for (int i = 0; i < text_len; i++) {
        if (islower(word1[i])) {
            word1[i] = toupper(word1[i]);
        }
    }

    for (int i = 0; i < key_len; i++) {
        if (islower(word2[i])) {
            word2[i] = toupper(word2[i]);
        }
    }

    for (int i = 0, d = 0; i < text_len; i++) {
        if (isupper(word1[i])) {
            word1[i] = 'A' + (word1[i] - word2[d % key_len] + 26) % 26;
            d++;
        }
    }

    free(word2);

    for (int i = 0; i < text_len; i++) {
        if (isupper(word1[i])) {
            word1[i] = tolower(word1[i]);
        }
    }

    return word1;
}