package main

import (
	"strings"
)

func backspaceCompare(s string, t string) bool {
	if !strings.Contains(s, "#") && !strings.Contains(t, "#") {
		return s == t
	}
	var stack []rune
	for _, r := range s {
		if r == '#' {
			if len(stack) > 0 {
				stack = stack[:len(stack)-1]
			}
		} else {
			stack = append(stack, r)
		}
	}
	s = string(stack)
	stack = []rune{}
	for _, r := range t {
		if r == '#' {
			if len(stack) > 0 {
				stack = stack[:len(stack)-1]
			}
		} else {
			stack = append(stack, r)
		}
	}
	t = string(stack)
	return s == t
}

func main() {
	s := "a#b#"
	t := "cd##"
	println(backspaceCompare(s, t))

	s1 := "a#b"
	t1 := "a"
	println(backspaceCompare(s1, t1))
}
