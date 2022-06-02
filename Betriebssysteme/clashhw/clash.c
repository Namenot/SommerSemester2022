#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "plist.h"

int printPorcesses(pid_t process, const char * process_name);
int collectAll(pid_t process, const char * process_name);
int manageCommand(char **command);
size_t getinput(char ***chopper);
char *reassembleCmd(char **command, char *output);
void execProcess(pid_t child, int fb, char **command);


void die(const char * msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int collectAll(pid_t process, const char * process_name)
{
    int wstatus = 0;
    // collecting all processes

    if(waitpid(process, &wstatus, WUNTRACED | WCONTINUED | WNOHANG) != 0)
        removeElement(process, NULL, 0);

    return 0;
}

int printPorcesses(pid_t process, const char * process_name)
{
    printf("[%d] | %s\n", process, process_name);
    return 0;
}

int manageCommand(char **command)
{

    char *reservedfunctions[] = {"cd", "jobs"};

    // switch directory
    if(strcmp(command[0], reservedfunctions[0]) == 0)
    {
        // change directory
        if(chdir(command[1]) == -1)
            printf("Couldnt change directory to %s\n", command[0]);
        return 0;
    }

    //check if command is not 0
    int i = 0;
    for(; command[i] != NULL; ++i);

    if(i == 0)
        return 0;
    
    int fg = 1; // foreground command
    int wstatus = 0;

    if(!strcmp(command[i-1], "&")) // is a background process?
        fg = 0; // tell them its a background process

    pid_t child = fork();

    if(child < 0)
        return -1;

    if(child > 0)
    {
        //printf("the parent is reporting that fb is : %d\n", fb);
        char assmbledcommand[1337] = ""; // 1337 is the max string length allowed for a command
        reassembleCmd(command, assmbledcommand);
    
        //add to plist
        insertElement(child,assmbledcommand);

        if(fg == 1)
        {
            waitpid(child, &wstatus, WUNTRACED | WCONTINUED);
            
            removeElement(child, NULL, 0);

            printf("Exitstatus [");
            printf("%s", assmbledcommand);
            printf("] = %d\n", wstatus);
        }
    }

    if(child == 0)
    {
        if(fg == 0)
            command[i-1] = NULL;

        if(strcmp(command[0], reservedfunctions[1]) == 0)
        {
            // print processes
            walkList(printPorcesses);
        }
        else
        {
            execvp(command[0], command);
        }
        exit(EXIT_SUCCESS);
    }
    
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
    
    fflush(stdin);

    // if getline sees ctrl + D / eof
    if(inlen == -1)
        return -1;
    
    if(inlen < 1)
        return -1;

    input = realloc(input, sizeof(char) * (inlen+1));
    input[inlen - 1] = ' ';
    input[inlen] = 0;

    // make sure our command length is legal
    if(inlen >= 1337)
    {
        printf("illegal command length : MAX allowed length is 1337\n");
        return 0;
    }

    // space, tab, string terminator
    const char delims[3] = {32, 9, 0};

    // init chopper to a length
    *chopper = malloc(sizeof(char*) * chopps);
    if(*chopper == NULL) 
    {
        perror("couldnt allocated *chopper\n");
        return 0;
    }

    do
    {
        // make space for the new element
        chopps ++;
        *chopper = realloc(*chopper, sizeof(char*) * chopps);

        if(*chopper == NULL) 
        {
            perror("couldnt re-allocated *chopper\n");
            return 0;
        }
        
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
    char **choppedassembly = NULL;
    
    int iStatus = 0;

    while(1)
    {
        // retrive and print current path
        getcwd(dir, 4096);
        printf("%s/: ", dir);
        
        // get input and execute the command
        iStatus = getinput(&choppedassembly);

        // do we have a valid command?
        if(iStatus > 0)
            manageCommand(choppedassembly);

        // collect all running processess
        walkList(collectAll);

        // end the shell
        if(iStatus == -1)
            break;
    }

    printf("\n");

    if(choppedassembly != NULL)
    {
        for(int i = 1; choppedassembly[i] != NULL; ++i)
            free(choppedassembly[i-1]);

        free(choppedassembly);
    }

    return 0;
}