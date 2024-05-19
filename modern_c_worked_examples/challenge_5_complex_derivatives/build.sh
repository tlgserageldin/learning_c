mkdir -p build
pushd build > /dev/null
clang -g -Wall -Wpedantic -o complex_derivatives.out ../complex_derivatives.c
popd > /dev/null
