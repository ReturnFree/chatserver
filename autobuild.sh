set -x

rm -rf "$(pwd)"/build/*

cmake .
make 
