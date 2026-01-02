rm -rf build
meson setup build
cd build
sudo meson install 
cd ..
ninja -C build 
cd slang-standalone-host
rm -rf Builds/LinuxMakefile/build
make -j -C Builds/LinuxMakefile/
