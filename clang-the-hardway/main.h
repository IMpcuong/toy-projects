// NOTE: Having the same semantic with `#ifndef ... #define` block statement.
// #pragma once

#ifndef MAIN_H_
#define MAIN_H_

extern int double_input_as_ref(int x);
extern void double_input_as_orig(int *x);

#endif
