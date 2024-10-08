//
// Created by User on 9/7/2024.
//

#include <Windows.h>


#include "../../headers/aa/antidump.h"

#include "../../headers/nt/parser.h"
#include "../../headers/nt/peb.h"

namespace Antidump {
    void IncreaseSizeOfImage(
        peb::PPEB peb
        ) {
        const static auto ldr_data = peb->LoaderData;
        const auto& [flink, blink] = ldr_data->InLoadOrderModuleList;
        const static auto pe = reinterpret_cast<peb::PLDR_DATA_TABLE_ENTRY>(flink->Flink);

        auto pSize = &pe->SizeOfImage;

        *pSize = static_cast<
            ULONG > (
                static_cast< INT_PTR > (pe->SizeOfImage + 0x10000000));
    }

    void EraseHeader() {
        DWORD oldProtect = 0;

        //auto base = getModuleBase2();

        if (const static auto base = getModuleBase();
            VirtualProtect(base, PAGE_SIZE, PAGE_READWRITE, &oldProtect)) {
            RtlSecureZeroMemory(base, PAGE_SIZE);

            VirtualProtect(base, PAGE_SIZE, oldProtect, &oldProtect);
            }
    }
}
