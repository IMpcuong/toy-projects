package main

import (
	"fmt"
	"math"
)

func mergeArrays(a, b []int) int {
	var res int
	boundA, boundB := len(a), len(b)
	lenNewNumber := boundA + boundB
	mergedMap := make(map[int]int, lenNewNumber)
	for i := range a {
		mergedMap[boundA-i-1] = a[i]
	}
	for i := range b {
		mergedMap[lenNewNumber-i-1] = b[i]
	}
	if mergedMap[boundA-1] > mergedMap[lenNewNumber-1] {
		mediateVal := mergedMap[boundA-1]
		mergedMap[boundA-1] = mergedMap[lenNewNumber-1]
		mergedMap[lenNewNumber-1] = mediateVal
	}
	for k, v := range mergedMap {
		res += v * int(math.Pow10(k))
	}
	fmt.Println(mergedMap)
	return res
}

func main() {
	arr1 := []int{1, 4, 2, 8, 7, 6}
	arr2 := []int{9, 3, 5, 0}
	// maxButSameOrder := 987643510
	// reality := 9350142876

	fmt.Println(arr1)
	fmt.Println(arr2)

	res := mergeArrays(arr1, arr2)
	fmt.Println(res)
}
