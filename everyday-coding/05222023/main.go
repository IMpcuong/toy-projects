package main

import (
	"fmt"
	"regexp"
	"strings"
)

func main() {
	obtainPatternFnOnce := func(inputStr string, errMsg string) (string, error) {
		var pattern string
		regexSpaces := regexp.MustCompile(`\s+`)
		if spaceChars := string(regexSpaces.Find([]byte(inputStr))); len(spaceChars) > 0 {
			if chunks := strings.Split(inputStr, spaceChars); len(chunks) > 1 {
				pattern = strings.Split(inputStr, spaceChars)[1]
			} else {
				return strings.Clone(""), fmt.Errorf(errMsg)
			}
		}
		return pattern, nil
	}

	txt1 := "/search         "
	txt2 := "/search     n"
	txt3 := ""
	txt4 := "      "

	p, _ := obtainPatternFnOnce(txt1, "err1")
	fmt.Println(p, len(p))
	p, _ = obtainPatternFnOnce(txt2, "err2")
	fmt.Println(p, len(p))
	p, _ = obtainPatternFnOnce(txt3, "err2")
	fmt.Println(p, len(p))
	p, _ = obtainPatternFnOnce(txt4, "err2")
	fmt.Println(p, len(p))
}
