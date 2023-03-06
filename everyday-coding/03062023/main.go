package main

import "fmt"

func main() {
	i := 10
	fmt.Println(-i)                                          // -10.
	fmt.Println(^i)                                          // -11.
	fmt.Println(-i == ^i /* `Negation operator (~)` in C */) // False.
}
