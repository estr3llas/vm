//
// Created by User on 7/21/2024.
//
#include "../headers/common.h"
#include "../headers/peb.h"

#include "windows.h"

#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)

//static PPEB getPeb() {
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

PVOID getNTDLL(PPEB peb) {
    PPEB_LDR_DATA ldr_data = peb->LoaderData;
    const auto& [flink, blink] = ldr_data->InLoadOrderModuleList;

    // NASTY !
    const auto ntdll = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(flink->Flink->Flink);

    return ntdll->DllBase;
}

PIMAGE_EXPORT_DIRECTORY getNTDLLExportTable(DWORD_PTR ntdll) {
    const auto dosHdr = reinterpret_cast<PIMAGE_DOS_HEADER>(ntdll);
    const auto ntHdr = reinterpret_cast<PIMAGE_NT_HEADERS>(ntdll + dosHdr->e_lfanew);

    const auto optHdr = &(ntHdr->OptionalHeader);
    return reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(ntdll + optHdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
}

