#include <stdbool.h>
#include <stdio.h>

#include "main.h"

#define ARR_SIZE 20

#define SIZEOF_ARR(arr) (sizeof(arr) / sizeof(*arr))
#define SIZEOF_ARR_ALT(arr) (sizeof(arr) / sizeof((arr)[0]))

// Resource: https://learnxinyminutes.com/docs/c/

// NOTE: Double the number passed in as `x`, returning the new value to the function caller.
int double_input_as_ref(int x)
{
  printf("Passed by another reference checker: %p\n", &x);
  printf("From %p ", &x);
  return 2 * x;
}

void double_input_as_orig(int *x)
{
  printf("Passed by original address checker: %p\n", x);
  *x *= 2;
}

int main(void)
{
  int x = 0;
  printf("%p\n", &x);
  printf("%p\n", (void *)&x); // NOTE: Have the same output as the above statement.

  int *ptr;
  ptr = &x; // NOTE: Point to variable x(type, value).
  int not_ptr;
  printf("Ptr: %zu, Non-ptr: %zu (in-length)\n", sizeof(ptr), sizeof(not_ptr));

  // Arithmetic expression with the pointee's value.
  printf("Dereference: %d\n", *ptr);
  (*ptr)++;
  printf("(Dereference value: %d) == (Original value: %d)\n", *ptr, x);

  // Array in C:
#ifndef ARR_SIZE
  int arr[20];
#else
  int arr[ARR_SIZE]; // NOTE: Cannot change the initialized size of an array.
#endif

  for (int i = 0; i < ARR_SIZE; i++) {
    arr[i] = 20 - i;
    printf("Idx: %d, Val: %d, Size: %zu\n", i, arr[i], sizeof(i));
  }

  // NOTE: Declare a pointer of type int and initialize it to point
  //  to our arr.
  int *arr_ptr = arr;
  // NOTE: arr_ptr now points to the first element of the array.
  //  The reason behind this behaviour depend on the way arrays often decay
  //  into pointer to their first element.
  //
  //  For example, when an array is passed to a function or is assigned to a
  //  pointer it implicitly converted to a pointer.
  printf("Array's pointer: %p, Dereferences/indirects to the first element: %d\n", arr_ptr, *arr_ptr);

  // FIXME: `int (*ptr_to_arr)[ARR_SIZE] = &arr;`, `&arr` is NOT of type `int *` but `[20]int *`!
  int *ptr_to_arr = &arr[0];
  printf("Dereferences/indirects to the first element: %d\n", *ptr_to_arr);

  // NOTE: Determine the number of elements in the array.
  int grades[3];
  int average;

  grades[0] = 80;
  // TODO: define the missing grade so that the average will sum to 85.
  grades[2] = 90;
  // NOTE: Type of `grades` changes `int -> long` -> the expression `sizeof(int) -> sizeof(long)` simultaneously.
  //  If forgot to change, some nasty bug will be appeared.
  int arr_len = sizeof(grades) / sizeof(int);
  if (NULL == &arr_len || arr_len == 0) {
    arr_len = SIZEOF_ARR(grades);
  }
  grades[1] = 85*arr_len - (grades[0] + grades[2]);

  average = (grades[0] + grades[1] + grades[2]) / 3;
  printf("The average of the %d grades is: %d\n", arr_len, average);

  bool first_ptr = (*grades == grades[0]);
  printf("Is underlying value of first element == array's pointer: %d\n", first_ptr);

  bool cmp_macro_result = (SIZEOF_ARR(grades) == SIZEOF_ARR_ALT(grades));
  printf("Tranquilize the comparision above by using macro rule instead: %d\n", cmp_macro_result);

  // NOTE: Characters sequence initialization (string).
  char hello_0[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
  char hello_1[] = "Hello";
  char *hello_2 = "Hello"; // NOTE: In C, a string is an array of `char` data, terminated with the `\0` character.
  printf("%s~%s~%s\n", hello_0, hello_1, hello_2);

  // NOTE: Pass by value of pass by reference in C.
  int magic_no = 10e5;
  printf("Archetype address: %p\n", &magic_no);

  double_input_as_orig(&magic_no);
  printf("Rock solid address: %p\n", &magic_no);

  int ref_val = double_input_as_ref(magic_no);
  printf("to %p address\n", &ref_val);


  // NOTE(learning): Until `char otherarr[] = "foobarbazquirk";`.
  return 0;
}
