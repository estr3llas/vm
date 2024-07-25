//
// Created by User on 7/21/2024.
//
#include "../headers/common.h"
#include "../headers/peb.h"

#include "windows.h"

#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)

PPEB getPeb() {
#ifdef _M_X64
    return reinterpret_cast<PPEB>(__readgsqword(0x60));
#elif _M_IX86
    return reinterpret_cast<PPEB>(__readfsdword(0x30));
#endif
}

PVOID getModuleBase() {
    const auto peb = getPeb();
    return peb->ImageBase;
}

extern "C" {
    void *text_base_addr() {
        return nullptr;
    }

    PVOID getModuleBase2() {
        MEMORY_BASIC_INFORMATION meminfo;
        VirtualQueryEx(NtCurrentProcess(), (LPCVOID)text_base_addr, &meminfo, sizeof(meminfo));

        return meminfo.BaseAddress;
    }
}

PLDR_MODULE getNTDLL(PPEB peb) {
    PPEB_LDR_DATA ldr_data = peb->LoaderData;
    LIST_ENTRY* list_entry = &(ldr_data->InMemoryOrderModuleList);
    //nasty !
    const auto ldr_data_table_entry = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(list_entry->Flink->Flink->Flink);

    return static_cast<PLDR_MODULE>(ldr_data_table_entry->DllBase);
}