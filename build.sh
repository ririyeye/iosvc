#! /bin/bash

build="tmp"
cur_path=$(pwd)

mkdir ${build}
cd ${build}
#cmake .. -DCMAKE_INSTALL_PREFIX=${workPath} -Dver=${ver} -DCMAKE_TOOLCHAIN_FILE=../compiler.a7.cmake
cmake .. -DCMAKE_INSTALL_PREFIX=${cur_path}
cpunum=$(cat /proc/cpuinfo | grep processor | wc -l)
make -j${cpunum}
make install
echo "123=${cur_path}"



