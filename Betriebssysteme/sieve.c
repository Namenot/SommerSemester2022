#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv)
{

    const int MAX = 100; // number space we want to search in
    bool prime[MAX+1]; // array of prime

    // special cases {0,1} are never prime
    prime[0] = false;
    prime[1] = false;
    
    // init the prime array
    for(int i = 2; i <= MAX; ++i)
        prime[i] = true; // init all to true (true will later indicated a prime)

    // the main loop that filters (starting at 2 as {0,1} arent considered prime)
    for(int i = 2; i*i <= MAX; ++i)
    {
        // skip any already determined none prime number
        if(prime[i] == false)
            continue;

        // delete / filter all multiples of the newly found prime number starting 
        // with the 1st multiple (we dont want to remove the prime itself)
        for(int k = i+i; k <= MAX; k+=i)
            prime[k] = false; // 0 -> not a prime
    }

    // output that returns all primes from 0 - MAX 
    for(int i = 0; i <= MAX; ++i)
    {
        // skip any none prime number
        if(prime[i] == false)
            continue;
        
        printf("%d\n", i);
    }

    return 0;
}