//
// Created by User on 10/7/2024.
//

#ifndef LOG_H
#define LOG_H

#pragma once

#include <cstdarg>
#include <cstdio>
#include <Windows.h>

//
// Example usage:
//
// HWID_LOG(LOG_GENERAL, VERBOSITY_WARNING, L"This is a warning message");
// HWID_LOG(LOG_GENERAL, VERBOSITY_INFO, L"Informational message. Value: %d", someValue);
//
// HWID_LOG(LOG_ERROR, VERBOSITY_ERROR, TEXT(" Unable to retrieve value data for key %ls. Error Code: %d"), key_name, ret);
// HWID_LOG(LOG_ERROR, VERBOSITY_ERROR, TEXT("Failed to retrieve pcbData size. Error Code: %d"), GetLastError());
//

//
// Log categories
//
// This is actually not used, but it is nice for code readability purposes
//
#define LOG_GENERAL         0
#define LOG_ERROR           2
#define LOG_WARNING         1
#define LOG_INFO            0
#define LOG_SUCCESS         3

//
// Verbosity categories
//
// VERBOSITY_SUCCESS    =   [+]
// VERBOSITY_ERROR      =   [-]
// VERBOSITY_WARNING    =   [!]
// VERBOSITY_INFO       =   [i]
//
#define VERBOSITY_SUCCESS   3
#define VERBOSITY_ERROR     2
#define VERBOSITY_WARNING   1
#define VERBOSITY_INFO      0

//
// Log message
//
#define LOG_LEVEL_ERROR     TEXT("Error")
#define LOG_LEVEL_WARNING   TEXT("Warning")
#define LOG_LEVEL_INFO      TEXT("Info")
#define LOG_LEVEL_SUCCESS   TEXT("Success")

//
// Define which LOG_LEVEL we got
//
#define GET_LOG_LEVEL_STRING(verbosity)                     \
    ((verbosity) == VERBOSITY_SUCCESS ? LOG_LEVEL_SUCCESS : \
     (verbosity) >= VERBOSITY_ERROR ? LOG_LEVEL_ERROR :     \
     (verbosity) == VERBOSITY_WARNING ? LOG_LEVEL_WARNING : \
     LOG_LEVEL_INFO)

//
// Main log macro
//
#define HWID_LOG(category, verbosity, format, ...)                                                  \
    do {                                                                                            \
        const wchar_t* logLevelString = GET_LOG_LEVEL_STRING(verbosity);                            \
        wchar_t buffer[1024];                                                                       \
        swprintf(buffer, sizeof(buffer)/sizeof(wchar_t), TEXT("\t%ls: %ls\n"), logLevelString, format); \
        LogImpl(category, verbosity, buffer, __FUNCTIONW__, __LINE__,  __VA_ARGS__);                \
    } while(0)

//
// Actual logging
//
static void LogImpl(int category, int verbosity, const wchar_t* format, const wchar_t* func_name, int line,  ...) {
    va_list args;
    va_start(args, format);

    (void)category;

    switch (verbosity)
    {
    case VERBOSITY_SUCCESS:
        fwprintf(stdout, L"[+] ");
        break;
    case VERBOSITY_ERROR:
        fwprintf(stdout, L"[-] ");
        break;
    case VERBOSITY_WARNING:
        fwprintf(stdout, L"[!] ");
        break;
    case VERBOSITY_INFO:
        fwprintf(stdout, L"[i] ");
        break;
    default:
        fwprintf(stdout, L"[i] ");
        break;
    }
    wprintf(L"Function: %ls, Line: %d\n", func_name, line);
    vfwprintf(stdout, format, args);

    va_end(args);
}

#endif //LOG_H
