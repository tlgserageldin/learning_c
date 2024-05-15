mkdir -p build
pushd build > /dev/null
clang -g -Wall -o derivatives.out ../derivatives.c
popd > /dev/null
