#include <stdio.h>
#include "bmp.h"
#include "playfair.h"
#include <stdlib.h>



int main(){
    char *encrypted, *decrypted;

    encrypted = playfair_encrypt("world", "Hello");
    printf("%s\n", encrypted);
    decrypted = playfair_decrypt("world", encrypted);
    printf("%s\n", decrypted);

    char* reversed = reverse("Hello world!");
    printf("%s\n", reversed);

    encrypted = vigenere_encrypt("CoMPuTeR", "Hello world!");
    printf("%s\n", encrypted);
    decrypted = vigenere_decrypt("CoMPuTeR", encrypted);
    printf("%s\n", decrypted);

    unsigned char* bit = bit_encrypt("Hello world!");
    for(int i=0; i < 12;i++) {
        printf("%x ", bit[i]);
        //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    }
    printf("\n");



    unsigned char* a;
    a = bmp_encrypt("SeCReT", "Hello world!");
    for(int i=0; i < 12;i++) {
        printf("%x ", a[i]);
    }

    printf("\n");


    free(bit);
    free(encrypted);
    free(decrypted);

    return 0;
}
