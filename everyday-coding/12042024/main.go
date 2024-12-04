package main

import (
	"reflect"
	"time"
	"unsafe"
)

// curl -LO https://go.dev/dl/go1.23.4.darwin-amd64.pkg
// sudo installer -pkg ./go1.23.4.darwin-amd64.pkg -target /

type hiddenJutsu struct {
	difficulty   uint8
	name         string
	category     string
	power        uint32
	creationDate string
}

// Idea from: https://stackoverflow.com/a/43918797/12535617
func retrieveValFromUnexportedField(arbitraryStruct interface{}, totalFields int) []reflect.Value {
	// NOTE: Hypothetically, the struct was addressable.
	concreteTypeStruct := arbitraryStruct.(hiddenJutsu)
	structPtr := &concreteTypeStruct
	structVal := reflect.ValueOf(structPtr).Elem()
	var exportableVals []reflect.Value
	for i := 0; i < totalFields; i++ {
		field := structVal.Field(i)
		val := reflect.NewAt(field.Type(), unsafe.Pointer(field.UnsafeAddr())).Elem()
		exportableVals = append(exportableVals, val)
	}
	return exportableVals
}

func main() {
	jutsu := hiddenJutsu{
		difficulty:   1,
		name:         "Shinra Tensei",
		category:     "Agility",
		power:        1e8,
		creationDate: time.Now().Local().String(),
	}
	structPtr := uintptr(unsafe.Pointer(&jutsu))
	println(structPtr)

	v := reflect.ValueOf(jutsu)
	t := v.Type()
	totalFields := t.NumField()

	exportableVals := retrieveValFromUnexportedField(jutsu, totalFields)
	println(exportableVals[0].Convert(reflect.TypeOf(uint8(0))).Uint())
	println(exportableVals[1].String())
	println(exportableVals[2].String())
	println(exportableVals[3].Convert(reflect.TypeOf(uint32(0))).Uint())
	println(exportableVals[4].String())
}
