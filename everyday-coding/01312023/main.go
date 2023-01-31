package main

import "fmt"

type cons struct {
	ask string
	cdr interface{}
}

func (c cons) String() string {
	if c.cdr == nil || c.cdr == (cons{}) {
		return c.ask
	}
	ret := fmt.Sprintf("%v %v", c.ask, c.cdr)

	// ret := fmt.Sprintf("%v %v", c.cdr, c.ask) // -> Return the string-array as its ordinary order.
	// NOTE: With the nested struct (by implementation) as `cons`, the order of fetching `c.ask` field
	//	was followed by the FIFO rule (if we're using the commented `ret` variable instead).
	return ret
}

func main() {
	m := map[cons]string{}
	c := cons{}
	for _, s := range []string{"life?", "with my", "I doing", "What am"} {
		fmt.Println(s)
		c = cons{s, c} // LIFO order.
		fmt.Printf("%#v\n", c)
	}
	m[c] = "No idea."
	fmt.Println(c, m[c])

	type X struct {
		f1 int
		f2 string
	}
	ntf := X{111, "Dude"}
	if ntf != (X{}) /*Error: with `X{}` syntax -> expected a declaration statement.*/ {
		fmt.Println("Value comparison mismatch")
	}
	fmt.Println("Nil object with type X:", (X{}), X{})

	var testStruct struct{} = struct{}{}
	fmt.Println("Nil object with non-type:", testStruct)
	/*
		Output:
		```
		life?
		main.cons{ask:"life?", cdr:main.cons{ask:"", cdr:interface {}(nil)}}
		with my
		main.cons{ask:"with my", cdr:main.cons{ask:"life?", cdr:main.cons{ask:"", cdr:interface {}(nil)}}}
		I doing
		main.cons{ask:"I doing", cdr:main.cons{ask:"with my", cdr:main.cons{ask:"life?", cdr:main.cons{ask:"", cdr:interface {}(nil)}}}}
		What am
		main.cons{ask:"What am", cdr:main.cons{ask:"I doing", cdr:main.cons{ask:"with my", cdr:main.cons{ask:"life?", cdr:main.cons{ask:"", cdr:interface {}(nil)}}}}}
		What am I doing with my life? No idea.
		Value comparison mismatch
		Nil object with type X: {0 } {0 }
		Nil object with non-type: {}
		```
	*/
}
