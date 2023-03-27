#!/bin/bash

go build .

declare -a ports=(3031 3032 3033 3034 3035)
declare -x servers="http://localhost:${ports[0]}"
for i in ${!ports[@]}; do
  curl -vv "http://localhost:${ports[i]}"
  if [[ "$?" != 0 ]]; then
    # NOTE: Python version < 3.
    # python -m SimpleHTTPServer ${ports[i]} &
    python3 -m http.server ${ports[i]} &
    if (($i > 0)); then
      servers+=",http://localhost:${ports[i]}"
    fi
  fi
done

declare -x binfile=$(grep -E "module\s.+$" go.mod | cut -d' ' -f2)
"./slb" --servers="${servers}"
