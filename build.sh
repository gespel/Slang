rm core/src/*.o
cd build
make
cd ..
make
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/sten/AudioProgramming/Slang/build/
./test
