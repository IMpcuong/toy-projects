package main

import (
	"fmt"
)

func canConstruct(ransomNote string, magazine string) bool {
	charFreqMap := func(s string) map[rune]int {
		rMap := make(map[rune]int, 26)
		for _, r := range s {
			rMap[r]++
		}
		return rMap
	}

	noteMap := charFreqMap(ransomNote)
	magMap := charFreqMap(magazine)
	for _, r := range ransomNote {
		if noteMap[r] > magMap[r] {
			return false
		}
	}
	return true
}

func main() {
	rNote := "aab"
	mag := "baa"

	rNote_1 := "abab"
	// mag_1 := "abab"
	mag_1 := "baba"

	rNote_2 := "ab"
	mag_2 := "bbab"

	rNote_3 := "a"
	mag_3 := "b"

	rNote_4 := "aa"
	mag_4 := "aab"

	rNote_5 := "bjaajgea"
	mag_5 := "affhiiicabhbdchbidghccijjbfjfhjeddgggbajhidhjchiedhdibgeaecffbbbefiabjdhggihccec"

	fmt.Println(canConstruct(rNote, mag))
	fmt.Println(canConstruct(rNote_1, mag_1))
	fmt.Println(canConstruct(rNote_2, mag_2))
	fmt.Println(canConstruct(rNote_3, mag_3))
	fmt.Println(canConstruct(rNote_4, mag_4))
	fmt.Println(canConstruct(rNote_5, mag_5))
}
