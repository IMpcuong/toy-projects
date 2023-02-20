package main

import "fmt"

func main() {
	array3D := [2][2][2]int{
		{
			{0, 0},
			{0, 0},
		},
		{
			{0, 0},
			{0, 0},
		},
	}
	fmt.Printf("%#v", array3D)
	/*
		Out:
		```
		[2][2][2]int{[2][2]int{[2]int{0, 0}, [2]int{0, 0}}, [2][2]int{[2]int{0, 0}, [2]int{0, 0}}}
		```
	*/
}
