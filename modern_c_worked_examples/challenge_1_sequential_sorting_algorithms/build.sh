mkdir -p build
pushd build > /dev/null
clang -Wall -g -o sorting.out ../sorting.c
popd > /dev/null
