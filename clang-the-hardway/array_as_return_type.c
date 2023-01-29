#include <stdio.h>
#include <stdlib.h>

// Source from: https://stackoverflow.com/questions/14297169/how-to-make-an-array-return-type-from-c-function

int* init(size_t size, int input) {
  int* factor = malloc(sizeof(int) * size);
  if (factor == NULL) return 0;
  for (size_t start = 0; start < size; start++) {
      factor[start] = (int)size + input;
  }
  return factor;
}

// NOTE: To compile C code in Windows, please use:
//  + Prompt: Visual Studio 2017 Developer Command Prompt v15.0.
//  + Command: `cl /W4 main.c && main.exe`.

int main() {
  printf("Hello World\n");
  size_t size = 10;
  int input = 10;
  int* f = init(size, input);
  for (size_t i = 0; i < size; i++) {
      // NOTE: Access element through its index doesn't require indirection
      // operator. Syntax error: `*f[i]`.
      printf("%d\n", f[i]);
  }
  free(f);
  return 0;
}