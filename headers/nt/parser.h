//
// Created by User on 7/21/2024.
//

#ifndef PARSER_H
#define PARSER_H

#include "peb.h"

PPEB getPeb();
PVOID getModuleBase();
extern "C" {
    PVOID getModuleBase2();
}

PVOID getNTDLL(PPEB peb);
PIMAGE_EXPORT_DIRECTORY getNTDLLExportTable(DWORD_PTR ntdll);

#endif //PARSER_H
