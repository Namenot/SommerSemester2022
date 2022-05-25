#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{

    char s[255];
    fgets(s, 255, stdin);
    FILE *fp = fopen("out.txt", "w+");


    fprintf(fp, "HAllo welt ich bin  hier");
    fclose(fp);
    return 0;
}