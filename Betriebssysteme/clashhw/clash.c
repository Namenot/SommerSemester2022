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
    {
        execvp(command[0], command);
        exit(EXIT_SUCCESS);
    }
    
    if(child > 0)
        waitpid(child, &wstatus, WUNTRACED | WCONTINUED);

    return wstatus;
}

size_t getinput(char ***chopper)
{
    size_t chopps = 0;
    size_t inlen = 0;

    char *input = NULL;
    char *choppedpiece;
    
    // get the input
    inlen = getline(&input, &inlen, stdin);

    input = realloc(input, sizeof(char) * (inlen+1));
    input[inlen - 1] = ' ';
    input[inlen] = 0;

    // make sure our command length is legal
    if(inlen > 1337)
    {
        printf("illegal command length : MAX allowed length is 1337\n");
        return inlen;
    }

    // space, tab, string terminator
    const char delims[3] = {32, 9, 0};

    // init chopper to a length
    *chopper = malloc(sizeof(char*) * chopps);
    do
    {
        // make space for the new element
        chopps ++;
        *chopper = realloc(*chopper, sizeof(char*) * chopps);
        
        //chop up the command and the options into different strings
        choppedpiece = strtok(input, delims);
        input = NULL;
        (*chopper)[chopps -1] = choppedpiece;

    }while(choppedpiece != NULL);

    return (chopps -1);
}

int main(int argc, char **argv)
{
    // according to the internet a path cant be longer than 4096 bytes 
    // i accept this arcane knowledge as absolut truth 
    char dir[4096];
    char **choppedassembly = malloc(0);
    
    while(1)
    {
        // retrive and print current path
        getcwd(dir, 4096);
        printf("%s/: ", dir);
        size_t size = getinput(&choppedassembly);

        int execstat = executecommand(choppedassembly);

        printf("Exitstatus [");

        for(size_t i = 0; i < size; ++i)
        {
            printf("%s", choppedassembly[i]);
            if(size -1 != i)
                printf(" ");
        }
        
        printf("] = %d\n", execstat);
    }

    free(*choppedassembly);
    free(choppedassembly);
    printf("\n");

    return 0;
}