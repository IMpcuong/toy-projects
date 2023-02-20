// NOTE: Having the same semantic with `#ifndef ... #define` block statement.
// #pragma once

#ifndef MAIN_H_
#define MAIN_H_

// NOTE: In C, it's not possible to assign a string value to an enumerated type directly.
typedef enum MyEnumType
{
  MET_NW /* 0: Networking */,
  MET_ALGO /* 1: Algorithms */,
  MET_PRJ /* 2: Projects */,
} MyEnumType;

extern int double_input_as_ref(int x);
extern void double_input_as_orig(int *x);
extern char *get_offset_from_type(void);

// https://gcc.gnu.org/onlinedocs/gcc/Inline.html
extern inline __attribute__((always_inline)) char *karatsuba_algo(size_t lfactor, size_t rfactor);

#endif
