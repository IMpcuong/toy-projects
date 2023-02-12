package main

/*
#include <stdio.h>
#include <Windows.h>

int add_two(int a, int b)
{
	return a + b;
}

static void print_sth(char *str)
{
	printf("%s\n", str);
}
*/
import "C"

import (
	"fmt"
	"unsafe"
)

// Cmd: `go list -e -json -compiled -x main.go`

func main() {
	res0 := C.add_two(C.int(0), C.int(1))
	fmt.Printf("Go FFI to C function with return value: %d\n", res0)

	// Load the .dll (Dynamic-link library) file.
	dllFile := "kernel32.dll"
	lib := C.LoadLibrary((*C.char)(unsafe.Pointer(&dllFile)))
	if lib == nil {
		fmt.Println("Failed to load kernel32.dll!")
	}
	defer C.FreeLibrary(lib)

	// Get the address of the `addTwo` function.
	cFuncName := "addTwo"
	addTwo := C.GetProcAddress(lib, (*C.char)(unsafe.Pointer(&cFuncName)))
	if addTwo == nil {
		fmt.Println("Failed to get `addTwo` function's address!")
	}

	// Convert the `add_two` function into Go function.
	// goAddTwo := *(*C.add_two)(addTwo)
	// res1 := goAddTwo(2, 2)

	res1 := C.add_two(C.int(10), C.int(100))
	fmt.Printf("Go FFI to C function with return value: %d\n", res1)

	str := C.CString("Some test string")
	C.print_sth(str)
	C.free(unsafe.Pointer(str))

	// NOTE: Casting to function pointer.
	f1 := func(s string) {
		fmt.Println(s)
	}
	f2 := func(i int) int {
		return i + 1
	}
	pointers := []unsafe.Pointer{
		unsafe.Pointer(&f1),
		unsafe.Pointer(&f2),
	}
	f3 := (*func(int) bool)(pointers[1])
	fmt.Println((*f3)(1))
}
