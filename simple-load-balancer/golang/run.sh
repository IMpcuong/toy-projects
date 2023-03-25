#!/bin/bash

go build .

declare -a ports=(3031 3032 3033 3034 3035)
for i in ${!ports[@]}; do
  curl -vv "http://localhost:${ports[i]}"
  if [[ "$?" != 0 ]]; then
    # NOTE: Python version < 3.
    # python -m SimpleHTTPServer ${ports[i]} &
    python3 -m http.server ${ports[i]} &
  fi
done

"./slb" --backends="http://localhost:3031,http://localhost:3032,http://localhost:3033,http://localhost:3034,http://localhost:3035"
