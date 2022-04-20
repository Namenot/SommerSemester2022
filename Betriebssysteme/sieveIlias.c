#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv){
    const int MAX = 100;
    bool prime[MAX+1];    // array with [0] and [1] == 0, [2 to n] == 1
    prime[0] = 0;
    prime[1] = 0;
    for(int i = 2; i <= MAX; i++){
        prime[i] = 1;
    }

    for(int counter = 2; counter <= MAX;){
        for(int i = counter + 1; i <= MAX; i++){
            if(i % counter == 0){
                prime[i] = 0;
            }
        }
        counter++;
        while(prime[counter] == 0){
            counter++;
            if(counter >= MAX){
                break;
            }
        }
    }

    for(int j = 0; j <= MAX; j++){
        if(prime[j] != 0){
            printf("%d \n", j);
        }

    }

    return 0;
}