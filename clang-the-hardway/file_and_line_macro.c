#ifdef _WIN32
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <sysinfoapi.h>
#include <tchar.h>
#include <Windows.h>

#define DIV 1048576
#define WIDTH 7

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif

#ifdef linux
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

void mem_status_report()
{
  // From: https://stackoverflow.com/questions/8666378/detect-windows-or-linux-in-c-c
#ifdef _WIN32
  MEMORYSTATUSEX mem_status;
  mem_status.dwLength = sizeof(mem_status);
  GlobalMemoryStatusEx(&mem_status);

  _tprintf(/* Unicode */ TEXT("Example 2: There is %*ld %% (escaped/meta character) of memory in use.\n"),
           WIDTH, mem_status.dwMemoryLoad);
#endif
}

void search_file_in_dir(WIN32_FIND_DATAW file_info, LPCWSTR dir_path)
{
  // `HANDLE`: a void pointer used to represent a reference to a system resource or object.
  // List of system resources := [file, thread, process, device, etc ...].
  //
  // `HANDLE` is a way to refer to these system resources in generic way, without needing to know the specific details of the resource.
  // It's worth noting that different types of system resources may have different functions for creating, managing, and using `HANDLEs`.
  HANDLE h_find_file = FindFirstFileW(dir_path, &file_info);
  printf("DEBUG: %ls\t%p\n", (wchar_t *)(h_find_file), h_find_file);
  if (h_find_file == INVALID_HANDLE_VALUE)
  {
    _tprintf(TEXT("ERROR: Unable to open directory %ld\n"), GetLastError());
    return;
  }

  printf("DEBUG: %ld\n", file_info.dwFileAttributes);
  do
  {
    DWORD file_info_dir_attr = file_info.dwFileAttributes;
    if ((file_info_dir_attr & FILE_ATTRIBUTE_DIRECTORY) == 0)
    {
      _tprintf(TEXT("Example 3.1 (Filename): %ls\n"), file_info.cFileName);
    }
    else if (file_info_dir_attr | FILE_ATTRIBUTE_DIRECTORY)
    {
      _tprintf(TEXT("Example 3.2 (Dirname): %ls\n"), file_info.cFileName);
    }
  } while (FindNextFileW(h_find_file, &file_info) != 0);
  FindClose(h_find_file);
}

// Cmd: `gcc -Wall file_and_line_macro.c -o fal`.

int main(void)
{
  printf("Example 1: file_name := [%s, %s]\n", __FILE__, __FILENAME__); // NOTE: Both macros have the same result in this context.

  mem_status_report();

  WIN32_FIND_DATAW file_attr;
  PWCHAR dir_name = L".\\*";
  WCHAR paths[MAX_PATH];               // NOTE: constant `MAX_PATH` := 260.
  wcscpy_s(paths, MAX_PATH, dir_name); // Preserve the order of the source UNICODE string/text.
  search_file_in_dir(file_attr, paths);

  return 0;
}
