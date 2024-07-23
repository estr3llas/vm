//
// Created by User on 7/21/2024.
//

#ifndef PARSER_H
#define PARSER_H

#include "peb.h"

PPEB getPeb();
PLDR_MODULE getNTDLL(PPEB peb);
PVOID getModuleBase();

#endif //PARSER_H
