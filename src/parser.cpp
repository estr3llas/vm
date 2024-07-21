//
// Created by User on 7/21/2024.
//
#include "../headers/common.h"
#include "../headers/peb.h"

#include "windows.h"

PPEB getPeb() {
    return reinterpret_cast<PPEB>(__readgsqword(0x30));
}