//
// Created by User on 8/25/2024.
//

#ifndef PARAMS_H
#define PARAMS_H

#include <Windows.h>

namespace NtAllocateVirtualMemory_params {

    enum class AllocationType : ULONG {
        Commit = 0x1000,
        Reserve = 0x2000,
        Reset = 0x80000,
    };

    enum class Protection : ULONG {
        No_Access = 0x01,
        Read_Only = 0x02,
        Read_Write = 0x04,
        Execute = 0x10,
        Execute_Read = 0x20,
        Guard = 0x100,
        No_Cache = 0x200,
        WriteCombine = 0x400
    };
}

namespace NtFreeVirtualMemory_params {

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

    enum class FreeType : ULONG {
        Mem_Decommit = 0x4000,
        Mem_Release = 0x8000
    };
}

#endif //PARAMS_H
