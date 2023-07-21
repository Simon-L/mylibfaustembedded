#! /bin/bash

# if [ -n "$1" ]; then
#   echo "Using $1 as llvmroot"
#   llvmroot="$1"
# else
#   echo "Getting packages..."
#   llvmroot=$(mktemp -d)
#   pushd ${llvmroot}
#   wget http://ftp.de.debian.org/debian/pool/main/l/llvm-toolchain-15/llvm-15-dev_15.0.7-6_arm64.deb
#   dpkg-deb -x llvm-15-dev_15.0.7-6_arm64.deb .
#   wget http://ftp.de.debian.org/debian/pool/main/l/llvm-toolchain-15/llvm-15_15.0.7-6_arm64.deb
#   dpkg-deb -x llvm-15_15.0.7-6_arm64.deb .
#   wget http://ftp.de.debian.org/debian/pool/main/l/llvm-toolchain-15/libpolly-15-dev_15.0.7-6_arm64.deb
#   dpkg-deb -x libpolly-15-dev_15.0.7-6_arm64.deb .
#   popd
# fi

llvmroot=/tmp/tmp.GGwHGHTpvC

export PATH="${llvmroot}/usr/lib/llvm-14/bin:$PATH"

pushd build
cmake --toolchain ../scratch/aarch64-toolchain.cmake -C ./backends/all.cmake . -Bbuild -DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_VERBOSE_MAKEFILE=ON -DINCLUDE_DYNAMIC=ON -DINCLUDE_STATIC=ON \
	-DINCLUDE_LLVM=ON -DUSE_LLVM_CONFIG=ON \
	-DLLVM_CONFIG=${llvmroot}/usr/lib/llvm-14/bin/llvm-config \
	-DCMAKE_PREFIX_PATH=${llvmroot}/usr/lib/llvm-14/lib/cmake/llvm
cmake --build build --config Release --parallel 1 --verbose

popd

echo "Used root ${llvmroot}"