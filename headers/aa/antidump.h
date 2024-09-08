//
// Created by User on 9/7/2024.
//

#ifndef ANTIDUMP_H
#define ANTIDUMP_H

#include "../../headers/nt/peb.h"

#define PAGE_SIZE 0x1000

void IncreaseSizeOfImage(peb::PPEB peb);
void EraseHeader();

#endif //ANTIDUMP_H
