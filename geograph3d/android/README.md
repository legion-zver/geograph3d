# Сборка

## Статья

https://kvurd.com/blog/compiling-a-cpp-library-for-android-with-android-studio/

## Для сборки своей C++ библиотеки

./make-standalone-toolchain.sh --platform=android-24 --install-dir=/tmp/my-android-toolchain

./make-standalone-toolchain.sh --platform=android-24 --install-dir=/tmp/my-android-toolchain-x86 --arch=x86

export PATH=/tmp/my-android-toolchain/bin:$PATH

export PATH=/tmp/my-android-toolchain-x86/bin:$PATH
