//
// Created by User on 9/7/2024.
//

#include <Windows.h>


#include "../../headers/aa/antidump.h"

#include <exception>
#include <winternl.h>

#include "../../headers/nt/parser.h"
#include "../../headers/nt/peb.h"

#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)

#define STATUS_PROCEDURE_NOT_FOUND 0xC000007A
#define STATUS_INVALID_PAGE_PROTECTION 0xC0000045
#define STATUS_SECTION_PROTECTION 0xC000004E
#define STATUS_SUCCESS 0x00000000


namespace Antidump {

    typedef
    NTSYSCALLAPI
    NTSTATUS
    (NTAPI* pNtProtectVirtualMemory) (
        _In_ HANDLE ProcessHandle,
        _Inout_ PVOID* BaseAddress,
        _Inout_ PSIZE_T RegionSize,
        _In_ ULONG NewProtect,
        _Out_ PULONG OldProtect
    );

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

    NTSTATUS EraseHeader() {
#ifdef _M_X64
        auto peb = reinterpret_cast<
            peb::PPEB> (
                __readgsqword(0x60)
                );
#elif _M_IX86
        auto peb = reinterpret_cast<
            peb::PPEB> (
                __readfsdword(0x30)
                );
#else
	    #error "Unsupported architecture"
#endif

	    auto base = peb->ImageBase;

        const static auto ldr_data = peb->LoaderData;
        LIST_ENTRY* flink = ldr_data->InLoadOrderModuleList.Flink;

        const auto ntdll = reinterpret_cast<
            peb::PLDR_DATA_TABLE_ENTRY > (
                flink->Flink
                )->DllBase;

        if (!GetProcAddress(static_cast<HMODULE>(ntdll), "NtProtectVirtualMemory")) {
            SetLastError(ERROR_PROC_NOT_FOUND);
            return STATUS_PROCEDURE_NOT_FOUND;
        }

	    static auto _vprotect = reinterpret_cast<
            pNtProtectVirtualMemory > (
                GetProcAddress(static_cast<HMODULE>(ntdll), "NtProtectVirtualMemory")
                );

        ULONG oldProtect = 0;
        SIZE_T size = PAGE_SIZE;

        auto status = _vprotect(
            NtCurrentProcess(),
            &base,
            &size,
            PAGE_READWRITE,
            &oldProtect
        );

        if(!NT_SUCCESS(status)) {
            return status;
        }

        try {
            RtlSecureZeroMemory(
                base,
                PAGE_SIZE
            );
        }
        catch (const std::exception& e) {
            ULONG dummy;
            _vprotect(
                NtCurrentProcess(),
                &base,
                &size,
                oldProtect,
                &dummy
            );
            return STATUS_ACCESS_VIOLATION;
        }

	    status = _vprotect(
            NtCurrentProcess(),
            &base,
            &size,
            oldProtect,
            &oldProtect
        );

        return status;
    }
}
