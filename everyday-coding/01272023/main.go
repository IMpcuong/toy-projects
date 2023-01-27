package main

import (
	"fmt"
	"reflect"
	"strings"
)

// Channel example:

func sum(s []int, c chan int) {
	sum := 0
	for _, v := range s {
		sum += v
	}
	c <- sum
}

// Higher order function example:

const test_txt string = "Pirate of Caribean"

func duplicate(s string, times int) string {
	return strings.Repeat(s, times)
}

func fnConsumer(s string, times int, fn func(string, int) string) string {
	return fn(s, times)
}

func fnProvider() func(string) int {
	return func(s string) int {
		return len(s)
	}
}

func execFnWithOrd(in string, fn func(string) int) int {
	return fn(in)
}

func main() {
	// Channel example:
	s := []int{7, 2, 8, -9, 4, 0}
	l := len(s)

	nChan := make(chan int)
	go sum(s[:l/2], nChan)
	go sum(s[l/2:], nChan)

	out := fmt.Println
	v1, v2 := <-nChan, <-nChan
	out(v1)
	out(v2)

	// Higher order function example:
	c := fnConsumer(test_txt, 10, duplicate)
	out(c)

	p := fnProvider()
	out(reflect.TypeOf(p))

	exec := execFnWithOrd(test_txt, p)
	out(exec)
}
