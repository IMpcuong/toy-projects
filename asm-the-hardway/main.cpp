#include <iostream>

int main()
{
  int v1 = 12;
  int v2 = 8;
  int res = 0;

  asm volatile (
      "mov %1, %%eax\n\t"
      "mov %2, %%ebx\n\t"
      "add %%ebx, %%eax\n\t"
      "mov %%eax, %0\n\t"
      : "=r" (res)         // Output operand, any register
      : "r" (v1), "r" (v2) // Input operand, any register
      : "%eax", "%ebx"     // Clobbered registers - tells compiler we modify these
  );

  std::cout << res << "\n";

  return 0;
}
