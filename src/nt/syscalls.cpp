//
// Created by User on 8/25/2024.
//
#include "../../headers/nt/syscalls.h"
#include "../../headers/nt/parser.h"

#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)

#pragma comment(lib, "ntdll")

PVOID vm_alloc(
    PSIZE_T sz,
    const ULONG type,
    const ULONG protect
    ) {
    PVOID ba;

    const static auto ntdll = getNTDLL(getPeb());
    const static auto pNtAllocateVirtualMemory = reinterpret_cast<
        Syscall::NtAllocateVirtualMemory > (
            GetProcAddress(static_cast<HMODULE>(ntdll), "NtAllocateVirtualMemory")
        );

    if(pNtAllocateVirtualMemory(NtCurrentProcess(), &ba, 0, sz, type, protect) == STATUS_SUCCESS)
        return ba;

    return nullptr;
}

NTSTATUS vm_free(
    PVOID ba,
    PSIZE_T sz,
    const ULONG
    ) {
    const static auto ntdll = getNTDLL(getPeb());
    const static auto pNtFreeVirtualMemory = reinterpret_cast<
        Syscall::NtFreeVirtualMemory > (
            GetProcAddress(static_cast<HMODULE>(ntdll), "NtFreeVirtualMemory")
        );

    return pNtFreeVirtualMemory(NtCurrentProcess(), &ba, sz, type);
}
