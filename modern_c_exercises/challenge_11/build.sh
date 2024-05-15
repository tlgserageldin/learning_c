#!/bin/bash

mkdir -p ./build/
pushd ./build/
clang -g -Wall -o image_seg.out ../image_segmentation.c
popd
