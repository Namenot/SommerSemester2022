#include<stdio.h>
#include<error.h>
#include<stdlib.h>

// step 1: buchstaben einlesen und zu wörtern/zeilen mschjen
// pointer zu disen wörtern sollen in ein array
struct disgustingWord{
    int size;
    int *letters;
};
typedef struct disgustingWord goodboi;

struct horrendousArray{
    int size;
    goodboi *wordArray;
};
typedef struct horrendousArray betterboi;

goodboi createWordarray(void){
    // remember that we have 0 byte 1 block mem alloc after this. if motivated, fix this
    // word array contains A SINGLE WORD
    int *wordArray = malloc(0); // init the array with 0 memory space bc we realloc later on 
    int newChar;// = fgetc(stdin);
    int charCount = 0; //keep track of how many characters were read in this word so far

    while(1){
        newChar = fgetc(stdin);
        if ((newChar == '\n') || (newChar == EOF)){break;}
        wordArray = realloc(wordArray, sizeof(int) * (charCount +1));
        wordArray[charCount] = newChar;
        charCount ++;
    }
    // always add \n at the end to avoid confusion further down the road
    wordArray = realloc(wordArray,  sizeof(int) * (charCount +1));
    wordArray[charCount] = '\n';
    charCount ++;

    goodboi newWord; // init new gooboi object
    newWord.size = charCount;
    newWord.letters = wordArray;
    return newWord;
}

betterboi *allInOne(betterboi *allWordsOneArray, goodboi word){
    // this might also cause valgrind problems check later

    if(word.size < 2){return allWordsOneArray;}

    allWordsOneArray->wordArray = realloc(allWordsOneArray->wordArray, (allWordsOneArray->size+1)*sizeof(goodboi));

    allWordsOneArray->wordArray[allWordsOneArray->size] = word;
    allWordsOneArray->size ++;
    return allWordsOneArray;
}

int main( int argc, char** argv){

    goodboi nW;
    while( (nW = createWordarray()).size > 1)
        for(int i = 0; i < nW.size; ++i)
            //printf("%c", nW.letters[i]);
            break;
    
    rewind(stdin);

    goodboi nW2;


    betterboi *nA = malloc(sizeof(betterboi));
    nA->size = 0;
    nA->wordArray = malloc(sizeof(goodboi *));

    while( (nW2 = createWordarray()).size > 1)
        allInOne(nA, nW2);

    //rewind(stdin);

    for(int i = 0; i < nA->size ; ++i)
    {
        printf("[%d] ", i);
        for(int j = 0; j < nA->wordArray[i].size; ++j)
        {
            printf("%c", (char)(nA->wordArray[i].letters[j]));
            //printf("WELT\n");
        }
    }
    return 0;
}