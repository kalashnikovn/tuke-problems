#include <stdio.h>

int main(){
    int holes, parts;

    scanf("%d %d", &holes, &parts);
    int first[10000], second[10000], third[10000], fourth[10000];

    for(int i = 0; i < holes; i++)
        scanf("%d %d %d %d", &fourth[i], &first[i], &second[i], &third[i]);


    if( parts == 1 || holes == 0 || parts == 0){

        for(int i = 0; i < parts; i++){

            if(i != parts - 1)
                printf("%.06f\n", 100.000000/parts);
            else
                printf("%.06f", 100.000000/parts);
        }
    }
    return 0;
}
