package main

import "fmt"

func sum(s []int, c chan int) {
	sum := 0
	for _, v := range s {
		sum += v
	}
	c <- sum
}

func main() {
	s := []int{7, 2, 8, -9, 4, 0}
	l := len(s)

	nChan := make(chan int)
	go sum(s[:l/2], nChan)
	go sum(s[l/2:], nChan)

	out := fmt.Println
	v1, v2 := <-nChan, <-nChan
	out(v1)
	out(v2)
}
