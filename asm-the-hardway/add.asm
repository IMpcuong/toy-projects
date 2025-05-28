; Sections:
;  + .data: read-write
;  + .rodata: readonly
;  + .bss: read-write + zero-init
;  + .text: readonly + program code

; @Doc: https://forum.nasm.us/index.php?topic=1932.0

default rel

section .data
var1: dq 100 ; word = 2 bytes
var2: dq 500

section .text
global  start
start:
  mov  rax, qword [var1]
  mov  rbx, qword [var2]
  add  rax, rbx
  mov  rdi, rax
  mov  rax, 0x2000001
  ; rax := 600
  ; shel exit-codes := [i | 0 <= i <= 255]
  ; echo $? := 600 % 256 = 88
  syscall
