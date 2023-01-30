package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"log"
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
}
