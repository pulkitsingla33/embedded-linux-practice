#!/bin/bash

find . -type f -name "*.log"
find . -type f -name "*.log" -print0 | xargs -0 grep -l "ERROR"
find . -type f -name "*.log" -print0 | xargs -0 grep -o "ERROR" | wc -l

