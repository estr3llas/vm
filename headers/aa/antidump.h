//
// Created by User on 9/7/2024.
//

#ifndef ANTIDUMP_H
#define ANTIDUMP_H

#include "../../headers/nt/peb.h"
#include "../../headers/nt/parser.h"

#define PAGE_SIZE 0x1000

namespace Antidump {
    void IncreaseSizeOfImage(peb::PPEB peb);
    void EraseHeader();
}

inline void EnableAntidump() {
    peb::PPEB peb = getPeb();
    Antidump::IncreaseSizeOfImage(peb);
    Antidump::EraseHeader();
}

#endif //ANTIDUMP_H
