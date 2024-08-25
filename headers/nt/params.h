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

#endif //PARAMS_H
