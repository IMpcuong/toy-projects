; llvm-objdump -d ./a.out

; 63                                             15 8 7             0
; +-------------------------------------------------+--+--------------+
; |                   (unused)                      |dh|     dl       | <-- 8-bit registers
; +-------------------------------------------------+--+------------- +
; |                   (unused)                      |       dx        | <-- 16-bit register
; +-------------------------------------------------+-----------------+
; |                             edx                                   | <-- 32-bit register
; +-------------------------------------------------------------------+
; |                                   rdx                             | <-- 64-bit register
; +-------------------------------------------------------------------+

default rel

section .data
var1: dq 100  ; word = 2 bytes
var2: dq 500
buff: resb 20 ; resb = reserves bytes

section .text
global  start
start:
  mov  rax, qword [var1]
  mov  rbx, qword [var2]
  add  rax, rbx
  shr  rax, 2
  mov  rdi, (buff + 19) ; rdi := point to last byte of our buffer (idx-19 := right->left string)
                        ;        (least significant digit first)
  mov  byte [rdi], 0x0A ; adds a newline char at the end of the output
  dec  rdi              ; moves rdi-ptr back one position to start placing digits

  .iota_loop:
    xor  rdx, rdx   ; clears rdx, div-op uses rdx:rda as the 128-bit dividend; clearing rdx
                    ; ensures we're just dividing rax
    mov  rbx, 10    ; divisor := 10
    div  rbx        ; performs rax / rbx -> quotient := rax && remainder := rdx

    add  dl, '0'    ; remainder := [0-9]; adds '0' converts a number to its ASCII char;
                    ; uses dl because the remainder is byte
                    ; dl := lower 8 bits (1 byte) of rdx; x86-64
                    ;       -> registers are hierarchical
                    ;       -> can be accessed in smaller chunks
    mov  [rdi], dl  ; stores ASCII digit into the buffer at the current rdi position
    dec  rdi        ; moves rdi-ptr back to the next position for the next digit

    cmp  rax, 0     ; check if the quotient == 0
    jnz  .iota_loop ; if rax != 0 -> jump back to the loop

  mov  rsi, rdi         ; rdi points to the first digit of the number
                        ; -> moves to rsi because sys_write expects string pointer in rsi instead
  mov  rdx, (buff + 20) ; rdx is set to the absolute end of the buffer (the byte after newline)
  sub  rdx, rsi         ; sub := rdx - rsi := end-ptr - start-ptr = len(string) (includes newline)
                        ; len(string) goes into rdx for sys_write

  mov  rdi, 1          ; fd := 1 := stdout
  mov  rax, 0x02000004 ; macOS x86-64 call number for sys_write
  syscall              ; executes the systemcall

  xor  rdi, rdi        ; exit-code := 1 | 1 = 0
  mov  rax, 0x02000001 ; macOS x86-64 call number for sys_exit
  syscall              ; executes the systemcall
