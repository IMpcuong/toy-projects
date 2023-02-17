#!/bin/bash

declare -r outfile="out"
declare -x filename="$1"

# NOTE: `-e "$filename"` is identical with `test -n "$filename"`.
if [[ -e "${filename:-}" && "$filename" == *".c"* ]]; then
  gcc -Wall -Wextra -pedantic \
  -Wshadow -Wformat=2 -Wconversion \
  -Wpointer-arith -Wredundant-decls -Wnested-externs \
  -Wno-long-long -Wno-long-long \
  -std=c99 -O2 \
  -o "$outfile" "$filename"
else
  printf "ERROR: Please provide a C source code file to serve the compiler\n"
  exit 1
fi

[[ -e "$outfile" ]] || {
  printf "ERROR: Cannot locate the binaries executable file %s" "$outfile"
  exit 1
}
./"$outfile"

[[ "$?" == 0 ]] || {
  printf "ERROR: Runtime error with %s" "$outfile"
  exit 1
}
rm -f "$outfile" && exit 0
