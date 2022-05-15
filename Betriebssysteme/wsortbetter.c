#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct streamline
{
    int size;
    int *arr;
};

struct arrayOfArrays
{
    int size;
    struct streamline **lines;
};

typedef  struct streamline streamline;
typedef struct arrayOfArrays ara_ara;

void printIntString(streamline *word)
{
    for(int i = 0; i < word->size; ++i) 
        if((char)word->arr[i] != '\n')
            printf("%c" , word->arr[i]);
}

int comparisons(const void* elem1, const void *elem2)
{   
    streamline *recaste1= *((streamline **)elem1);
    streamline *recaste2= *((streamline **)elem2);

    int i = 0;

    while(recaste1->arr[i] == recaste2->arr[i])
    {      
        // given that the original condition was that both chars are equal 
        // if one is '\n' so must the other
        if(recaste1->arr[i] == '\n')
            break;
        i ++;    
    }

    // if either last element is == '\n' set it to the smallest possible number 0
    unsigned int nL1 = (recaste1->arr[i] != '\n') * recaste1->arr[i];
    unsigned int nL2 = (recaste2->arr[i] != '\n') * recaste2->arr[i]; 

    /* all possiblities
        - nL1 == nL2 => (0) - (0) = 0 = >both the same
        - nL1 > nL2 => (1) - (0) = 1 => nL2 comes before nL1
        - nL1 < nL2 => (0) - (1) = -1 => nL1 comes before nL2
    */
    return (nL1 > nL2) - (nL2 > nL1);
}

streamline *dynamicAllocation(ara_ara *element, streamline *insert)
{   

    // if the new string is empty we just end this
    if(insert->arr == NULL)
        return NULL;

    //max word length is 100 characters + '\n' = 101
    if(insert->size > 101)
        return NULL;

    // if a line only contains '\n' then its considered empty and usortable
    if(insert->size < 2)
        return NULL;

    // allocate the memory 
    streamline *tempWord = (streamline *)malloc(sizeof(streamline));
    if(tempWord == NULL)
    {
        perror("couldnt assigne Memory to tempWord");
        exit(EXIT_FAILURE);
    }

    tempWord->arr = (int *)malloc(sizeof(int)* (insert->size));
    if(tempWord->arr == NULL)
    {
        perror("couldnt assigne Memory to tempWord->array");
        exit(EXIT_FAILURE);
    }

    tempWord->size = insert->size;
    
    element->lines = (streamline **)realloc(element->lines, sizeof(streamline **) * (element->size + 1));
    if(element->lines == NULL)
    {
        perror("couldnt realloc element->lines");
        exit(EXIT_FAILURE);
    }

    for(int k = 0; k < insert->size; ++k)
        tempWord->arr[k] = insert->arr[k];

    element->lines[element->size] = tempWord;
    element->size ++;

    return element->lines[element->size - 1];
}


int main(int argc, char **argv)
{

    // check if an input stream exists
    if(!feof(stdin))
    {
        perror("stdin buffer is empty");
        exit(EXIT_FAILURE);
    }

    ara_ara filecontent;
    filecontent.size = 0;
    filecontent.lines = malloc(sizeof(streamline *));
    if(filecontent.lines == NULL)
    {
        perror("malloc of fliecontent.lines was unsuccessfull");
        exit(EXIT_FAILURE);
    }

    streamline nWord;
    nWord.size = 0;
    nWord.arr = NULL;

    char test[102];

    while(fgets(test, 102, stdin) != NULL)
    {
        nWord.arr = (int *)test;
        dynamicAllocation(&filecontent, &nWord);
        free(nWord.arr);
    }

    qsort(filecontent.lines, filecontent.size, sizeof(int *), comparisons);

    // print new order
    for(int i = 0; i < filecontent.size ; ++i)
    {
        //printf("[%d] ", i);
        printIntString(filecontent.lines[i]);
        printf("\n");
        free(filecontent.lines[i]->arr);
        free(filecontent.lines[i]); 
    }

    free(filecontent.lines);

    return 0;
}