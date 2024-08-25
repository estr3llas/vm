//
// Created by User on 8/25/2024.
//
#include "../../headers/nt/syscalls.h"
#include "../../headers/nt/parser.h"
#include "../../headers/common.h"

#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)

#pragma comment(lib, "ntdll")

auto FnVMAlloc(PSIZE_T sz, const ULONG type, const ULONG protect) -> NTSTATUS {
    PVOID ba;

    const static auto ntdll = getNTDLL(getPeb());
    const static auto pNtAllocateVirtualMemory = reinterpret_cast<Syscall::NtAllocateVirtualMemory>(
        GetProcAddress(static_cast<HMODULE>(ntdll), "NtAllocateVirtualMemory")
        );

    return pNtAllocateVirtualMemory(NtCurrentProcess(), &ba, 0, sz, type, protect);
}