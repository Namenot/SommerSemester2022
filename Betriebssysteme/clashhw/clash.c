#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int executecommand(char **command)
{   

    pid_t child = fork();
    int wstatus;
    
    if (child == 0)
        execl(command[0], *(command + 1));
    
    if(child > 0)
        waitpid(child, &wstatus, WUNTRACED | WCONTINUED);
    
    return wstatus;
}

size_t getinput(char ***chopper)
{
    size_t chopps = 1;
    size_t inlen = 0;

    char *input = NULL;
    char *choppedpiece;
    
    // space, tab, string terminator
    char delims[3] = {32, 9, 0};
    inlen = getline(&input, &inlen, stdin);

    //chop up the command and the options into different strings
    choppedpiece = strtok(input, delims);

    *chopper = malloc(sizeof(char*) * chopps);

    // cutting board
    while( choppedpiece != NULL )
    {
        (*chopper)[chopps -1] = choppedpiece;
        chopps ++;
        *chopper = realloc(*chopper, sizeof(char*) * chopps);
        choppedpiece = strtok(NULL, delims);
    }
    // now the input can be free'd
    *chopper = realloc(*chopper, sizeof(char*) * (chopps -1));

    return (chopps - 1);
}

int main(int argc, char **argv)
{
    
    // set reasonable limit for how long a directory is gonna be 
    // (i usually didnt supass 80 however i found it to be on the safer site)
    char dir[255];
    char **choppedassembly = malloc(0);

    // retrive and print current path
    getcwd(dir, 255);
    printf("%s/:", dir);
    size_t size = getinput(&choppedassembly);

    for(size_t i = 0; i < size; ++i)
        printf("%s\n", choppedassembly[i]);

    executecommand(choppedassembly);

    free(*choppedassembly);
    free(choppedassembly);
    printf("\n");
    return 0;
}