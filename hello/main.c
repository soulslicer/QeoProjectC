#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc > 1) printf("Your name is %s\n", argv[1]);
  else printf("Your name is not knowns\n");
}