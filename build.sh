cd build
make
cd ..
make
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/root/Slang/build/
./test
