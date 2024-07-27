//
// Created by User on 7/21/2024.
//

#ifndef PARSER_H
#define PARSER_H

#include "peb.h"

static PPEB getPeb();
PVOID getModuleBase();
extern "C" {
    PVOID getModuleBase2();
}

PVOID getNTDLL(PPEB peb);
int64_t getNTDLL2();

#endif //PARSER_H
