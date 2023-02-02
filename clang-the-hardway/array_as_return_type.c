#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE 10

// NOTE: The " ({ ... })" construct is a GNU specific extension. Microsoft's
// compiler does not support it.
#define SIZE_CMP(orig, given)  \
  ({                           \
    size_t ret_val;            \
    do {                       \
      if (orig < given) {      \
        ret_val = given;       \
      } else {                 \
        ret_val = orig;        \
      }                        \
    } while (0);               \
    ret_val;                   \
  })

// Source from:
// https://stackoverflow.com/questions/14297169/how-to-make-an-array-return-type-from-c-function

int *init(const size_t size, int input)
{
  // NOTE: C doesn't advocate returning the address of a local variable
  //  outside of the scope of its bound function. If you intend to do this,
  //  the variable should be declared with a static type.
  //
  //  This concept is similar to the lifetime expansion in Rust,
  //  a technique to indicate to the compiler that the annotated variables
  //  or fields (struct) must be callable at least after the
  //  return instruction is invoked.

  // FIXME: Error "Initializer element is not a compile-time constant with `malloc`".
  //  A "large" object is never a constant expression in C, even if
  //  the object declared as `const`. Const-qualified objects (of any type)
  //  are not constants in C language terminology. They cannot be used in
  //  initializers of objects with static storage duration, regardless of
  //  their type.
  //  Same error: an attempt to initialize a static object with a
  //  non-constant.
  /* static */ int *factor = malloc(sizeof(int) * size);
  if (factor == NULL)
  	return 0;
  for (size_t start = 0; start < size; start++) {
  	factor[start] = (int)size + input;
  }
  return factor;
}

typedef struct Custom_Array {
  size_t size;
  int arr[DEFAULT_SIZE];
} Custom_Array;

Custom_Array new_arr(size_t size_, int arr_[])
{
  Custom_Array a = {0};
#ifdef DEFAULT_SIZE
  size_ = SIZE_CMP(DEFAULT_SIZE, size_);
#endif
  arr_ = &arr_[size_];

  a.size = size_;
  // NOTE: `sizeof` returns size of `*int` not `&int`.
  if (sizeof(a.size) != sizeof(&arr_)) {
  	return a;
  }
  for (size_t i = 0; i < size_; i++) {
  	a.arr[i] = arr_[i];
  }
  return a;
}

void returns_an_arr(void (*accept)(void *))
{
  char arr[] = "Something else!!!";
  accept(arr);
}

void on_accept(void *res)
{
  puts((char *)res);
}

// NOTE: To compile C code in Windows, please use:
//  + Prompt: Visual Studio 2017 Developer Command Prompt v15.0.
//  + Command: `cl /W4 main.c && main.exe`.

int main(void)
{
  // 01292023:
  printf("Hello World\n");
  size_t size = 10;
  int input = 10;
  int *f = init(size, input);
  for (size_t i = 0; i < size; i++) {
    // NOTE: Access element through its index doesn't require indirection
    //  operator. Syntax error: `*f[i]`.
    printf("%d\n", f[i]);
  }
  free(f);

  // 01302023:
  returns_an_arr(on_accept);

  // FIXME: Error "Signal: segmentation fault (core dumped)".
  size_t n_size = 50;
  int empty_arr[n_size];
  Custom_Array arr = new_arr(n_size, empty_arr);
  for (size_t i = 0; i < n_size; i++) {
    arr.arr[i] = DEFAULT_SIZE;
  }
  printf("%d\n", (int)arr.size);

  return 0;
}
