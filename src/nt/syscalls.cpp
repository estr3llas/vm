//
// Created by User on 8/4/2024.
//

#include "Windows.h"
#include "Winternl.h"

#include "../../headers/nt/syscalls.h"

extern "C" {

    // https://github.com/winsiderss/systeminformer/blob/c2e84fb8ac3bd33ce63c5d55f9e5fb6720d382e0/phnt/include/ntmmapi.h#L532
    _Must_inspect_result_
    _When_(return == 0, __drv_allocatesMem(mem))
    NTSYSCALLAPI
    NTSTATUS
    NTAPI
    NtAllocateVirtualMemory(
        _In_ HANDLE ProcessHandle,
        _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID *BaseAddress,
        _In_ ULONG_PTR ZeroBits,
        _Inout_ PSIZE_T RegionSize,
        _In_ ULONG AllocationType,
        _In_ ULONG Protect
    );

    // https://github.com/winsiderss/systeminformer/blob/c2e84fb8ac3bd33ce63c5d55f9e5fb6720d382e0/phnt/include/ntmmapi.h#L568
    NTSYSCALLAPI
    NTSTATUS
    NTAPI
    NtFreeVirtualMemory(
        _In_ HANDLE ProcessHandle,
        _Inout_ PVOID *BaseAddress,
        _Inout_ PSIZE_T RegionSize,
        _In_ ULONG FreeType
    );

    // https://github.com/winsiderss/systeminformer/blob/c2e84fb8ac3bd33ce63c5d55f9e5fb6720d382e0/phnt/include/ntmmapi.h#L626
    NTSYSCALLAPI
    NTSTATUS
    NTAPI
    NtQueryVirtualMemory(
        _In_ HANDLE ProcessHandle,
        _In_opt_ PVOID BaseAddress,
        _In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
        _Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
        _In_ SIZE_T MemoryInformationLength,
        _Out_opt_ PSIZE_T ReturnLength
    );

}