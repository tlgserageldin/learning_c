#!/bin/bash

mkdir -p build
pushd build
clang -g -Wall -o performance.out ../performance_comparison.c
popd
