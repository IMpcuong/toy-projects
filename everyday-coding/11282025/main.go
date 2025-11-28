package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
)

const _url string = "https://jsonplaceholder.typicode.com/users/1"

func main() {
	res, err := http.Get(_url)
	if err != nil {
		panic("Oops!!!")
	}
	defer res.Body.Close()

	byteData, _ := io.ReadAll(res.Body)
	// Method 1: Lowercase struct field(s) cannot be exported during the deserialize phase (handles by reflect-pkg).
	var u struct {
		ID   int    `json:"id"`
		Name string `json:"name"`
		Age  int    `json:"age,string"` // Converts to/from string
	}
	json.Unmarshal(byteData, &u)
	fmt.Println(u)

	// Method 2:
	var result map[string]any
	json.Unmarshal(byteData, &result)
	id := result["id"].(float64)
	name := result["name"].(string)
	if age, ok := result["age"].(string); ok {
		fmt.Println(age)
	}
	addr := result["address"].(any)
	fmt.Println(id, name, addr)
}
