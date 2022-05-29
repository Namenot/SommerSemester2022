#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "plist.h"

void execProcess(pid_t child, int fb, char **command);
int manageCommand(char **command);
size_t getinput(char ***chopper);
char *reassembleCmd(char **command, char *output);

int manageCommand(char **command)
{

    char *reservedfunctions[] = {"cd", "ps", "&"};

    //check if command is not 0
    int i = 0;
    for(; command[i] != NULL; ++i);

    if(i == 0)
        return 0;
    
    int fb = 1;
    
    if(!strcmp(command[i-1], "&")) // is a background process?
    {
        fb = 0; // tell them its a background process
        command[i-1] = NULL;
    }

    pid_t child = fork();
    int wstatus = 0;

    if(!strcmp(command[0], reservedfunctions[0]))
    {
        printf("switching directory\n");
    } // change directory
    else if(!strcmp(command[0], reservedfunctions[1]))
    {
        printf("this should be printing all the running processes\n");
    } // print processes
    else 
        execProcess(child, fb, command);
    
    return wstatus;
}

void execProcess(pid_t child, int fb, char **command)
{   
    int wstatus = 0; 

    if (child == 0)
    {   
        if(fb == 1)
            execvp(command[0], command);
        else
        {
            execvp(command[0], command);
        }
        exit(EXIT_SUCCESS);
    }
    
    if(child > 0)
    {
        printf("the parent is reporting that fb is : %d\n", fb);
        if(fb == 1)
        {
            waitpid(child, &wstatus, WUNTRACED | WCONTINUED);
            
            printf("Exitstatus [");

            char assmbledcommand[1337] = ""; // 1337 is the max string length allowed for a command
            reassembleCmd(command, assmbledcommand);
            printf("%s", assmbledcommand);
        
            printf("] = %d\n", wstatus);
        }
        else
            {}//add to plist
    }
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

char *reassembleCmd(char **command, char *output)
{
    char spacecowboy[] = " ";

    for(int i = 0; command[i] != NULL; ++i)
    {
        strcat(output, command[i]);
        if(command[i+1] != NULL)
            strcat(output, spacecowboy);
    }

    return output;
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
        //size_t size = 
        getinput(&choppedassembly);

        manageCommand(choppedassembly);
    }

    free(*choppedassembly);
    free(choppedassembly);
    printf("\n");

    return 0;
}

/* TODO:
 * - manageCommand(); check for reservedfunctions in command (obv based on the specific function) [done]
 * - executeBackgroundProcess(); insert every background pid and command into a plist specified in main() 
 * - main(); collect finisched pid's and removed them from plist -> walkList(), waitpid(WNOHANG)
 */