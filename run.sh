#!/bin/bash

set -e

BUILD_DIR="build"
EXECUTABLE_NAME="data-structures"
VALID_TESTS=("DynamicArray" "Stack" "Queue" "LinkedList")

if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR"
cmake ..
make

if [ "$1" == "tests" ]; then
    cd ..

    if [ -n "$2" ]; then
        if [[ " ${VALID_TESTS[@]} " =~ " $2 " ]]; then
            echo -e "\nRunning tests for $2.\n"
            GTEST_COLOR=1 ctest --test-dir build/test --output-on-failure -R "$2" -j12
        else
            echo -e "\nError: Not valid test '$2'. Expected one of: [${VALID_TESTS[*]}]."
            exit 1
        fi
    else
        echo -e "\nRunning all the tests.\n"
        GTEST_COLOR=1 ctest --test-dir build/test --output-on-failure -j12
    fi
elif [ "$1" == "run" ]; then
    if [ ! -f "$EXECUTABLE_NAME" ]; then
        echo -e "\nError: Executable file: $EXECUTABLE_NAME was not found in $BUILD_DIR directory."
        exit 1
    fi

    ./"$EXECUTABLE_NAME"
else
    echo -e "\nUsage: $0 {tests [TestName]|run}"
    exit 1
fi
