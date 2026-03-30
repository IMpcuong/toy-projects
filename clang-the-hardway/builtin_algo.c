#include <stdio.h>
#include <stdlib.h>

int compare_type_int(const void *f, const void *s)
{
  const int *fi = f;
  const int *si = s;

  if (*fi == *si)
    return 0;

  if (*fi > *si)
    return 1;
  return -1;
}

void print_arr(const int *arr, const int sz)
{
  for (int i = 0; i < sz; i++)
    printf("%d%c", arr[i], " \n"[i == sz - 1]);
}

int main()
{
#define _sz 5
  int a[_sz] = {17, 13, 8, 128, 69};
  qsort(a, _sz, sizeof(int), compare_type_int);
  print_arr(a, _sz);

  int *f_found = bsearch(&(int){128}, a, _sz, sizeof(int), compare_type_int);
  printf("BSearch ans := %d", *f_found);
  putchar('\n');

  int need = 13;
  int *s_found = bsearch(&need, a, _sz, sizeof(int), compare_type_int);
  printf("BSearch ans := %d", *s_found);

  return 0;
}
