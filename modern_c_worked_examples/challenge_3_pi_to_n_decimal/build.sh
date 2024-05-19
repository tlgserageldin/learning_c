mkdir -p build
pushd build > /dev/null
clang -g -Wall -Wpedantic -o pi_to_n.out ../pi_to_n.c
popd > /dev/null
