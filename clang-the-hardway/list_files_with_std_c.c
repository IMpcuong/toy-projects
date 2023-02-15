#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

// NOTE: `CRT` := `C Runtime library`.

// NOTE: Explicit function declaration.
extern int _cdecl atoi(const char *_String);
extern size_t __cdecl strlen(const char *_String);

// Cmd: `gcc -Wall -D_WINDOWS -D_MINGW list_files_with_std_c.c -o lfs`.

int main()
{
  const wchar_t *var_name = L"PATH";
  wchar_t *var_val = _wgetenv(var_name);
  printf("%ls\n", var_val);

  char *next_token = NULL;
  char *first_path = strtok_s(getenv("PATH"), ";", &next_token);
  printf("%s\n", first_path);

  char *cur_dir = _getcwd(NULL, 0);
  printf("Current directory: %s (len = %zu)\n", cur_dir, strlen(cur_dir));

  DIR *dir = opendir(cur_dir);
  if (dir == NULL)
  {
    perror("Cannot open out current directory!");
    return 1;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL)
  {
#ifndef _DIRENT_HAVE_D_TYPE
    printf("Filename %s (len = %d)\n", entry->d_name, entry->d_namlen);
#else
    // NOTE: Only the hierarchy pf Linux/BSD Operating Systems have the `d_type` attribute.
    printf("Filename %s (len = %d, type = %zu)\n", entry->d_name, entry->d_namlen, entry->d_type);
#endif
  }

  closedir(dir);
  return 0;
}