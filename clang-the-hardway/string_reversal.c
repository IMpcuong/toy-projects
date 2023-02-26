#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Idea from: https://github.com/torvalds/linux/blob/master/arch/arm/boot/compressed/string.c
size_t strlen_custom(char *src)
{
  const char *copy = src;
  while (*copy != '\0')
    copy++;
  return (size_t)(copy - src); // `length = last_addr - first_addr (`char` := 1 byte)`.
}

void reverse_str_method0(char *src)
{
  int src_len = (int)strlen_custom(src);
  int i;
  for (i = 0; i < src_len / 2; i++)
  {
    char tmp = src[i];
    src[i] = src[src_len - 1 - i];
    src[src_len - 1 - i] = tmp;
  }
}

void reverse_str_method1(char *src)
{
  char *end = src + (strlen_custom(src) - 1); // NOTE: Offset started from subscript 0 -> `last_offset = length - 1`.
  while (src < end)
  {
    // NOTE: `char *tmp = src;` --> `(*src == *end) := True`.
    //    Reason: An address is remain consistent.
    char tmp = *src;
    *src = *end;
    *end = tmp;
    src++;
    end--;
  }
}

void reverse_str_method2(char *src, int length)
{
  if (length <= 1)
    return;

  char tmp = src[0];
  src[0] = src[length - 1];
  src[length - 1] = tmp;
  reverse_str_method2(src + 1, length - 2);
}

int main(void)
{
  char *test_length = "IMpcuong can do it!!!";
  printf("Test custom string length calculation: %d\n", strlen(test_length) == strlen_custom(test_length));

  char test_string0[128] = "IMpcuong";
  reverse_str_method0(test_string0);
  printf("%s\n", test_string0);

  char test_string1[128] = "IMpcuong";
  reverse_str_method1(test_string1);
  printf("%s\n", test_string1);

  char test_string2[128] = "IMpcuong";
  reverse_str_method2(test_string2, (int)strlen_custom(test_string2));
  printf("%s\n", test_string2);

  return 0;
}