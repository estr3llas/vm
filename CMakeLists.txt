cmake_minimum_required(VERSION 3.28)
project(simple_vm)

set(CMAKE_CXX_STANDARD 17)

add_executable(simple_vm src/main.cpp
        headers/Bytecode.h
        headers/common.h
        headers/Examples.h
        headers/exception_handler.h
        headers/vm.h
        src/exception.cpp
        src/vm.cpp
        src/nt/parser.cpp
        headers/nt/peb.h
        headers/nt/parser.h
        headers/nt/syscalls.h
        headers/misc/usage.h
)
