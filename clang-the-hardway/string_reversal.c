#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// NOTE: Duplicated with the implementation in `main.c`.
char *convert_to_binary(size_t _src_num)
{
  size_t size_t_bitlen;
#if defined(__x86_64__)
  size_t_bitlen = (sizeof _src_num) / 2 * 8; // 8 (size_t) / 2 * 8 (char) = 32.
#elif defined(__i386__)
  size_t_bitlen = (sizeof _src_num) * 8; // 4 (size_t) * 8 (char) = 32.
#endif
  size_t binary_str_bufsize = size_t_bitlen + 1;

  char *binary_str;
  // NOTE: Allocate a buffer to hold the binary string.
  //    Expression `+ 1` := '\0' terminated character.
  binary_str = malloc(/* optional := char ~ 1 byte */ sizeof(*binary_str) * binary_str_bufsize + 1);
  if (binary_str == NULL)
    fprintf(stderr, "Errno = %d\n", ENOMEM);
  binary_str[0] = '\0';

  // NOTE: Extract each bit of the number and add it to the binary string.
  int i;
  for (/* 31 -> 0 */ i = (int)size_t_bitlen - 1; i >= 0; i--)
  {
    if (_src_num & (1 << i))
      strcat_s(binary_str, binary_str_bufsize, "1");
    else
      strcat_s(binary_str, binary_str_bufsize, "0");
  }
  return binary_str;
}

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
  char *end = src + (strlen_custom(src) - 1); // NOTE: Offset started from subscript 0 --> `last_offset = length - 1`.
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

// FIXME: Reverse with an incorrect order.
uint32_t reverse_bits_orderV1(uint32_t orig)
{
  uint32_t reverse = 0;
  // Traversing bits from the right.
  size_t i;
  for (i = 0; i < (sizeof orig) * 8; i++)
  {
    reverse <<= 1;
    if (orig & 1)
      reverse |= 1;
    orig >>= 1;
  }
  return reverse;
}

uint32_t reverse_bits_orderV2(uint32_t orig)
{
  uint32_t reverse = 0;
  // Traversing bits from the right.
  while (orig > 0)
  {
    reverse <<= 1;
    if (orig & 1)
      reverse ^= 1;
    orig >>= 1;
  }
  return reverse;
}

uint32_t f_randi(uint32_t index)
{
  index = (index << 13) ^ index;
  return ((index * (index * index * 15731 + 789221) + 1376312589) & 0x7fffffff);
}

int main(void)
{
  char *test_length = "IMpcuong can do it!!!";
  printf("Test custom string length calculation: %d\n", strlen(test_length) == strlen_custom(test_length));

  char test_string0[128] = "IMpcuong";
  reverse_str_method0(test_string0);
  printf("Reversal method 0: %s\n", test_string0);

  char test_string1[128] = "IMpcuong";
  reverse_str_method1(test_string1);
  printf("Reversal method 1: %s\n", test_string1);

  char test_string2[128] = "IMpcuong";
  reverse_str_method2(test_string2, (int)strlen_custom(test_string2));
  printf("Reversal method 2: %s\n", test_string2);

  uint32_t rand = f_randi(0xFFFF);
  printf("Randomize algorithm output: %d\n", rand);

  unsigned int zero = 0;
  printf("%d: %s\n", zero << 1, convert_to_binary((size_t)(zero << 1)));

  uint32_t orig = 0b11110000; // (0x80 == 128) := 8 bits.
  printf("%d: %s\n", orig, convert_to_binary((size_t)orig));
  uint32_t reverse1 = reverse_bits_orderV1(orig);
  uint32_t reverse2 = reverse_bits_orderV2(orig);
  printf("%d / %d: %s / %s\n", reverse1, reverse2,
         convert_to_binary((size_t)reverse1),
         convert_to_binary((size_t)reverse2));

  return 0;
}