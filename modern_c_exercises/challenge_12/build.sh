#!/bin/bash

mkdir -p ./build/
pushd ./build/
clang -g -Wall -o text_processor.out ../text_processor.c
popd
