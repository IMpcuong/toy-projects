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
  printf("Passed by another reference checker: %p\n", (void *)&x);
  printf("From %p ", (void *)&x);
  return 2 * x;
}

void double_input_as_orig(int *x)
{
  printf("Passed by original address checker: %p\n", (void *)x);
  *x *= 2;
}

typedef struct NestedControl
{
  char *outer;
  struct NestedSetting
  {
    double id;
    char *desc;
  } **settings; // Usage: Pointer to an array.
} NestedControl;

void looping_through_ptr_arr(void)
{
  for (char **name = (char *[]){"uid", "gid", "oid", 0}; *name; name++)
  {
    printf("%s\t", *name);
  }
  printf("\n");

  struct NestedSetting base_setting = {
      .id = 0.0,
      .desc = "Settings controller-default",
  };

  // NOTE: Pointer to an array -> { `char **char_ptr` == `char *char_ptr[]` || `**` == `*[]` }.
  struct NestedControl *controllers[] = {
      &(struct NestedControl){
          .outer = "controller0",
          .settings = (struct NestedSetting *[]){
              &base_setting,
              // NOTE: Adding trailing NULL element to avoid below error.
              //    Error: `CRT: unhandled exception (main) -- terminating`.
              NULL,
          },
      },
      &(struct NestedControl){
          .outer = "controller1",
          .settings = (struct NestedSetting *[]){
              &(struct NestedSetting){
                  .id = 1.1,
                  .desc = "Settings controller-2.1",
              },
              &(struct NestedSetting){
                  .id = 1.2,
                  .desc = "Settings controller-2.2",
              },
              NULL,
          },
      },
      NULL,
  };

  // NOTE: Looping by using object's pointer incrementation,
  //    for more specific: using pointers as counters.
  //    `NestedControl **ctrl` := first element's pointer (representation/embodiment of the whole array).
  //    `for (...)` := `for (first pointer; if its pointee's address != NULL; pointer++)`.
  for (struct NestedControl **ctrl = controllers; *ctrl != NULL; ++ctrl)
  {
    printf("%s\n", (*ctrl)->outer);
    for (struct NestedSetting **setup = (*ctrl)->settings; *setup != NULL; ++setup)
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
  printf("This's another thread, with sample parameter's pointer value: %p\n", (void *)thread_ptr);
  return 0;
}

char *is_arr_eq_ptr(int arr_test[3])
{
  int third_1 = arr_test[2];
  int *ptr_test = arr_test;
  int third_2 = *(ptr_test + 2);
  return CMP_PAIR(third_1, third_2);
}

// NOTE: `struct` are just a `sizeof` and a bunch of offset types.
typedef struct MyStructType
{
  unsigned int type;
  char name[32];
  float size;
} MyStructType;

// Calculate the offset of a specified attribute from its own struct type.
char *get_offset_from_type(void)
{
  MyStructType *tmp = &(struct MyStructType){
      .type = 100,
      .name = "MST",
      .size = 10,
  };
  MyStructType *alter = malloc(sizeof *tmp);
  memmove(alter, tmp, sizeof *alter);

  size_t _size_attr_offset = offsetof(MyStructType, size);
  char *val = CMP_PAIR((size_t)(&alter->size), _size_attr_offset); // False.
  if (strcmp("False", val) == 0)
  {
    // NOTE: At address zero, a null pointer was created that points to our structure.
    MyStructType *mst_nullptr = (MyStructType *)NULL; // Akin with: `(MyStructType *)0`.

    // NOTE: Starting from the beginning of this struct pointer,
    //    we counted how many steps (offset) it took to reach `size`.
    size_t cal_offset = (size_t)(&mst_nullptr->size);
    val = CMP_PAIR(cal_offset, _size_attr_offset);
  }
  return val;
}

int main(void)
{
  int x = 0;
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
  printf("Array's pointer: %p, Dereferences/indirects to the first element: %d\n", (void *)arr_ptr, *arr_ptr);

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
  if (arr_len == 0)
    arr_len = SIZEOF_ARR(grades);
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
  printf("Archetype address + value: %p + %d\n", (void *)&magic_no, magic_no);

  double_input_as_orig(&magic_no);
  printf("Rock solid address: %p\n", (void *)&magic_no);

  int ref_val = double_input_as_ref(magic_no);
  printf("to %p address\n", (void *)&ref_val);

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

  int arr_test[3] = {1e3, 1e3, 1e3};
  printf("Is pointers equal array: %s\n", is_arr_eq_ptr(arr_test));

  char *size_attr_offset = get_offset_from_type();
  printf("%s\n", size_attr_offset);

  // NOTE(learning): Until `char otherarr[] = "foobarbazquirk";`.
  return 0;
}
