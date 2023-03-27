#!/bin/bash

ps aux | grep -i python | awk '{ print $2 }' | tail -n+2 | xargs kill -9
