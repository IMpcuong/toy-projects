package main

import "fmt"

func main() {
	fmt.Println("Hello, 世界")
	//lint:ignore S1021 -> Reason: intended to provide 2 yield methods.
	var t struct {
		i int
		s string
	}

	t = struct {
		i int
		s string
	}{1, "DUDE"}
	fmt.Printf("%+v\n", t)

	t1 := struct {
		name   string
		gender string
	}{"Nene", "Female"}
	fmt.Printf("%#v\n", t1)
}
