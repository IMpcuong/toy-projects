package main

import (
	"strings"
	"testing"
)

func TestIndexStr(t *testing.T) {
	var testCases = []struct {
		str  string
		find string
		out  int
	}{
		{"", "", 0},
		{"", "a", -1},
		{"foo", "foo", 0},
		{"oofofoofooo", "f", 2},
	}
	for _, test := range testCases {
		actual := strings.Index(test.str, test.find)
		if actual != test.out {
			t.Errorf("Index(%q, %q) = %v; want %v", test.str, test.find, actual, test.out)
		}
	}
}
