#! /bin/bash

llvmroot=$(mktemp -d)

echo ${llvmroot}
pushd ${llvmroot}
wget http://ftp.de.debian.org/debian/pool/main/l/llvm-toolchain-15/llvm-15-dev_15.0.7-6_amd64.deb
dpkg-deb -x llvm-15-dev_15.0.7-6_amd64.deb .
wget http://ftp.de.debian.org/debian/pool/main/l/llvm-toolchain-15/llvm-15_15.0.7-6_amd64.deb
dpkg-deb -x llvm-15_15.0.7-6_amd64.deb .
wget http://ftp.de.debian.org/debian/pool/main/l/llvm-toolchain-15/libpolly-15-dev_15.0.7-6_amd64.deb
dpkg-deb -x libpolly-15-dev_15.0.7-6_amd64.deb .

popd
export PATH="${llvmroot}/usr/lib/llvm-15/bin:$PATH"

pushd faust/build
cmake  -C ./backends/all.cmake . -B${llvmroot}/build -DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_VERBOSE_MAKEFILE=ON -DINCLUDE_DYNAMIC=ON -DINCLUDE_STATIC=ON \
	-DINCLUDE_LLVM=ON -DUSE_LLVM_CONFIG=ON \
	-DLLVM_CONFIG=${llvmroot}/usr/lib/llvm-15/bin/llvm-config \
	-DCMAKE_PREFIX_PATH=${llvmroot}/usr/lib/llvm-15/lib/cmake/llvm
cmake --build ${llvmroot}/build --config Release --parallel 16

popd

echo "Used root ${llvmroot}"