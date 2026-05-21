#!/bin/bash

mkdir -p logs

make -C src > logs/build_errors.txt

if [ $? -eq 0 ]; then
    echo "build successful"
    rm -f logs/build_errors.txt

    mv src/my_demo ./build/my_demo
else
    echo "build failed, check logs/build_errors.txt for details"
    exit 1
fi


