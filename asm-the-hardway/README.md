* How to compile ASM on MacOS:

  ```bash
  nasm -fmacho64 add_print.asm
  ld -macos_version_min `sw_vers -productVersion` -static add_print.o
  ./a.out
  ```
