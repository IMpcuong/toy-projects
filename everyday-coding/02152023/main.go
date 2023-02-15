package main

import "fmt"

// From: https://go-review.googlesource.com/c/go/+/467417/4/src/slices/slices.go#76
// Or: https://cs.opensource.google/go/go/+/master:src/slices/slices.go;l=76

// Insert inserts the values v... into s at index i,
// returning the modified slice.
// The elements at s[i:] are shifted up to make room.
// In the returned slice r, r[i] == v[0],
// and r[i+len(v)] == value originally at r[i].
// Insert panics if i is out of range.
// This function is O(len(s) + len(v)).
func Insert[S ~[]E, E any](s S, i int, v ...E) S {
	tot := len(s) + len(v)
	if tot <= cap(s) {
		s2 := s[:tot]
		copy(s2[i+len(v):], s[i:])
		copy(s2[i:], v)
		return s2
	}
	s2 := make(S, tot)
	copy(s2, s[:i])
	copy(s2[i:], v)
	copy(s2[i+len(v):], s[i:])
	return s2
}

// End from: https://go-review.googlesource.com/c/go/+/467417/4/src/slices/slices.go#96
// Or: https://cs.opensource.google/go/go/+/master:src/slices/slices.go;l=96

func main() {
	origArr := []int{1, 2, 3, 4, 5}
	newArr := []int{0, 0, 0, 0, 0}
	origArr = Insert(origArr, len(newArr), newArr...)
	fmt.Printf("%+v\n", origArr) // Out: `[1 2 3 4 5 0 0 0 0 0]`.

	origArr = Insert(origArr, 0, newArr...)
	fmt.Printf("%+v\n", origArr) // Out: `[0 0 0 0 0 1 2 3 4 5 0 0 0 0 0]`
}
