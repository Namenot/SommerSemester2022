#include <stdio.h>
#include <stdbool.h>

int main(int argc, char** argv) {

    const int MAX = 100;
    bool prime[MAX + 1]; // include the largest number in MAX
    // set 0 and 1 to false; def of prime
    prime[0] = 0;
    prime[1] = 0;
    // set all elements in prime to true
    for (int i = 2; i <= MAX; i++) {
        prime[i] = 1;
    }

    for (int counter = 2; counter <= MAX;) {  // set counter to first element
        // check rest of array for duplicates of counter
        for (int i = counter + 1; i <= MAX; i++) {
            if (i % counter == 0) {
                prime[i] = 0;
            }
        }
        // increase counter until next element != 0 is found
        counter++;
        while (prime[counter] == 0) {
            counter++;
            if (counter >= MAX) {
                break;
            }
        }
    }

    // print every prime number up to MAX
    for (int j = 0; j <= MAX; j++) {
        if (prime[j] != 0) {
            printf("%d \n", j);
        }

    }

    return 0;
}