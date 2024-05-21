mkdir -p build
pushd build > /dev/null
clang -Wall -pedantic -g -o dijkstras.out ../dijkstras.c
popd > /dev/null
