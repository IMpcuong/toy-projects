#!/bin/bash

declare -x main_file="$(find . -type f -iname 'main.*')"
$(which black) -t py311 "${main_file}" --quiet
python3 "${main_file}"
