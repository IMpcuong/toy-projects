#!/bin/bash

go clean
go build .

declare -x binary_file=$(grep -E "module\s.+$" go.mod | cut -d' ' -f2)
./${binary_file}.exe