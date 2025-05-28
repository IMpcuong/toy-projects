; https://cs.lmu.edu/~ray/notes/nasmtutorial/
; https://guihao-liang.github.io/2020/05/24/hw-mac

; ----------------------------------------------------------------------------------------
; Writes "Hello, World" to the console using only system calls. Runs on 64-bit macOS only.
; To assemble and run:
;
;     nasm -fmacho64 hello_x64.asm
;     ld hello_x64.o # --> FAILED
;     ld -v -macos_version_min `sw_vers -productVersion` -static hello_x64.o # --> SUCCESS
;     ./a.out
; ----------------------------------------------------------------------------------------

section .data
message: db "Hello, World", 10 ; note the newline at the end

section .text
global  start
start:
  mov  rax, 0x02000004         ; system call for write
  mov  rdi, 1                  ; file handle 1 is stdout
  mov  rsi, message            ; address of string to output
  mov  rdx, 13                 ; number of bytes
  syscall                      ; invoke operating system to do the write

  mov  rax, 0x02000001         ; system call for exit
  xor  rdi, rdi                ; exit code 0
  syscall                      ; invoke operating system to exit
