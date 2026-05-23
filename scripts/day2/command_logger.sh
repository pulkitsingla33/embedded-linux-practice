#!/bin/bash

$1

exit_code=$?

echo "[$(date)] $1, Exit code: $exit_code" >> command.log
