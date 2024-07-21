//
// Created by User on 7/21/2024.
//
#include "../headers/common.h"
#include "../headers/peb.h"

#include "windows.h"

PPEB getPeb() {
    return reinterpret_cast<PPEB>(__readgsqword(0x30));
}

PLDR_MODULE getNTDLL(const PPEB peb) {
    PPEB_LDR_DATA ldr_data = peb->LoaderData;
    LIST_ENTRY* list_entry = &(ldr_data->InMemoryOrderModuleList);
    //nasty !
    const auto ldr_data_table_entry = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(list_entry->Flink->Flink->Flink);

    return static_cast<PLDR_MODULE>(ldr_data_table_entry->DllBase);
}