package main

import (
	"fmt"
)

func romanToInt(s string) int {
	romanMap := map[uint8]int{
		'I': 1,
		'V': 5,
		'X': 10,
		'L': 50,
		'C': 100,
		'D': 500,
		'M': 1000,
	}
	var sum, curDigit, lastDigit int
	for i := len(s) - 1; i >= 0; i-- {
		curDigit = romanMap[s[i]]
		if curDigit < lastDigit {
			sum -= curDigit
		} else {
			sum += curDigit
		}
		lastDigit = curDigit
	}
	return sum
}

func main() {
	s := "MCMXCIV"
	ans := romanToInt(s)
	fmt.Println(ans)
}
