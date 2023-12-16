#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>

int main()
{
    time_t t;   // not a primitive datatype
    time(&t);
    printf("%s", ctime(&t));
    return 0;
}