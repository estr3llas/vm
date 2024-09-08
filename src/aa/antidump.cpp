//
// Created by User on 9/7/2024.
//

#include <stdio.h>

#include "../../headers/aa/antidump.h"
#include "../../headers/nt/peb.h"

void IncreaseSizeOfImage(peb::PPEB peb) {
    const static auto ldr_data = peb->LoaderData;
    const auto& [flink, blink] = ldr_data->InLoadOrderModuleList;
    const static auto pe = reinterpret_cast<peb::PLDR_DATA_TABLE_ENTRY>(flink->Flink);

    auto pSize = &pe->SizeOfImage;

    *pSize = static_cast<
        ULONG > (
            static_cast< INT_PTR > (pe->SizeOfImage + 0x10000000));
}
