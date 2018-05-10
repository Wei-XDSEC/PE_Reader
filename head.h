#ifndef _HEAD_H_
#define _HEAD_H_

#include<iostream>
#include<iomanip>
#include<inttypes.h>
#include<stdlib.h>
#include<stdio.h>
//#include<winnt.h>
//_IMAGE_
typedef unsigned short WORD;
typedef uint64_t ULONGLONG;
typedef uint32_t LONG;
typedef int32_t DWORD;
typedef char BYTE;




//////////////////////////////////////////////////
/////DOS Header
#define NUMBER_OF_DOS_HEADER 19
#define SIZE_OF_DOS_HEADER 64
typedef struct _MY_IMAGE_DOS_HEADER
{
    WORD e_magic;
    WORD e_cblp;
    WORD e_cp;
    WORD e_crlc;
    WORD e_cparhdr;
    WORD e_minalloc;
    WORD e_maxalloc;
    WORD e_ss;
    WORD e_sp;
    WORD e_csum;
    WORD e_ip;
    WORD e_cs;
    WORD e_lfarlc;
    WORD e_ovno;
    WORD e_res[4];
    WORD e_oemid;
    WORD e_oeminfo;
    WORD e_res2[10];
    LONG e_lfanew;
} MY_IMAGE_DOS_HEADER, *MY_PIMAGE_DOS_HEADER;

class MY_DOS_HEADER
{
public:
    MY_PIMAGE_DOS_HEADER m_pDOS_Header;
    int Read(FILE *fp);
    int Paint();
    int Comment(int index);
public:
    static const char *m_pszTypeTable[];
    static const char *m_pszNameTable[];
    static const size_t m_pnSizeTable[];
};

//////////////////////////////////////////////////
/////DOS Stub
class MY_DOS_STUB
{
public:
    char *m_pcontent;
    int Read(FILE *fp);
    int Paint();
    static LONG m_lpOffset_Of_NT_header;
};

//////////////////////////////////////////////////
/////NT header: File Header
#define NUMBER_OF_FILE_HEADER 7
typedef struct _MY_IMAGE_FILE_HEADER
{
    WORD Machine;
    WORD NumberOfSections;
    DWORD TimeDateStamp;
    DWORD PointerToSymbolTable;
    DWORD NumberOfSymbols;
    WORD SizeOfOptionalHeader;
    WORD Characteristics;
} MYIMAGE_FILE_HEADER,*MYPIMAGE_FILE_HEADER;

class MY_FILE_HEADER
{
public:
    MYPIMAGE_FILE_HEADER m_pFile_header;
    int Read(FILE *fp);
    int Paint();
    static const char *m_pszTypeTable[];
    static const char *m_pszNameTable[];
    static const size_t m_pnSizeTable[];
};


//////////////////////////////////////////////////
/////NT header: Optional Header
typedef struct _MY_IMAGE_DATA_DIRECTORY
{
    DWORD VirtualAddress;
    DWORD Size;
} MYIMAGE_DATA_DIRECTORY,*MYPIMAGE_DATA_DIRECTORY;

#define MYIMAGE_NUMBEROF_DIRECTORY_ENTRIES 16
#define SIZE_OF_OPTIONAL_HEADER64 0xf0
#define SIZE_OF_OPTIONAL_HEADER32 0xe0
typedef struct _MY_IMAGE_OPTIONAL_HEADER32
{
    WORD Magic;
    BYTE MajorLinkerVersion;
    BYTE MinorLinkerVersion;
    DWORD SizeOfCode;
    DWORD SizeOfInitializedData;
    DWORD SizeOfUninitializedData;
    DWORD AddressOfEntryPoint;
    DWORD BaseOfCode;
    DWORD BaseOfData;
    DWORD ImageBase;
    DWORD SectionAlignment;
    DWORD FileAlignment;
    WORD MajorOperatingSystemVersion;
    WORD MinorOperatingSystemVersion;
    WORD MajorImageVersion;
    WORD MinorImageVersion;
    WORD MajorSubsystemVersion;
    WORD MinorSubsystemVersion;
    DWORD Win32VersionValue;
    DWORD SizeOfImage;
    DWORD SizeOfHeaders;
    DWORD CheckSum;
    WORD Subsystem;
    WORD DllCharacteristics;
    DWORD SizeOfStackReserve;
    DWORD SizeOfStackCommit;
    DWORD SizeOfHeapReserve;
    DWORD SizeOfHeapCommit;
    DWORD LoaderFlags;
    DWORD NumberOfRvaAndSizes;
    MYIMAGE_DATA_DIRECTORY DataDirectory[MYIMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} MYIMAGE_OPTIONAL_HEADER32,*MYPIMAGE_OPTIONAL_HEADER32;


typedef struct _MY_IMAGE_OPTIONAL_HEADER64
{
    WORD Magic;
    BYTE MajorLinkerVersion;
    BYTE MinorLinkerVersion;
    DWORD SizeOfCode;
    DWORD SizeOfInitializedData;
    DWORD SizeOfUninitializedData;
    DWORD AddressOfEntryPoint;
    DWORD BaseOfCode;
    ULONGLONG ImageBase;
    DWORD SectionAlignment;
    DWORD FileAlignment;
    WORD MajorOperatingSystemVersion;
    WORD MinorOperatingSystemVersion;
    WORD MajorImageVersion;
    WORD MinorImageVersion;
    WORD MajorSubsystemVersion;
    WORD MinorSubsystemVersion;
    DWORD Win32VersionValue;
    DWORD SizeOfImage;
    DWORD SizeOfHeaders;
    DWORD CheckSum;
    WORD Subsystem;
    WORD DllCharacteristics;
    ULONGLONG SizeOfStackReserve;
    ULONGLONG SizeOfStackCommit;
    ULONGLONG SizeOfHeapReserve;
    ULONGLONG SizeOfHeapCommit;
    DWORD LoaderFlags;
    DWORD NumberOfRvaAndSizes;
    MYIMAGE_DATA_DIRECTORY DataDirectory[MYIMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} MYIMAGE_OPTIONAL_HEADER64,*MYPIMAGE_OPTIONAL_HEADER64;


#define NUMBER_OF_OPTIONAL_HEADER64 30
#define NUMBER_OF_OPTIONAL_HEADER32 31
class MY_OPTIONAL_HEADER
{
    static const char *m_pszTypeTable32[];
    static const char *m_pszNameTable32[];
    static const size_t m_pnSizeTable32[];
    static const char *m_pszTypeTable64[];
    static const char *m_pszNameTable64[];
    static const size_t m_pnSizeTable64[];
    static const char *m_pszDataDirectoryTable[];
public:
    union m_pMY_IMAGE_OPTIONAL_HEADER
    {
        MYPIMAGE_OPTIONAL_HEADER32 MY_IMAGE_OPTIONAL_HEADER32;
        MYPIMAGE_OPTIONAL_HEADER64 MT_IMAGE_OPTIONAL_HEADER64;
    };
    MYPIMAGE_OPTIONAL_HEADER64 m_pOptional_header64;
    MYPIMAGE_OPTIONAL_HEADER32 m_pOptional_header32;
    int Read(FILE *fp);
    int Paint();
    bool Is64;
};


//////////////////////////////////////////////////
/////NT headers
typedef struct _MY_IMAGE_NT_HEADERS
{
    DWORD Signature;
    MYIMAGE_FILE_HEADER FileHeader;
    MYIMAGE_OPTIONAL_HEADER32 OptionalHeader;
} MY_IMAGE_NT_HEADERS32, *MYPIMAGE_NT_HEADERS32;

#define SIZE_OF_NT_HEADER 0XF8
#define SIZE_OF_SIGNATURE 0X4
#define SIZE_OF_FILE_HEADER 0x14
class MY_NT_HEADERS
{
public:
    char *m_pcontent;
    int Read(FILE *fp);
    int Paint();
};

//////////////////////////////////////////////////
/////Section headers
#define MYIMAGE_SIZEOF_SHORT_NAME 8
#define SIZE_OF_SECTION_HEADER 40
#define NUMBER_OF_SECTION_HEADER 10
typedef struct _IMAGE_SECTION_HEADER
{
    BYTE Name[MYIMAGE_SIZEOF_SHORT_NAME];
    union
    {
        DWORD PhysicalAddress;
        DWORD VirtualSize;
    } Misc;
    DWORD VirtualAddress;
    DWORD SizeOfRawData;
    DWORD PointerToRawData;
    DWORD PointerToRelocations;
    DWORD PointerToLinenumbers;
    WORD NumberOfRelocations;
    WORD NumberOfLinenumbers;
    DWORD Characteristics;
} MYIMAGE_SECTION_HEADER,*MYPIMAGE_SECTION_HEADER;

class MY_SECTION_HEADERS
{
    static const char *m_pszTypeTable[];
    static const char *m_pszNameTable[];
    static const size_t m_pnSizeTable[];
public:
    char *m_pcontent;
    char **m_pszSectionNames;
    DWORD *m_pVirtualAdresses;
    DWORD *m_pPointerToRawDatas;
    int Read(FILE *fp, MY_OPTIONAL_HEADER OH);
    int Paint(MY_OPTIONAL_HEADER OH);
    int numberOfsections;
};

//////////////////////////////////////////////////
/////Import Directory Table


typedef struct _MY_IMAGE_IMPORT_DESCRIPTOR
{
    union
    {
        DWORD Characteristics;
        DWORD OriginalFirstThunk;
    } DUMMYUNIONNAME;
    DWORD TimeDateStamp;

    DWORD ForwarderChain;
    DWORD Name;
    DWORD FirstThunk;
} MYIMAGE_IMPORT_DESCRIPTOR;

typedef struct _MY_IMAGE_IMPORT_BY_NAME
{
    WORD Hint;
    BYTE Name[1];
} MYIMAGE_IMPORT_BY_NAME,*MYPIMAGE_IMPORT_BY_NAME;

#define SIZE_OF_IMAGE_IMPORT_DESCRIPTOR 20
#define NUMBER_OF_IID 5
class MY_IMPORT_DIRECTORY_TABLE
{
    static const char *m_pszTypeTable[];
    static const char *m_pszNameTable[];
    static const size_t m_pnSizeTable[];
public:
    char *m_pContent;
    int number;
    int Read(FILE *fp, MY_OPTIONAL_HEADER OH, MY_SECTION_HEADERS SH);
    int Paint();
    DWORD offset;
};
//////////////////////////////////////////////////
/////Import Name Table & Import Adress Table
class MY_INT_IAT_TABLE
{
public:
    char **m_pszDllName;
    DWORD *m_pINToffset;
    DWORD *m_pIAToffset;
    int number;
    int Read(FILE *fp, MY_IMPORT_DIRECTORY_TABLE IDT, MY_SECTION_HEADERS SH);
    int Paint(FILE *fp, MY_OPTIONAL_HEADER OH, MY_SECTION_HEADERS SH);
};
DWORD RVAtoRAW(MY_SECTION_HEADERS section_header, DWORD RVA);
#endif // _HEAD_H_
