//
// Created by User on 7/21/2024.
//

#ifndef PEB_H
#define PEB_H
#include <bemapiset.h>

typedef unsigned short USHORT;
typedef wchar_t WCHAR;
typedef WCHAR *NWPSTR, *LPWSTR, *PWSTR;
typedef void *PVOID;
typedef unsigned long ULONG;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef long LONG;
typedef __int64 LONGLONG;
typedef short SHORT;
typedef BYTE BOOLEAN;
typedef void *HANDLE;
typedef unsigned char UCHAR;

typedef struct LSA_UNICODE_STRING {
 USHORT Length;
 USHORT MaximumLength;
 PWSTR Buffer;
} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING, UNICODE_STRING, *PUNICODE_STRING;

typedef struct LDR_MODULE {
 LIST_ENTRY InLoadOrderModuleList;
 LIST_ENTRY InMemoryOrderModuleList;
 LIST_ENTRY InInitializationOrderModuleList;
 PVOID BaseAddress;
 PVOID EntryPoint;
 ULONG SizeOfImage;
 UNICODE_STRING FullDllName;
 UNICODE_STRING BaseDllName;
 ULONG Flags;
 SHORT LoadCount;
 SHORT TlsIndex;
 LIST_ENTRY HashTableEntry;
 ULONG TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

typedef struct PEB_LDR_DATA {
 ULONG Length;
 ULONG Initialized;
 PVOID SsHandle;
 LIST_ENTRY InLoadOrderModuleList;
 LIST_ENTRY InMemoryOrderModuleList;
 LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct PEB {
 BOOLEAN InheritedAddressSpace;
 BOOLEAN ReadImageFileExecOptions;
 BOOLEAN BeingDebugged;
 BOOLEAN Spare;
 HANDLE Mutant;
 PVOID ImageBase;
 PPEB_LDR_DATA LoaderData;
 PVOID ProcessParameters;
 PVOID SubSystemData;
 PVOID ProcessHeap;
 PVOID FastPebLock;
 PVOID FastPebLockRoutine;
 PVOID FastPebUnlockRoutine;
 ULONG EnvironmentUpdateCount;
 PVOID* KernelCallbackTable;
 PVOID EventLogSection;
 PVOID EventLog;
 PVOID FreeList;
 ULONG TlsExpansionCounter;
 PVOID TlsBitmap;
 ULONG TlsBitmapBits[0x2];
 PVOID ReadOnlySharedMemoryBase;
 PVOID ReadOnlySharedMemoryHeap;
 PVOID* ReadOnlyStaticServerData;
 PVOID AnsiCodePageData;
 PVOID OemCodePageData;
 PVOID UnicodeCaseTableData;
 ULONG NumberOfProcessors;
 ULONG NtGlobalFlag;
 BYTE Spare2[0x4];
 LARGE_INTEGER CriticalSectionTimeout;
 ULONG HeapSegmentReserve;
 ULONG HeapSegmentCommit;
 ULONG HeapDeCommitTotalFreeThreshold;
 ULONG HeapDeCommitFreeBlockThreshold;
 ULONG NumberOfHeaps;
 ULONG MaximumNumberOfHeaps;
 PVOID** ProcessHeaps;
 PVOID GdiSharedHandleTable;
 PVOID ProcessStarterHelper;
 PVOID GdiDCAttributeList;
 PVOID LoaderLock;
 ULONG OSMajorVersion;
 ULONG OSMinorVersion;
 ULONG OSBuildNumber;
 ULONG OSPlatformId;
 ULONG ImageSubSystem;
 ULONG ImageSubSystemMajorVersion;
 ULONG ImageSubSystemMinorVersion;
 ULONG GdiHandleBuffer[0x22];
 ULONG PostProcessInitRoutine;
 ULONG TlsExpansionBitmap;
 BYTE TlsExpansionBitmapBits[0x80];
 ULONG SessionId;
} PEB, *PPEB;

struct LDR_DATA_TABLE_ENTRY
{
    struct _LIST_ENTRY InLoadOrderLinks;                                    //0x0
    struct _LIST_ENTRY InMemoryOrderLinks;                                  //0x10
    struct _LIST_ENTRY InInitializationOrderLinks;                          //0x20
    VOID* DllBase;                                                          //0x30
    VOID* EntryPoint;                                                       //0x38
    ULONG SizeOfImage;                                                      //0x40
    UNICODE_STRING FullDllName;                                     //0x48
    UNICODE_STRING BaseDllName;                                     //0x58
    union
    {
        UCHAR FlagGroup[4];                                                 //0x68
        ULONG Flags;                                                        //0x68
        struct
        {
            ULONG PackagedBinary:1;                                         //0x68
            ULONG MarkedForRemoval:1;                                       //0x68
            ULONG ImageDll:1;                                               //0x68
            ULONG LoadNotificationsSent:1;                                  //0x68
            ULONG TelemetryEntryProcessed:1;                                //0x68
            ULONG ProcessStaticImport:1;                                    //0x68
            ULONG InLegacyLists:1;                                          //0x68
            ULONG InIndexes:1;                                              //0x68
            ULONG ShimDll:1;                                                //0x68
            ULONG InExceptionTable:1;                                       //0x68
            ULONG ReservedFlags1:2;                                         //0x68
            ULONG LoadInProgress:1;                                         //0x68
            ULONG LoadConfigProcessed:1;                                    //0x68
            ULONG EntryProcessed:1;                                         //0x68
            ULONG ProtectDelayLoad:1;                                       //0x68
            ULONG ReservedFlags3:2;                                         //0x68
            ULONG DontCallForThreads:1;                                     //0x68
            ULONG ProcessAttachCalled:1;                                    //0x68
            ULONG ProcessAttachFailed:1;                                    //0x68
            ULONG CorDeferredValidate:1;                                    //0x68
            ULONG CorImage:1;                                               //0x68
            ULONG DontRelocate:1;                                           //0x68
            ULONG CorILOnly:1;                                              //0x68
            ULONG ChpeImage:1;                                              //0x68
            ULONG ReservedFlags5:2;                                         //0x68
            ULONG Redirected:1;                                             //0x68
            ULONG ReservedFlags6:2;                                         //0x68
            ULONG CompatDatabaseProcessed:1;                                //0x68
        };
    };
    USHORT ObsoleteLoadCount;                                               //0x6c
    USHORT TlsIndex;                                                        //0x6e
    struct _LIST_ENTRY HashLinks;                                           //0x70
    ULONG TimeDateStamp;                                                    //0x80
    struct _ACTIVATION_CONTEXT* EntryPointActivationContext;                //0x88
    VOID* Lock;                                                             //0x90
    struct LDR_DDAG_NODE* DdagNode;                                        //0x98
    struct _LIST_ENTRY NodeModuleLink;                                      //0xa0
    struct LDRP_LOAD_CONTEXT* LoadContext;                                 //0xb0
    VOID* ParentDllBase;                                                    //0xb8
    VOID* SwitchBackContext;                                                //0xc0
    ULONGLONG OriginalBase;                                                 //0xf8
    union _LARGE_INTEGER LoadTime;                                          //0x100
    ULONG BaseNameHashValue;                                                //0x108
    ULONG ImplicitPathOptions;                                              //0x110
    ULONG ReferenceCount;                                                   //0x114
    ULONG DependentLoadFlags;                                               //0x118
    UCHAR SigningLevel;                                                     //0x11c
};

#endif //PEB_H
