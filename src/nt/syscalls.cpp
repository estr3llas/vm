//
// Created by User on 8/4/2024.
//

#include "Windows.h"

#include "../../headers/nt/syscalls.h"

extern "C" {

    typedef NTSTATUS(NTAPI *NtAllocateVirtualMemory) (
        HANDLE ProcessHandle,
        PVOID *BaseAddress,
        ULONG_PTR ZeroBits,
        PSIZE_T RegionSize,
        ULONG AllocationType,
        ULONG Protect
        );

}