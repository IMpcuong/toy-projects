package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

// Resource:
//	+ https://github.com/golang/go/wiki/CommonMistakes
//	+ https://github.com/uber-go/guide/blob/master/style.md
//	+ https://github.com/golang/go/wiki/CodeReviewComments

// Learning path:
// 1. https://www.golangtraining.in/lessons/contents.html
// 2. https://github.com/uber-go/guide/blob/master/style.md
// 2.1. https://go.dev/doc/effective_go
// 2.2. https://go.dev/ref/spec

type SomeStruct struct {
	id   int
	data string
}

func NewStruct(id int, data string) *SomeStruct {
	return &SomeStruct{id, data}
}

func (s SomeStruct) Read() (int, string) {
	return s.id, s.data
}

func (s *SomeStruct) Write(str string) {
	s.data = str
}

func main() {
	out := make([]*int, 10)
	type_of_out := reflect.TypeOf(out).Elem()
	fmt.Println(type_of_out)

	for i := 0; i < 3; i++ {
		tmp_var := i
		out = append(out, &tmp_var)
	}
	for idx, addr := range out {
		if addr != nil {
			fmt.Println(idx, addr, *addr)
		}
	}

	var out2 [][2]int
	from := [][2]int{{1, 2}, {2, 3}, {3, 4}}
	out2 = append(out2, from...)
	fmt.Println(out2)

	for _, a := range from {
		sliceHeader := (*reflect.SliceHeader)(unsafe.Pointer(&a))
		data := &sliceHeader.Data
		arr_addr := (*[2]int)(unsafe.Pointer(data))
		out2 = append(out2, *arr_addr)
		out2 = append(out2, a)
	}
	fmt.Println("Values:", out2)

	for _, v := range out2 {
		go func(val interface{}) {
			fmt.Println(v) // WARN: `v` captured by the scope of closure/lambda function literal.
		}(v)
	}

	for i := range out2 {
		copy := out2[i]
		go func(val interface{}) {
			// NOTE: Goroutines are represented for the concurrency but not for parallelization.
			// 	The sequence of all routines is determined/evaluated by the speed at
			// 	which they are executed.
			fmt.Println(copy)
		}(copy)
	}

	for i, v := range out2 {
		func() {
			fmt.Println(i, v) // NOTE: Without executing closure as goroutine, the code run as expected.
		}()
	}

	newS := NewStruct(2, "Hey")
	valStruct := map[int]*SomeStruct{1: {1, "Dude"}, 2: newS}
	valStruct[1].Write("Neh!!!")

	// NOTE: As with method calls, a reference to a non-interface method with a value receiver
	//	using an adressable value will automatically take the address of that value.
	//	Un-addresable values include := [values in a map; return values from function/method].
	//	Exp: `&m["key"], &afunc(), &t.method()` are all errors.
	//
	//	Document:
	//		+ https://go.dev/ref/spec#Method_values
	// 		+ https://www.golangtraining.in/lessons/pointers/addressable-values.html
	//		+ https://go.dev/doc/effective_go#pointers_vs_values

	indirective_func := (*valStruct[1]).Write // Equals: `val[1].Write` --> `SomeStruct` is an addressable type.
	indirective_func("Dude again")

	// NOTE: Methods with value receivers can be called on pointers as well as values.
	//	Methods with pointer receivers can only be called on pointers or addressable values.
	fmt.Println(valStruct[1].Read()) // Equivalent (semantically): `(*SomeStruct).Read()`.
	fmt.Println(valStruct[2].Read())
	fmt.Printf("%#v\n", valStruct)

	// NOTE: Distinctive between `var` and `:=` value assignment begins with 2 or more variables.
	var int1, int2 int = 1, 2 // Mutual variables are on the same line, must be of the same type.
	fmt.Println(int1, int2)

	diff1, diff2 := 1, "1" // Mutual types are accepted.
	fmt.Println(diff1, diff2)
}
