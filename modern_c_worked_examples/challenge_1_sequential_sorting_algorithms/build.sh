mkdir -p build
pushd build
clang -Wall -g -o sorting.out ../sorting.c
popd
