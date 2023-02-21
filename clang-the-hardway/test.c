#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  size_t num = 4;
  fprintf(stdout, "%zu", sizeof num);

  return 0;
}
