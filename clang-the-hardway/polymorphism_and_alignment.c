#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

// HACK: `warning: function returns address of local variable [-Wreturn-local-addr]`.
//    1. Return a pointer to static memory.
//    2. Allocate memory dynamically.
//    3. Pass a pointer to the output buffer as a function argument.
inline char *karatsuba_algo(size_t lfactor, size_t rfactor)
{
  return (char *)(0 + lfactor + rfactor);
}

// 0. Polymorphism in C:

typedef enum MyStructType
{
  MST_INT,
  MST_FLOAT,
  MST_COUNT
} MyStructType;

typedef struct MyHeader
{
  char name[32];
  MyStructType type;
} MyHeader;

typedef struct MyStructInt
{
  MyHeader header; // Nifty/handy.
  int value;
} MyStructInt;

typedef struct MyStructFloat
{
  MyHeader header;
  float value;
} MyStructFloat;

void set_value_from(MyHeader *h, double value)
{
  if (h->type == MST_INT)
    // NOTE: The reason behind the `seems like inappropriate` casting operation
    //    is all about how we manage to align the offset of `MyHeader` to zero
    //    on both `MyStructInt` and `MyStructFloat`. That means the pointer
    //    is pointing to the `MyStructInt` or `MyStructFloat` is also indicating
    //    the `MyHeader`'s address (or a `MyHeader`'s pointer either).
    ((MyStructInt *)h)->value = (int)value;
  if (h->type == MST_FLOAT)
    ((MyStructFloat *)h)->value = (float)value;
}

// 1. Alignment (memory) makes things more complicated:

typedef struct
{
  unsigned char a;     // 1 byte.
  unsigned int b;      // 4 bytes (32 bits) -> Want to live in a `even` 4 byte addresses (addr % 4 == 0).
} AlignmentTestStruct; // Calculation: 5 bytes -> Reality: 8 bytes.

// Avoid wasting free memory (ordering matter):
typedef struct
{
  unsigned char a;
  unsigned char x;
  unsigned char y;
  unsigned char z;
  unsigned int b;
} UsingFreedStruct;

// Ordering won't always save your memory:
typedef struct
{
  unsigned int b;     // 4 bytes.
  unsigned char a;    // 1 byte.
} OrderingTestStruct; // NOTE: Theoretically speaking that the total size lied down on heap mem := 5 bytes.

// Manually packing: but auto-padding is `faster` and avoiding corruption better.

OrderingTestStruct *packing_mem_manually(int size)
{
  static unsigned char *mem;
  mem = malloc(5 * (size_t)size);
  OrderingTestStruct *ots = {0};

  // NOTE: This maybe very slow or even cause crash.
  int i;
  for (i = 0; i < size; i++)
  {
    // NOTE: We want the compiler to address exact 5 bytes per each object.
    ots = (OrderingTestStruct *)&mem[i * 5];
    ots->b = (unsigned char)i;
    ots->a = (unsigned char)i;
    printf("[%d]: %d / %d\n", i, ots->b, ots->a);
  }
  return ots;
}

// NOTE: Working perfectly fine if all fields are filled with the `char` type.
void print_overlay_struct(OrderingTestStruct *_src_struct)
{
  union
  {
    OrderingTestStruct dest;
    char buf[sizeof *_src_struct];
  } overlay;
  // Abbrev: `overlay.dest = _src_struct;`
  overlay.dest.a = _src_struct->a;
  overlay.dest.b = _src_struct->b;
  printf("Accept field(s) with `char` typed only (because of `buf`): %s\n", overlay.buf);
}

void print_overlay_struct_generic(void *struct_ptr, size_t struct_size)
{
  // NOTE: There is no guarantee of type safety here.
  //    Reason: With `void *` as an argument, the compiler doesn't perform any
  //    type-checking to ensure that the pointer points to the correct type of data.
  //    The function will still accept the pointer, but when you try to access
  //    the data pointed to by the pointer, you will run into problems, because
  //    the data wasn't presenting in the expected format.
  char *field_ptr = (char *)struct_ptr;
  size_t i;
  for (i = 0; i < struct_size; i++)
  {
    if ('\0' == field_ptr[i])
      continue;
    printf("%c", /* field_ptr[i] */ *(field_ptr + i));
  }
  printf("\n");
}

void print_overlay_struct_by_field(void *struct_ptr, size_t offset, char field_type)
{
  switch (field_type)
  {
  case 'c':
    printf("Char type field: %c\n", *((char *)struct_ptr + offset));
    break;

  case 'd':
    printf("Integer type field: %d\n", *((int *)struct_ptr + offset));
    break;

  case 'f':
    printf("Float type field: %f\n", *((float *)struct_ptr + offset));
    break;

  default:
    printf("Invalid data type\n");
    break;
  }
}

// 2. Trick to reduce memory allocations:

typedef struct
{
  unsigned int length;
  unsigned char data[1]; // Version < C99, from C99 := `data[]`.
} MyArrayOfBytes;        // An array container.

MyArrayOfBytes *init_zero(MyArrayOfBytes *array, unsigned int length)
{
  array = malloc((sizeof *array) * sizeof(unsigned char) * /* From: data[1] */ length - 1);
  array->length = length;
  unsigned int i;
  for (i = 0; i < length; i++)
    array->data[i] = 0;
  return array;
}

typedef struct
{
  int a;
  long b;
} FirstPackedStruct;

typedef struct
{
  char x[128];
  short y;
  long long z;
} SecondPackedStruct;

// NOTE: Really dangerous; because these two structs may have different alignment.
//    Need to understand deeply about how alignment work.
void init_both(FirstPackedStruct *first_buf, SecondPackedStruct *second_buf)
{
  first_buf = malloc((sizeof *first_buf) + (sizeof *second_buf)); // Subscript := 0.

  // NOTE: Subscript := 1, an access point to `SecondPackedStruct` was created
  //    and stored adjacent with `FirstPackedStruct`.
  second_buf = (SecondPackedStruct *)&first_buf[1];
}

int main(void)
{
  MyStructInt *mst_intptr = &(struct MyStructInt){
      .header = (struct MyHeader){
          .name = "Integer Form",
          .type = MST_INT,
      },
      .value = 1e3,
  };

  MyStructFloat *mst_floatptr = &(struct MyStructFloat){
      .header = (struct MyHeader){
          .name = "Float Form",
          .type = MST_FLOAT,
      },
      .value = 1e4,
  };

  set_value_from(&mst_intptr->header, ~(1 << 31));
  set_value_from(&mst_floatptr->header, ~(1 << 31));
  printf("Integer: %d | Float: %.3f (%zu)\n", mst_intptr->value, mst_floatptr->value, sizeof(float));

  // NOTE: `***` == `pad` (padding operation).
  // NOTE: Padding `AlignmentTestStruct` to := `a***bbbb`.
  //    That means `b` wants to be stored on the location (index) divisible by 4.
  int cmp_result = sizeof(AlignmentTestStruct) == 8;
  printf("Padding size comparison: %s\n", CMP_ONE(cmp_result));

  // NOTE: `UsingFreedStruct` := `axyzbbbb`.
  // NOTE: Cannot use this `sizeof UsingFreedStruct` syntax because of the lack of verbosity
  //    in the struct name. To be more specific, the anonymous struct must be explicitly declared
  //    (with name) rather than relying on the type alias itself.
  cmp_result = sizeof(UsingFreedStruct) == 8;
  printf("Padding size comparison: %s\n", CMP_ONE(cmp_result)); // The same size.

  // NOTE: Padding `OrderingTestStruct` to := `bbbba***`.
  //    The reason: it's always possible to have an adjacent struct right after the previous one
  //    := `bbbba***bbbba***` (yeah, array is suck).
  cmp_result = sizeof(OrderingTestStruct) == 8;
  printf("Padding size comparison: %s\n", CMP_ONE(cmp_result));

  // NOTE: `sizeof` always give you a value that you can repeat.
  int test_no = 10;
  printf("Test narrow casting: %u\n", (char)test_no);

  OrderingTestStruct test_ots = {
      .a = 97, // ASCII := 'a'.
      .b = 65, // ASCII := 'A'.
  };
  print_overlay_struct(&test_ots);
  print_overlay_struct_generic(&test_ots, sizeof test_ots);
  print_overlay_struct_by_field(&test_ots, offsetof(OrderingTestStruct, b), 'd');
  print_overlay_struct_by_field(&test_ots, offsetof(OrderingTestStruct, a), 'c');

  OrderingTestStruct *ots = packing_mem_manually(10);
  printf("`OrderingTestStruct` := (a: %d) / (b: %d)\n", ots->a, ots->b);

  MyArrayOfBytes *zeros = (void *)0; // Equality with: `{0}`, `NULL`.
  zeros = init_zero(zeros, 10);
  printf("Size comparision: %s\n", CMP_PAIR(10, zeros->length));
  for (unsigned int i = 0; i < zeros->length; i++)
    printf("%d: %d == %d\n", i, *(zeros->data + i), zeros->data[i]);

  FirstPackedStruct first_pack = {
      .a = 73, // ASCII: 'I'.
      .b = 77, // ASCII: 'M'.
  };
  SecondPackedStruct second_pack = {
      .x = "Pcuo",
      .y = 110, // ASCII: 'n'.
      .z = 103, // ASCII: 'g'.
  };
  init_both(&first_pack, &second_pack); // NOTE: Pass by references (reference == pointer).
  print_overlay_struct_generic(&first_pack, sizeof first_pack);
  print_overlay_struct_generic(&second_pack, sizeof second_pack);

  free(ots);
  free(zeros);
  return 0;
}