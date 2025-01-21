rm core/src/*.o
cd build
make
cd ..
make
#rm /lib/libslang.so
cp build/libslang.so /lib/libslang.so
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/c/Users/stenh/AudioProgramming/Slang/build/
./test
