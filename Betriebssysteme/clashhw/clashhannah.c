#include <stdio.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// upon starting program:
// display directory

// read input via stdin gets() or something 
// process the input and split it into commands and arguments vith strtok() : seperators: space and tab
// start child processs for each command with fork 
// execute process with corresponding arguments via exec

// if process id foregroud process: wait for processes to teminate (waitpid(2))) and give exit status before taking in new input
// if process is background process: dont wait, take new promts instantly

// before displaying new prompt: collect zombie processes and give exit status

// compile this file with: gcc -std=c11 -pedantic -D_XOPEN_SOURCE=700 -Wall -Werror -o clash clash.c 


static void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

static void getDir(){
    char cwd[4096];     // max filesystem pathlength is  usually 4096
    if (getcwd(cwd, sizeof(cwd)) != 0){
        printf("current working dir %s\n", cwd);
    }
    else{
        die("getcwd() failed");
    }
}

static char **processInput(){
    char **tokenArray = malloc(0);                      // an array containing pointers to all of the tokens
    int tokenCounter = 0;

/* * * * * * * * * * * * * * * * * * * * *
 * I CHANGED THE FOLLOWING LINE:          *  
 * originally: char newInput[1337];      *
 * * * * * * * * * * * * * * * * * * * * */
    static char newInput[1337];                                 // create Array with max length of input (taken from aufgabenstellung)

/* * * * * * * * * * * * * * * * * * * * *
 * Dieser fix ist ziemlich lazy aber     *
 * funktioniert.                         *
 * Das Problem war, dass wir zwar den    *
 * POINTER zum Array zurueck geben       *
 * aber jeder POINTER in dem Array       * 
 * selbst nicht bestehen bleibt, da es   *
 * sich um locale Variablen handelt,     *
 * die nach Beendigung der Funktion      *
 * verfallen.                            *
 * Dadurch dass newInput jetzt fest      *
 * (static) gesetzt ist bleiben die      *
 * POINTER auchnach Funktions-Ende       *
 * bestehen.                             *
 * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * *
 * In einer alternativen Loesung koennte *
 * man die Var newInput ausserhalb       *
 * (z.B. in der main) definieren und als *
 * Parameter an die Funktion uebergeben. *
 * So wuerde man das Dilemma umgehen,    *
 * aber damit wuerde ich auch mehr von   *
 * deinem Code aendern, was dir nicht    *
 * wirklich dabei hilft die Loesung zu   *
 * verstehen.                            *
 * * * * * * * * * * * * * * * * * * * * */
    
    fgets(newInput, 1337 ,stdin);                           // get input fgets(array we want to write to, how many chars, source)
    const char delimiters[] = {' ','\t', 0};               // setzen der zeichen an denen getrennt wird
    char *token = strtok(newInput, delimiters);         // beginn des auftrennens des strings an den delimitern 
    do{
        printf("token %s \n", token);
        tokenArray = realloc(tokenArray, (tokenCounter + 1) * sizeof(char*));       // Token array um die länge des neuen tokens erhöhen (da es ein char pointer array is gilt sizeof array = #pointer * pointergröße
        tokenArray[tokenCounter] = token;                                           // Token anfügen ans Array

        tokenCounter += 1;
        token = strtok(NULL, delimiters);                                           // einen token weitergehen, da wir strtok mit null aufgerufen haben
    }while (token != NULL);
    printf("token[0] %s \n", tokenArray[0]);
    printf("token[1] %s \n", tokenArray[1]);
    return tokenArray;
}


static int executeCmd(char **tokenArray){         // tokenarray[0] is command, rest of tokenarray are arguments
    int status;
    pid_t child = fork();
    printf("we should be executing rn \n");

    // idea: when we fork, we have two frolocking processes who both go thorugh the if thingies below independently, 
    // thats why the child execs and terminates invisibly
    // and the status is always set, because at some point in time, the parent will go through the if clauses and enter the else part.

    if (child == -1){
        // awesome error handling here
        printf("something is foul in the state of denmark \n");
    }
    else if(child == 0){             // current process is child process
        printf("token array %s \n", tokenArray[0]);
        execvp(tokenArray[0], tokenArray);    // execvp(command aka token 0, allesauchcommand aka alle tokens)
        exit(EXIT_SUCCESS);                   // void exit(int status) EXIT_SUCCESS = 0, EXIT_FAILURE != 0, usually 1         
    }                                         // exit frees all resources the process allocated, process becomes zombie

    else{        // we are parent process
       waitpid(child, &status, WUNTRACED | WCONTINUED);                   //waitpid(processID (pid_t), adress of status with which child has exited (integer), misc options from stack overflow)
    }                                                                      // waitpid will write in the status location the according status with the process has terminated
    return status;
}


int main(int argc, char **argv)
{
    while(1){
        getDir();
        char **input = processInput();
        printf("token[0] %s \n", input[0]);
        printf("token[1] %s \n", input[1]);
        executeCmd(input);

    }
    return 0;
}