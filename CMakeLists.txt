cmake_minimum_required(VERSION 3.28)
project(simple_vm)

set(CMAKE_CXX_STANDARD 17)

add_executable(simple_vm src/main.cpp
        headers/Bytecode.h
        headers/common.h
        headers/Examples.h
        headers/exceptions.h
        headers/vm.h
        src/exception.cpp
        src/vm.cpp
        src/nt/parser.cpp
        headers/nt/parser.h
        headers/nt/syscalls.h
        headers/misc/usage.h
        src/nt/syscalls.cpp
        headers/nt/params.h
        headers/nt/peb.h
        src/aa/antidump.cpp
        headers/aa/antidump.h
        headers/misc/log.h
)
