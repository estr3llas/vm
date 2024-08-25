//
// Created by User on 7/21/2024.
//
#include "../../headers/common.h"
#include "../../headers/nt/peb.h"

#include "windows.h"

#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)

auto getPeb() -> PPEB {
#ifdef _M_X64
    return reinterpret_cast<PPEB>(__readgsqword(0x60));
#elif _M_IX86
    return reinterpret_cast<PPEB>(__readfsdword(0x30));
#endif
}

auto getModuleBase() -> PVOID {
    const static auto peb = getPeb();
    return peb->ImageBase;
}

extern "C" {
    void *text_base() {
        return nullptr;
    }

    PVOID getModuleBase2() {
        static auto mbi = MEMORY_BASIC_INFORMATION();
        VirtualQueryEx(NtCurrentProcess(), reinterpret_cast<LPCVOID>(text_base()), &mbi, sizeof(mbi));

        return reinterpret_cast<PVOID>(reinterpret_cast<DWORD_PTR>(mbi.BaseAddress) - 0x3000);
    }
}

auto getNTDLL(PPEB peb) {
    const static auto ldr_data = peb->LoaderData;
    const auto& [flink, blink] = ldr_data->InLoadOrderModuleList;

    // NASTY !
    const static auto ntdll = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(flink->Flink->Flink);

    return ntdll->DllBase;
}

auto getNTDLLExportTable(DWORD_PTR ntdll) {
    const static auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(ntdll);
    const static auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(ntdll + dos->e_lfanew);

    const static auto opt = &(nt->OptionalHeader);
    return reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(ntdll + opt->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
}

