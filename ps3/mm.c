#include <stdio.h>
#include <string.h>

unsigned long long mm(char* input){
    unsigned long long digit = 0;


    int len = strlen(input);

    for(int i = 0; i < len; i++){
        digit += input[i] - '0';
    }

    if(digit >= 10){
        char buffer[20];
        sprintf(buffer, "%llu", digit);
        return mm(buffer);
    }

    return digit;
}

int main(){
    char input[100000];

    scanf("%s", input);
    printf("%llu\n", mm(input));

    return 0;
}
