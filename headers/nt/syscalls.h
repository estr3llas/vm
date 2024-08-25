//
// Created by User on 8/4/2024.
//

#ifndef SYSCALLS_H
#define SYSCALLS_H

#pragma comment(lib, "ntdll")
#include <Windows.h>

// https://github.com/winsiderss/systeminformer/blob/c2e84fb8ac3bd33ce63c5d55f9e5fb6720d382e0/phnt/include/ntmmapi.h#L83
typedef enum MEMORY_INFORMATION_CLASS
{
    MemoryBasicInformation,                 // q: MEMORY_BASIC_INFORMATION
    MemoryWorkingSetInformation,            // q: MEMORY_WORKING_SET_INFORMATION
    MemoryMappedFilenameInformation,        // q: UNICODE_STRING
    MemoryRegionInformation,                // q: MEMORY_REGION_INFORMATION
    MemoryWorkingSetExInformation,          // q: MEMORY_WORKING_SET_EX_INFORMATION // since VISTA
    MemorySharedCommitInformation,          // q: MEMORY_SHARED_COMMIT_INFORMATION // since WIN8
    MemoryImageInformation,                 // q: MEMORY_IMAGE_INFORMATION
    MemoryRegionInformationEx,              // MEMORY_REGION_INFORMATION
    MemoryPrivilegedBasicInformation,       // MEMORY_BASIC_INFORMATION
    MemoryEnclaveImageInformation,          // MEMORY_ENCLAVE_IMAGE_INFORMATION // since REDSTONE3
    MemoryBasicInformationCapped,           // 10
    MemoryPhysicalContiguityInformation,    // MEMORY_PHYSICAL_CONTIGUITY_INFORMATION // since 20H1
    MemoryBadInformation,                   // since WIN11
    MemoryBadInformationAllProcesses,       // since 22H1
    MaxMemoryInfoClass
} MEMORY_INFORMATION_CLASS;

namespace Syscall {


    extern "C" {

        // https://github.com/winsiderss/systeminformer/blob/c2e84fb8ac3bd33ce63c5d55f9e5fb6720d382e0/phnt/include/ntmmapi.h#L532
        typedef
        NTSTATUS
        (NTAPI* NtAllocateVirtualMemory)(
            _In_ HANDLE ProcessHandle,
            _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID *BaseAddress,
            _In_ ULONG_PTR ZeroBits,
            _Inout_ PSIZE_T RegionSize,
            _In_ ULONG AllocationType,
            _In_ ULONG Protect
        );

        // https://github.com/winsiderss/systeminformer/blob/c2e84fb8ac3bd33ce63c5d55f9e5fb6720d382e0/phnt/include/ntmmapi.h#L568
        typedef
        NTSYSCALLAPI
        NTSTATUS
        (NTAPI* NtFreeVirtualMemory)(
            _In_ HANDLE ProcessHandle,
            _Inout_ PVOID *BaseAddress,
            _Inout_ PSIZE_T RegionSize,
            _In_ ULONG FreeType
        );

        // https://github.com/winsiderss/systeminformer/blob/c2e84fb8ac3bd33ce63c5d55f9e5fb6720d382e0/phnt/include/ntmmapi.h#L626
        typedef
        NTSTATUS
        (NTAPI NtQueryVirtualMemory)(
            _In_ HANDLE ProcessHandle,
            _In_opt_ PVOID BaseAddress,
            _In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
            _Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
            _In_ SIZE_T MemoryInformationLength,
            _Out_opt_ PSIZE_T ReturnLength
        );
    }
}

#endif //SYSCALLS_H
