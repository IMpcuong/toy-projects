package main

import (
	"encoding/json"
	"fmt"
	"log"
)

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
}
