#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{

    char s[255];
    fgets(s, 255, stdin);

    printf("%s\n", s);

    return 0;
}