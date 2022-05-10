#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct subarray
{
    int size;
    int *word;
};

typedef struct subarray subarray;

void printArray(int *)
{

}

int main(void)
{

    int ***array = malloc(0);
    int arraysize = 0;

    subarray sa;
    sa.word = malloc(0);
    sa.size = 0;

    // load the entire content into an array of arrays
    int c;
    do
    {  
        c = fgetc(stdin);
        if(c == '\n' || c == EOF)
        {
            if(sa.size > 0)
            {
                arraysize++;
                array = realloc(array, sizeof(subarray *)* arraysize);
                array[arraysize -1] = &sa.word;
            }

            free(sa.word);
            sa.size = 0;
            continue;
        }
        
        sa.size ++;
        sa.word = realloc(sa.word, sizeof(int) * sa.size);
        sa.word[sa.size-1] = c;
    }while(c != EOF);

    return 0;
}