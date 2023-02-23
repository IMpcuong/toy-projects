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
}