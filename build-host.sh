rm -rf build
meson setup build
cd build
sudo meson install 
cd .. 
ninja -C build 
rm -rf slang-standalone-host/Builds/LinuxMakefile/build
make -j -C slang-standalone-host/Builds/LinuxMakefile/
