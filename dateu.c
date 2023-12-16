#include <time.h>
#include <stdio.h>


int main(void)
{
  struct tm *local;
  time_t t;
  t = time(NULL);
  local = gmtime(&t);
  printf("UTC time and date: %s", asctime(local));

  return 0;
}