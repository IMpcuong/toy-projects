#include <stdbool.h>
#include <stdio.h>
#include <Windows.h>

#include "main.h"

#define ARR_SIZE 20

#define SIZEOF_ARR(arr) (sizeof(arr) / sizeof(*arr))
#define SIZEOF_ARR_ALT(arr) (sizeof(arr) / sizeof((arr)[0]))

#define CMP_PAIR(lhs, rhs) (lhs == rhs ? "True" : "False")
#define CMP_ONE(bool_val) (bool_val == 1 ? "True" : "False")

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

typedef struct nested_control
{
  char *outer;
  struct nested_setting
  {
    float id;
    char *desc;
  } **settings; // Usage: Pointer to an array.
} nested_control;

void looping_through_ptr_arr(void)
{
  for (char **name = (char *[]){"uid", "gid", "oid", 0}; *name; name++)
  {
    printf("%s\t", *name);
  }
  printf("\n");

  struct nested_setting base_setting = {
      .id = 0.0,
      .desc = "Settings controller-default",
  };

  // NOTE: Pointer to an array -> { `char **char_ptr` == `char *char_ptr[]` || `**` == `*[]` }.
  struct nested_control *controllers[] = {
      &(struct nested_control){
          .outer = "controller0",
          .settings = (struct nested_setting *[]){
              &base_setting,
              // NOTE: Adding trailing NULL element to avoid below error.
              //    Error: `CRT: unhandled exception (main) -- terminating`.
              NULL,
          },
      },
      &(struct nested_control){
          .outer = "controller1",
          .settings = (struct nested_setting *[]){
              &(struct nested_setting){
                  .id = 1.1,
                  .desc = "Settings controller-2.1",
              },
              &(struct nested_setting){
                  .id = 1.2,
                  .desc = "Settings controller-2.2",
              },
              NULL,
          },
      },
      NULL,
  };

  // NOTE: Looping by using object's pointer incrementation.
  //    `nested_control **ctrl` := first element's pointer (representation/embodiment of the whole array).
  //    `for (...)` := `for (first pointer; if its pointee's address != NULL; pointer++)`.
  for (struct nested_control **ctrl = controllers; *ctrl != NULL; ++ctrl)
  {
    printf("%s\n", (*ctrl)->outer);
    for (struct nested_setting **setup = (*ctrl)->settings; *setup != NULL; ++setup)
    {
      printf("\t(%.1f; %s)\n", (*setup)->id, (*setup)->desc);
    }
  }
}

// `spawn_thread` is defined as the entry point for the new thread.
// This function take a single parameter `lp_param`, which is a pointer
// to any data that you want to pass to the new spawned thread.
DWORD WINAPI spawn_thread(LPVOID lp_param)
{
  int *thread_ptr = (int *)(lp_param);
  printf("This's another thread, with sample parameter's pointer value: %p\n", thread_ptr);
  return 0;
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

  for (int i = 0; i < ARR_SIZE; i++)
  {
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
  if (NULL == &arr_len || arr_len == 0)
  {
    arr_len = SIZEOF_ARR(grades);
  }
  grades[1] = 85 * arr_len - (grades[0] + grades[2]);

  average = (grades[0] + grades[1] + grades[2]) / 3;
  printf("The average of the %d grades is: %d\n", arr_len, average);

  bool first_ptr = (*grades == grades[0]);
  printf("Is underlying value of first element == array's pointer: %s\n", CMP_ONE(first_ptr));

  bool cmp_macro_result = (SIZEOF_ARR(grades) == SIZEOF_ARR_ALT(grades));
  printf("Tranquilize the comparision above by using macro rule instead: %s\n", CMP_ONE(cmp_macro_result));

  // NOTE: Characters sequence initialization (string).
  char hello_0[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
  char hello_1[] = "Hello";
  char *hello_2 = "Hello"; // NOTE: In C, a string is an array of `char` data, terminated with the `\0` character.
  printf("%s~%s~%s\n", hello_0, hello_1, hello_2);

  // NOTE: Pass by value of pass by reference in C.
  int magic_no = 10e5;
  printf("Archetype address + value: %p + %d\n", &magic_no, magic_no);

  double_input_as_orig(&magic_no);
  printf("Rock solid address: %p\n", &magic_no);

  int ref_val = double_input_as_ref(magic_no);
  printf("to %p address\n", &ref_val);

  printf("Compare value after doubling (%d == %d): %s\n", ref_val, magic_no, CMP_PAIR(ref_val, magic_no));

  looping_through_ptr_arr();

  // NOTE: Spawning C thread example.
  HANDLE h_thread;
  DWORD dw_thread_id;

  // * The first parameter is a `security attribute`, which can be set to NULL for default security.
  // * The second parameter is the `initial stack size` for the thread, which can be set to 0 to use the default stack size.
  // * The third parameter is the `entry point` for the thread, which is `spawn_thread` in this case.
  // * The fourth parameter is the `argument` to pass to the thread, which is &average in this case.
  // * The fifth parameter is the `creation flags`, which can be set to 0 for default behavior.
  // * The sixth parameter is a `pointer` to a DWORD that will receive the thread identifier.
  h_thread = CreateThread(NULL, 0, spawn_thread, &average, 0, &dw_thread_id);
  if (NULL == h_thread)
  {
    printf("Failed to create a new thread!\n");
    return 1;
  }
  printf("This's the main thread, with sample parameter's pointer value: %p\n", h_thread);
  // NOTE: The main thread waits for the new thread to finish using the
  //  `WaitForSingleObject` function, which blocks the terminated signal
  //  to be returned, until the specified object (thread-handler) is reaching
  //  the signaled state.
  WaitForSingleObject(h_thread, INFINITE);
  // NOTE: Close the thread handler.
  CloseHandle(h_thread);

  // NOTE(learning): Until `char otherarr[] = "foobarbazquirk";`.
  return 0;
}
