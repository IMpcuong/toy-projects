#include <stdio.h>
#include <stdint.h>
#include <string.h>

char *strintefere(int8_t rand_num, char *base_char, char *src_str)
{
  size_t len_srcstr_ = strlen(src_str);
  if ((size_t)rand_num < len_srcstr_)
    rand_num += len_srcstr_;
  if (strnstr(src_str, base_char, len_srcstr_) != NULL)
  {
    const size_t buffer_len = 16;
    char buffer_conversion[buffer_len];
    int actual_len_ = snprintf(buffer_conversion, buffer_len, "%d", rand_num);
    // size_t i = 0; // NOTE: Unnecessary version of string concatenation.
    if (actual_len_ >= 0 && (size_t)actual_len_ < buffer_len)
    {
      printf("Converted number: %s\n", buffer_conversion);
      // NOTE: Unnecessary version of string concatenation.
      // for (; buffer_conversion[i] != '\0'; i++)
      //   src_str[len_srcstr_ + i] = buffer_conversion[i];
      strlcat(buffer_conversion, src_str, len_srcstr_ + buffer_len);
    }
    // src_str[len_srcstr_ + i] = '\0';
    return src_str;
  }
  return base_char;
}

int main(void)
{
  char *test_str_0 = "test string";
  printf("%zu\n", strlen(test_str_0));

  char *test_str_1 = "test string manipulation with matching pattern";
  char *test_str_2 = "manipulation";
  printf("%s\n", strintefere(10, test_str_2, test_str_1));
  return 0;
}
