#!/bin/bash

pushd build/
clang -g -Wall -o sorting.out ../sorting.c
popd
