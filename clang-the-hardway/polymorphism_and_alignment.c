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

// 1: Alignment (memory) makes things more complicated:

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

// NOTE: Working perfectly fine if all fields have the `char` type.
void overlay_struct_stats(OrderingTestStruct *_src_struct)
{
  union
  {
    OrderingTestStruct dest;
    char buf[sizeof *_src_struct];
  } overlay;
  // Abbrev: `overlay.dest = _src_struct;`
  overlay.dest.a = _src_struct->a;
  overlay.dest.b = _src_struct->b;
  printf("%s\n", overlay.buf);
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
      .a = 100,
      .b = 65 // ASCII := 'A',
  };
  overlay_struct_stats(&test_ots);

  OrderingTestStruct *ots = packing_mem_manually(10);
  printf("`OrderingTestStruct` := (a: %d) / (b: %d)\n", ots->a, ots->b);

  free(ots);
  return 0;
}