#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

char* ab;
char* q;
bool parse(const char* line, char* abs_path, char* query)
{
    if (strncmp(line, "GET ", 4) != 0)
    {

        return false;
    }

    if (line[4] != '/')
    {

        return false;
    }
    if(strchr(line, '"')!= NULL)
    {

        return false;
    }
    int pos = 0;
    for(int i = 0; i < strlen(line);i++)
    {
        if(line[i] == ' ')
        {pos = i;}
    }
    char temp[9];
    for (int i = pos, j = 0; i < strlen(line); i++,j++)
    {
        temp[j] = line[i];
    }
   if(strcmp(temp, " HTTP/1.1") != 0)
   {

       return false;
   }
    char target[100];
    target[0] = line[4];
    int i = 5, j=1;
    while(line[i] != ' ')
    {
        target[j] = line[i];
        i++;j++;
    }
    char absolute[100];
    int h = 0;
    while(target[h] != '?')
    {
        absolute[h] = target[h];
        h++;
    }
    query = &target[h+1];
    abs_path = absolute;
    return true;

}


int main(void)
{

    bool temp = parse("GET test/cat.php?q=bebe HTTP/1.1", ab,q);
    if(temp)
    printf("%s  %s", ab, q);
}