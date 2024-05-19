mkdir -p build
pushd build > /dev/null
clang -g -Wall -Wpedantic -o union_find.out ../union_find.c
popd > /dev/null
