package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

// Resource: https://github.com/golang/go/wiki/CommonMistakes

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
}
