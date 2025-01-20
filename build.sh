rm core/src/*.o
cd build
make
cd ..
make
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/c/Users/stenh/AudioProgramming/Slang/build/
./test
