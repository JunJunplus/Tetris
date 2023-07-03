1.命令行编译：
arm-linux-gcc *.c -o main  -lpthread -L ./ -lfont -lm

2.cmake方式：
mkdir build

cd build

cmake ..

make
