#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#pragma warning(disable : 4710)
#pragma warning(disable : 4204)
#endif

#define DEFAULT_SIZE 10

// NOTE: Analogous with the macro rule as below.
// #define SIZEOF_ARR(arr) ((size_t)(sizeof arr) / sizeof arr[0])
#define SIZEOF_ARR(arr) ((size_t)(sizeof(arr) / sizeof(*arr)))
#define CMP_PAIR(lhs, rhs) (lhs == rhs ? "True" : "False")

// NOTE:
//  + The " ({ ... })" construct is a GNU specific extension. Microsoft's
//    compiler does not support it.

/**
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
*/

//  + The `typeof(T)` built-in function only supported by GNU C Extensions;
//    lots of these language features are not found in ISO standard C, pedantically.
//    Link: https://gcc.gnu.org/onlinedocs/gcc-4.9.3/gcc/Typeof.html#Typeof.

/**
#define max(a, b)       \
  {(                    \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _a < _b ? _b : _a;  \
  )}                    \
*/

// NOTE: Follows `winsock.h` coding conventions.
#undef wSIZE_CMP
#define wSIZE_CMP(orig, given, __ret_val)                      \
  do                                                           \
  {                                                            \
    (orig < given) ? (__ret_val = given) : (__ret_val = orig); \
  } while (0)

#define lSIZE_CMP(orig, given, __ret_val) \
  do                                      \
  {                                       \
    if (orig < given)                     \
    {                                     \
      __ret_val = given;                  \
    }                                     \
    else                                  \
    {                                     \
      __ret_val = orig;                   \
    }                                     \
  } while (0)

// Source from:
// https://stackoverflow.com/questions/14297169/how-to-make-an-array-return-type-from-c-function

static int *init_arr(const size_t size, /* default = 0 */ const int input)
{
  // NOTE: C doesn't advocate returning the address of a local variable
  //    outside of the scope of its bound function. If you intend to do this,
  //    the variable should be declared with a static type.
  //
  //    This concept is similar to the lifetime expansion in Rust,
  //    a technique to indicate to the compiler that the annotated variables
  //    or fields (struct) must be callable at least after the
  //    return instruction is invoked.

  // FIXME: Error "Initializer element is not a compile-time constant with `malloc`".
  //    A "large" object is never a constant expression in C, even if
  //    the object declared as `const`. Const-qualified objects (of any type)
  //    are not constants in C language terminology. They cannot be used in
  //    initializers of objects with static storage duration, regardless of
  //    their type.
  //    Same error: an attempt to initialize a static object with a
  //    non-constant.
  if (0 == size)
    return 0;
  int *factor = malloc(sizeof(int) * size);
  if (NULL == factor)
    return 0;

  for (size_t i = 0; i < size; i++)
  {
    factor[i] = (int)size + input;
  }
  return factor;
}

typedef struct CustomArray CustomArray, *ca;
struct CustomArray
{
  size_t size;
  int *child_arr;

  void (*print_childs)(CustomArray *);
};

// NOTE: Type definition abbreviation.
/**
typedef struct Position {
  x, y int;
} Position;
*/

void ca_print_childs(CustomArray *self)
{
  if (0 == self->size)
    printf("Zero-length array: %zu", self->size);

  printf("%s\n", CMP_PAIR(self->size, SIZEOF_ARR(self->child_arr)));
  for (size_t i = 0; i < self->size; i++)
  {
    printf("Idx: %zu / Val: %d\n", i, (self->child_arr)[i]);
  }
}

// NOTE: `int *arr_` -> `SIZEOF_ARR(arr_) = 2`.
//       `int **arr_` -> `SIZEOF_ARR(arr_) = 1`.
static inline CustomArray *new_custom_arr(size_t size_, int *arr_)
{
  size_t __arg_arr_size = SIZEOF_ARR(arr_);
  printf("Arg-array's len = %zu\n", __arg_arr_size);

  // Alter native method for `new` keyword in C:
  // int *p = malloc(sizeof(*p)); // int* p = new int;
  // ...
  // free(p);

  size_t out_;
#ifdef DEFAULT_SIZE
  wSIZE_CMP(DEFAULT_SIZE, size_, out_);
#else
  // HACK: Verbose version for this macro rule's implementation.
  lSIZE_CMP(0, size_, out_);
#endif
  printf("arr_'s size = %zu (%s)\n", out_, CMP_PAIR(out_, size_));

  CustomArray *__custom = {0};
  // FIXME: Cannot reassign the array argument's size.
  //    Because it already has a fixed size.
  // arr_ = &arr_[size_]; // Correct syntax, but wrong semantic.

  // FROM: https://stackoverflow.com/questions/11207783/read-and-write-to-a-memory-location
  __custom = (CustomArray *)malloc(sizeof(CustomArray) * 1);
  if (__custom)
  {
    __custom->size = out_;
    // NOTE: `sizeof` returns size of `*int` not `&int`, valid e.g. `sizeof(&arr_)`.
    // NOTE: `sizeof(int)` with a type name, the name must be enclosed in parentheses.
    //       `sizeof <expr>` when used with an expression, can be specified with or without parentheses.
    //       `sizeof` is an operator.
    __custom->child_arr = init_arr(__custom->size, (int)__arg_arr_size);
    printf("__custom := (size / first) ~ (%zu / %d)\n", __custom->size, *__custom->child_arr);

    return __custom;
  }
  return NULL;
}

static inline void returns_an_arr(void (*accept)(void *))
{
  char arr[] = "Something else!!!";
  accept(arr);
}

static inline void on_accept(void *res)
{
  puts((char *)res);
}

int sum_variadic_args(size_t count, ...)
{
  int res = 0;
  va_list args;
  va_start(args, count);
  for (size_t i = 0; i < count; i++)
  {
    int tmp = va_arg(args, int);
    res += tmp;
  }
  va_end(args);
  return res;
}

// NOTE: To compile C code in Windows, please use:
//  + Prompt: Visual Studio 2017 Developer Command Prompt v15.0.
//  + Command: `cl /W4 main.c && main.exe`.
//             `cl /O2 /analyze:WX- /Ze /Wall array_as_return_type.c /o aart && aart.exe`.

int main(void)
{
  // 01292023:
  printf("Hello World!!!\n");

  size_t size = 10;
  int input = 10;
  int *f_arr = init_arr(size, input);
  for (size_t i = 0; i < size; i++)
  {
    // NOTE: Access element through its index doesn't require indirection
    //    operator. Syntax error: `*f[i]`.
    printf("Part 1: %d\n", f_arr[i]);
  }

  // 01302023:
  returns_an_arr(on_accept);

  // size_t x = ...;
  // ssize_t y = ...;
  // printf("%zu\n", x);  // Prints as unsigned decimal.
  // printf("%zx\n", x);  // Prints as hex.
  // printf("%zd\n", y);  // Prints as signed decimal.

  // FIXME: Error "Signal: segmentation fault (core dumped)".
  static size_t N_SIZE = 50;
  int *ca_childs = init_arr(N_SIZE, 0);
  CustomArray ca = {
      .size = N_SIZE,
      .child_arr = (int *)(0),
      .print_childs = NULL,
  };
  ca.child_arr = ca_childs;

  // NOTE: Struct methods implementation in C.
  //    No needed anymore, when the struct initializer has already do this.
  ca.print_childs = ca_print_childs; // Function assignment.
  ca.print_childs(&ca);
  printf("Initialize `CustomArray ca`: (size / first) ~ (%zu / %d)\n", ca.size, *ca.child_arr);

  CustomArrayPtr arr = new_custom_arr(N_SIZE, ca.child_arr);
  printf("`CustomArray *arr` destructuring: (size, arr_ptr) = (%zu, %p)\n", arr->size, (void *)(arr->child_arr));

  arr->print_childs = ca_print_childs;
  arr->print_childs(arr);

  printf("Part 2.2: %zu\n", arr->size);

  int sum = sum_variadic_args(2, (arr->child_arr)[0], (arr->child_arr)[1]);
  printf("Part 3: %d\n", sum);

  free(f_arr);
  free((void *)ca.child_arr);
  free(arr->child_arr);

  return 0;
}
