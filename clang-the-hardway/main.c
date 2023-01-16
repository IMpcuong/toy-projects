#include <stdio.h>

#define ARR_SIZE 20

// Resource: https://learnxinyminutes.com/docs/c/

int main() {
	int x = 0;
	printf("%p\n", &x);
	printf("%p\n", (void *)&x); // NOTE: Have the same output as above statement.

	int *ptr;
	ptr = &x; // NOTE: Point to variable x(type, value).
	int not_ptr;
	printf("Ptr: %zu, Non: %zu (in-length)\n", sizeof(ptr), sizeof(not_ptr));

	// Arithmetric expression with the pointee's value.
	printf("Dereference: %d\n", *ptr);
	(*ptr)++;
	printf("%d == %d\n", *ptr, x);

	// Array in C:
	int arr_size = 20; // NOTE: Using scoped variable or preprocessor.
	int arr[ARR_SIZE]; // NOTE: Cannot change the initiallized size of an array.
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
	printf("%p, %d\n", arr_ptr, *arr_ptr);

	// FIXME: `int (*ptr_to_arr)[ARR_SIZE] = &arr;`, `&arr` is NOT of type `int *` but `[20]int *`!
	int *ptr_to_arr = &arr[0];
  	printf("%d\n", *ptr_to_arr);

  	// NOTE(learning): Until `char otherarr[] = "foobarbazquirk";`.
	return 0;
}
