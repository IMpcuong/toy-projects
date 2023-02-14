#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

int main(void)
{
  printf("Example 1: %s\t%s\n", __FILE__, __FILENAME__); // NOTE: Both macros have the same result in this context.

  WIN32_FIND_DATA file_data_attr;
  HANDLE file_handler;
  TCHAR file_path[MAX_PATH]; // NOTE: constant `MAX_PATH` := 260.
  _tcscpy_s(file_path, MAX_PATH, _T(".."));

  file_handler = FindFirstFile(file_path, &file_data_attr);
  if (file_handler == INVALID_HANDLE_VALUE)
  {
    _tprintf("Unable to open directory %d\n", GetLastError());
    return 1;
  }

  do
  {
    if (!(file_data_attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
      _tprintf(_T("%s\n"), file_data_attr.cFileName);
    }
  } while (FindNextFile(file_handler, &file_data_attr) != 0);
  FindClose(file_handler);
  return 0;
}
