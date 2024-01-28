#include <stdio.h>

double binary(double left, double right){
    return (left + right) / 2;
}

double work(int part, int time, int distance[], int speed[]) {
    double left = 0, right = 1000000;
    double k = binary(left, right);
    double resultedTime = 0;

    for(int i = 0; i < part; i++) {
        if((i != 0 && left > speed[i]) || i == 0)
            left = speed[i];
    }
    left = -left;

    while(resultedTime < time - 0.0000001 || resultedTime > time + 0.0000001){
        for(int i = 0; i < part; i++)
            resultedTime += distance[i] / (speed[i] + k);

        if(resultedTime < time)
            right = k;
        else if(resultedTime > time)
            left = k;
        else
            break;

        resultedTime = 0;
        k = binary(left, right);
        if(k < left + 0.0000001 || k > right + 0.0000001)
            break;
    }

    return k;
}

int main(){
    int part, time;
    scanf("%d %d", &part, &time);

    int distance[1000];
    int speed[1000];

    for(int i = 0; i < part; i++) {
        scanf("%d %d", &distance[i], &speed[i]);
    }

    double k = work(part, time, distance, speed);
    printf("%.9f\n", k);

    return 0;
}
