package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"log"
	"os"
	"sync"
	"time"
)

type Statement struct {
	content string
	date    time.Time
}

func (s *Statement) String() string {
	strDate := s.date.GoString()
	return fmt.Sprintf("%s, written at %s", s.content, strDate)
}

type Embed struct {
	Statement
}

type LazyPrimes struct {
	once   sync.Once // Guards the prime slices, initiate once per invocation.
	primes []int
}

func (lp *LazyPrimes) init() {
	size := 10
	for i := 0; i < size; i++ {
		lp.primes = append(lp.primes, 2+3)
	}
}

func (lp *LazyPrimes) Primer() []int {
	lp.once.Do(lp.init) // Function decorator: `(*sync.Once).Do(f func())`.
	return lp.primes
}

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

	var t2 = []struct {
		i int
		s string
	}{
		{6 * 9, "Question"},
		{42, "Answer"},
	}
	fmt.Printf("%+v\n", t2)

	var data struct {
		ID     int
		Person struct {
			Name string
			Job  string
		}
	}
	const jsonData string = `{"ID": 123, "Person": {"Name": "NHT", "Job": "System Architecture"}}`
	err := json.Unmarshal([]byte(jsonData), &data)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(data.ID, data.Person.Name, data.Person.Job)

	e := &Embed{}
	e.content = "Ayokay"
	fmt.Println(e)

	// Anonymous structs: embedded mutex.
	// NOTE: An anonymous struct, which groups the related values with an embedded `sync.Mutex` field,
	// 	is commonly used to protect a global variable.
	var viewCount struct {
		sync.Mutex
		counter int64
	}
	viewCount.Lock()
	viewCount.counter = 1
	if viewCount.counter <= 10e4 {
		viewCount.counter <<= 10
	}
	viewCount.Unlock()
	fmt.Printf("%+v\n", &viewCount)

	// Anonymous interfaces:
	var fmtStringerAgent interface {
		String() string
	} = bytes.NewBufferString("Secret instance overrided from `fmt.Stringer`")
	fmt.Println(fmtStringerAgent.String())

	if _, ok := fmtStringerAgent.(interface {
		Fd() uintptr
	}); !ok {
		fmt.Println("Can't access methods of underlying *os.File")
	}

	// Method values: is what you get when you evaluate a method as an expression.
	// The result is a function value.

	// Evaluating a method from: `a type -> yields its function/method`.
	var fn func(*bytes.Buffer, string) (int, error)
	var buf bytes.Buffer
	fn = (*bytes.Buffer).WriteString // A pointer receiver method, yields from a type.
	fn(&buf, "Equivalent to `buf.WriteString` LMAO\n")
	buf.WriteString("Equivalent to `buf.WriteString` LMAO, really???\n")
	buf.WriteTo(os.Stdout)

	// Evaluating a method from: `a value -> create a closure that hold that value`.
	var fnVal func(string) (int, error)
	var bufVal bytes.Buffer
	fnVal = bufVal.WriteString // Yields from a value/instance.
	fnVal("Heyyyyy, I'm a fuckboy! ")
	fnVal("Your bazooms are huge\n")
	bufVal.WriteTo(os.Stdout)

	// Exp: Method values in `sync.Once`.
	lp := &LazyPrimes{}
	primes := lp.Primer()
	for _, p := range primes {
		fmt.Printf("%d~", p)
	}
}
