#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  char first;
  int middle;
  char last;

} OrderingVolatility;

typedef struct
{
  char first;
  char middle;
  int last;

} OrderingMatter;

int main(void)
{
  size_t num = 4;
  fprintf(stdout, "%zu\n", sizeof num);

  size_t ordered = sizeof(OrderingMatter);
  size_t volatility = sizeof(OrderingVolatility);
  char *is_greater = (ordered < volatility) ? "True" : "False";
  printf("`sizeof(OrderingMatter) < sizeof(OrderingVolatility)`: %s (%zu < %zu)\n",
         is_greater, ordered, volatility);

  return 0;
}
