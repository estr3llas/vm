//
// Created by User on 8/4/2024.
//

#ifndef SYSCALLS_H
#define SYSCALLS_H

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

#endif //SYSCALLS_H
