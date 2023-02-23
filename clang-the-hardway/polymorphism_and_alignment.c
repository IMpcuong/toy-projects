#include <stdio.h>

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
  unsigned int b;  // 4 bytes.
  unsigned char a; // 1 byte.
} OrderingTestStruct;

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
  printf("True: %d\n", sizeof(AlignmentTestStruct) == 8);

  // NOTE: `UsingFreedStruct` := `axyzbbbb`.
  printf("True: %d\n", sizeof(UsingFreedStruct) == 8); // The same size.

  // NOTE: Padding `OrderingTestStruct` to := `bbbba***`.
  //    The reason: it's always possible to have an adjacent struct right after the previous one
  //    := `bbbba***bbbba***` (yeah, array is suck).
  printf("True: %d\n", sizeof(OrderingTestStruct) == 8);

  // NOTE: `sizeof` always give you a value that you can repeat
}