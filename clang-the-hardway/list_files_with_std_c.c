#define _CRT_SECURE_NO_WARNINGS

#include <dirent.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// NOTE: `CRT` := `C Runtime library`.

// NOTE: Explicit function declaration.
extern int _cdecl atoi(const char *_String);
extern size_t __cdecl strlen(const char *_String);

// Cmd: `gcc -Wall -D_WINDOWS -D_MINGW list_files_with_std_c.c -o lfs`.

size_t str_count_num_delim(char *_src_str, const char *delim)
{
  size_t count = 0;
  for (int i = 0; i < strlen(_src_str); i++)
    if (_src_str[i] == *delim)
      count++;
  return count;
}

char ***str_separate_with_delim(char *_src_str, const char *delim, char **next_pos)
{
  size_t size = str_count_num_delim(_src_str, delim) + 1;
  char ***substr_with_idx = (char ***)malloc(size * sizeof(char **));

  char *token = strtok_s(_src_str, delim, next_pos);
  while (NULL != token)
  {
    for (size_t i = 0; i < size; i++)
    {
      size_t substr_len = strlen(token) + size;
      substr_with_idx[i] = (char **)malloc(substr_len * sizeof(char *));

      substr_with_idx[i][0] = (char *)malloc(sizeof i);
      snprintf(substr_with_idx[i][0], sizeof substr_with_idx[i][0], "%zu", i);

      substr_with_idx[i][1] = token;
      token = strtok_s(NULL, delim, next_pos);
    }
  }

  return substr_with_idx;
}

char *str_narrow_cast(wchar_t *_src_str)
{
  setlocale(LC_ALL, "");
  char *narrow_str = NULL; // Allocate on heap-mem later.

  // NOTE: `wcstombs` := `wide-charater string to multi-bytes string`.
  //
  // `wcstombs` used to determine the length of the narrow string
  // that will be produced from `src` string.
  size_t narrow_str_len = wcstombs(NULL, _src_str, 0);
  if (narrow_str_len != -1)
  {
    narrow_str = (char *)malloc(narrow_str_len + 1);
    wcstombs(narrow_str, _src_str, narrow_str_len + 1);
  }
  if (narrow_str == NULL)
    printf("Could not narrow the source string: %p", _src_str);
  return narrow_str;
}

DIR *curdir_open()
{
  char *fullpath = _getcwd(NULL, 0);
  // NOTE: Implementation using `dirent.h` from GNU C standard libraries.
  DIR *dir = opendir(fullpath);
  printf("Current directory: %s (len = %zu)\n", fullpath, strlen(fullpath));
  if (dir == NULL)
    perror("Cannot open out current directory!");
  return dir;
}

void curdir_list_files(DIR *current)
{
  // NOTE: Implementation using `dirent.h` from GNU C standard libraries.
  //
  // NOTE: By default, C does not include struct types in the global namespace.
  //  In other words, if you define a struct within a function, you cannot refer to it by name
  //  outside of that function without using the `struct` keyword as an identifier.
  struct dirent *entry = (struct dirent *)malloc(sizeof(struct dirent));
  while ((entry = readdir(current)) != NULL)
  {
#ifndef _DIRENT_HAVE_D_TYPE
    printf("Filename %s (len = %d)\n", entry->d_name, entry->d_namlen);
#else
    // NOTE: Only the direct hierarchy of Linux/BSD Operating Systems have the `d_type` attribute.
    printf("Filename %s (len = %d, type = %zu)\n", entry->d_name, entry->d_namlen, entry->d_type);
#endif
  }
  free(entry);
}

int main()
{
  // Using wide-character strings to store the `%PATH%` env-var on Windows.
  const wchar_t *env_var_name = L"PATH";
  wchar_t *env_var_ws = _wgetenv(env_var_name);
  printf("Length of `%%PATH%%` env-var: %lld\n", (intptr_t)env_var_ws);
  printf("\n");

  // `%PATH%` separator with a given delimiter into multiple sub-strings.
  char *narrow_env_var1 = str_narrow_cast(env_var_ws);
  const char *delim = ";";

  // Approach 1:
  char *next_pos1 = NULL; // `context`: Used to store position information between calls to the function.
  char *path1 = strtok_s(narrow_env_var1, delim, &next_pos1);
  unsigned int count = 0;

  printf("Approach 1:\n");
  while (NULL != path1)
  {
    ++count;
    printf("Path [%d]: %s\n", count, path1);
    path1 = strtok_s(NULL, delim, &next_pos1);
  }
  printf("\n");

  // Approach 2:
  char *narrow_env_var2 = str_narrow_cast(env_var_ws);
  // strcpy(narrow_env_var2, narrow_env_var1); // FIXME: Only copy the first path.
  size_t size = str_count_num_delim(narrow_env_var2, delim) + 1;
  char *next_pos2 = NULL;
  char ***path2 = str_separate_with_delim(narrow_env_var2, delim, &next_pos2);

  printf("Approach 2:\n");
  for (size_t i = 0; i < size; i++)
  {
    for (size_t j = 0; j < 2; j++)
    {
      printf("Path [%zu]: %s\n", i, path2[i][j]);
    }
    free(path2[i]);
  }
  printf("\n");

  // Open and list files in the current directory.
  DIR *current_dir = curdir_open();
  curdir_list_files(current_dir);
  closedir(current_dir);

  free(narrow_env_var1);
  free(narrow_env_var2);
  free(path2);
  return 0;
}
