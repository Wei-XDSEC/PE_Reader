#include "head.h"
int MY_NT_HEADERS::Read(FILE *fp)
{
    int Size = 4;
    char *temp = (char*)malloc(Size);
    fseek(fp, (long)(MY_DOS_STUB::m_lpOffset_Of_NT_header), SEEK_SET);
    fread(temp, sizeof(char), (size_t)Size, fp);
    this->m_pcontent = temp;
    return 1;
}

int MY_NT_HEADERS::Paint()
{
    using namespace std;
    cout << "\n__________________________________NT Headers:\n";
    cout << "_________________Signature:\n";
    cout << setw(11) << "Offset";
    cout << setw(3) << "Content\n";
    cout << "------------------" << endl;
    int i, Size = 4;
    char *content = this->m_pcontent;
    cout << setfill('0') << setiosflags(ios::right);
    cout << "0x" << setw(8) << hex << (LONG)(MY_DOS_STUB::m_lpOffset_Of_NT_header) << ' ';
    for(i = 0; i < Size; i++)
        cout << setw(2) << hex << (unsigned int)(unsigned char)*content++ << ' ';
    cout << "#Signature:\"PE\"\n";
    cout << setfill(' ') << resetiosflags(ios::right) <<  endl;
    return 1;
}

const char *MY_FILE_HEADER::m_pszTypeTable[]=
{
    "WORD", "WORD", "DWORD", "DWORD",
    "DWORD", "WORD", "WORD"
};
const char *MY_FILE_HEADER::m_pszNameTable[]=
{
    "Machine", "NumberOfSections", "TimeDataStamp", "PointerToSymbolTable",
    "NumberOfSymbols", "SizeOfOptionalHeader", "Characteristics"
};
const size_t MY_FILE_HEADER::m_pnSizeTable[]=
{
    sizeof(WORD), sizeof(WORD), sizeof(DWORD), sizeof(DWORD),
    sizeof(DWORD), sizeof(WORD), sizeof(WORD)
};

int MY_FILE_HEADER::Read(FILE *fp)
{
    int Size = SIZE_OF_FILE_HEADER;
    char *temp = (char*)malloc(Size);
    fseek(fp, (long)(MY_DOS_STUB::m_lpOffset_Of_NT_header+SIZE_OF_SIGNATURE), SEEK_SET);
    fread(temp, sizeof(char), (size_t)Size, fp);
    this->m_pFile_header = reinterpret_cast<MYPIMAGE_FILE_HEADER>(temp);
    return 1;
}

int MY_FILE_HEADER::Paint()
{
    using namespace std;
    unsigned int i, j;
    LONG offset = MY_DOS_STUB::m_lpOffset_Of_NT_header+SIZE_OF_SIGNATURE;
    char *content = reinterpret_cast<char *>(this->m_pFile_header);
    cout << "_________________File header:\n";
    cout << setiosflags(ios::left);
    cout << setw(11) << "Offset";
    cout << setw(22) << "Name of member";
    cout << setw(10) << "Type";
    cout << setw(3) << "Content\n";
    cout << "--------------------------------------------------" << endl;
    for(i = 0; i < NUMBER_OF_FILE_HEADER; i++)
    {
        cout << setfill('0') << setiosflags(ios::right);
        cout << "0x" << setw(8) << hex << (LONG)offset << ' ';
        cout<<resetiosflags(ios::right);
        cout << setfill(' ');
        cout << setw(22) << MY_FILE_HEADER::m_pszNameTable[i];
        cout << setw(10) << MY_FILE_HEADER::m_pszTypeTable[i];
        cout << setfill('0') << setiosflags(ios::right);
        for(j = 0; j < MY_FILE_HEADER::m_pnSizeTable[i]; j++)
            cout << setw(2) << hex << (unsigned int)(unsigned char)*content++ << ' ';
        cout<<resetiosflags(ios::right);
       // Comment(i);
        cout << endl;
        offset += MY_FILE_HEADER::m_pnSizeTable[i];
    }
    cout << setfill(' ') << resetiosflags(ios::right) << endl;
    return 1;
}


const char *MY_OPTIONAL_HEADER::m_pszTypeTable32[]=
{
    "WORD", "WORD", "DWORD", "DWORD",
    "DWORD", "WORD", "WORD"
};
const char *MY_OPTIONAL_HEADER::m_pszNameTable32[]=
{
    "Machine", "NumberOfSections", "TimeDataStamp", "PointerToSymbolTable",
    "NumberOfSymbols", "SizeOfOptionalHeader", "Characteristics"
};
const size_t MY_OPTIONAL_HEADER::m_pnSizeTable32[]=
{
    sizeof(WORD), sizeof(WORD), sizeof(DWORD), sizeof(DWORD),
    sizeof(DWORD), sizeof(WORD), sizeof(WORD)
};

const char *MY_OPTIONAL_HEADER::m_pszTypeTable64[]=
{
    "WORD", "BYTE", "BYTE", "DWORD",
    "DWORD", "DWORD", "DWORD", "DWORD",
    "ULONGLONG", "DWORD", "DWORD", "WORD",
    "WORD", "WORD", "WORD", "WORD",
    "WORD", "DWORD", "DWORD", "DWORD",
    "DWORD", "WORD", "WORD", "ULONGLONG",
    "ULONGLONG", "ULONGLONG", "ULONGLONG", "DWORD",
    "DWORD"
};
const char *MY_OPTIONAL_HEADER::m_pszNameTable64[]=
{
    "Magic", "MajorLinkerVersion", "MinorLinkerVersion", "SizeOfCode",
    "SizeOfInitializedData", "SizeOfUninitializedData", "AddressOfEntryPoint", "BaseOfCode",
    "ImageBase", "SectionAlignment", "FileAlignment", "MajorOperatingSystemVersion",
    "MinorOperatingSystemVersion", "MajorImageVersion", "MinorImageVersion", "MajorSubsystemVersion",
    "MinorSubsystemVersion", "Win32VersionValue", "SizeOfImage", "SizeOfHeaders",
    "CheckSum", "Subsystem", "DllCharacteristics", "SizeOfStackReserve",
    "SizeOfStackCommit", "SizeOfHeapReserve", "SizeOfHeapCommit", "LoaderFlags",
    "NumberOfRvaAndSizes"

};
const size_t MY_OPTIONAL_HEADER::m_pnSizeTable64[]=
{
    sizeof(WORD), sizeof(BYTE), sizeof(BYTE), sizeof(DWORD),
    sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(DWORD),
    sizeof(ULONGLONG), sizeof(DWORD), sizeof(DWORD), sizeof(DWORD),
    sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD),
    sizeof(WORD), sizeof(WORD), sizeof(DWORD), sizeof(DWORD),
    sizeof(DWORD), sizeof(WORD), sizeof(WORD), sizeof(ULONGLONG),
    sizeof(ULONGLONG), sizeof(ULONGLONG), sizeof(ULONGLONG), sizeof(DWORD),
    sizeof(DWORD)
};

const char *MY_OPTIONAL_HEADER::m_pszDataDirectoryTable[]=
{
    "EXPORT Directory", "IMPORT Directory", "RESOURCE Directory", "EXCEPTION Directory",
    "SECUTRITY Directory", "BASERELOC Directory", "DEBUG Directory", "COPYRIGHT Directory",
    "GLOBALPTR Directory", "TLS Directory", "LOAD_CONFIG Directory", "BOUND_IMPORT Directory",
    "IAT Directory", "DELAY_IMPORT Directory", "COM_DESCRIPTOR Directory", "Reserved Directory",
};

int MY_OPTIONAL_HEADER::Read(FILE *fp)
{
    int Size = this->Is64? 0xf0: 0xe0;
    char *temp = (char*)malloc(Size);
    fseek(fp, (long)(MY_DOS_STUB::m_lpOffset_Of_NT_header+SIZE_OF_SIGNATURE+SIZE_OF_FILE_HEADER), SEEK_SET);
    fread(temp, sizeof(char), (size_t)Size, fp);
    if(this->Is64)
        this->m_pOptional_header64 = reinterpret_cast<MYPIMAGE_OPTIONAL_HEADER64>(temp);
    else
        this->m_pOptional_header32 = reinterpret_cast<MYPIMAGE_OPTIONAL_HEADER32>(temp);
    return 1;
}

int MY_OPTIONAL_HEADER::Paint()
{
    using namespace std;
    char *content = reinterpret_cast<char *>(this->m_pOptional_header64);
    unsigned int i, j, NumberOfRvaAndSizes = this->m_pOptional_header64->NumberOfRvaAndSizes;
    LONG offset = MY_DOS_STUB::m_lpOffset_Of_NT_header+SIZE_OF_SIGNATURE+SIZE_OF_FILE_HEADER;
    cout << "_________________Optional header:\n";
    cout << setiosflags(ios::left);
    cout << setw(11) << "Offset";
    cout << setw(33) << "Name of member";
    cout << setw(10) << "Type";
    cout << setw(3) << "Content\n";
    cout << "--------------------------------------------------" << endl;
    for(i = 0; i < NUMBER_OF_OPTIONAL_HEADER64-1; i++)
    {
        cout << setfill('0') << setiosflags(ios::right);
        cout << "0x" << setw(8) << hex << (LONG)offset << ' ';
        cout<<resetiosflags(ios::right);
        cout << setfill(' ');
        cout << setw(33) << MY_OPTIONAL_HEADER::m_pszNameTable64[i];
        cout << setw(10) << MY_OPTIONAL_HEADER::m_pszTypeTable64[i];
        cout << setfill('0') << setiosflags(ios::right);
        for(j = 0; j < MY_OPTIONAL_HEADER::m_pnSizeTable64[i]; j++)
            cout << setw(2) << hex << (unsigned int)(unsigned char)*content++ << ' ';
        cout<<resetiosflags(ios::right);
       // Comment(i);
        cout << endl;
        offset += MY_OPTIONAL_HEADER::m_pnSizeTable64[i];
    }
    cout << setfill('0') << setiosflags(ios::right);
    cout << "0x" << setw(8) << hex << (LONG)offset << ' ';
    cout << setfill(' ') << resetiosflags(ios::right);
    cout << setw(33) << "DataDirectory";
    cout << "array of IMAGE_DATA_DIRECTORY" << endl;
    for(i = 0; i < NumberOfRvaAndSizes; i++)
    {
        cout << setfill('0') << setiosflags(ios::right);
        cout << "0x" << setw(8) << hex << (LONG)offset << ' ';
        cout<<resetiosflags(ios::right);
        cout << setfill(' ');
        cout << setw(8) << "RVA of ";
        cout << setw(25) << MY_OPTIONAL_HEADER::m_pszDataDirectoryTable[i];
        cout << setw(10) << "DWORD";
        cout << setfill('0') << setiosflags(ios::right);
        for(j = 0; j < sizeof(DWORD); j++)
            cout << setw(2) << hex << (unsigned int)(unsigned char)*content++ << ' ';
        cout<<resetiosflags(ios::right) << endl;
        offset += sizeof(DWORD);
        cout << setfill('0') << setiosflags(ios::right);
        cout << "0x" << setw(8) << hex << (LONG)offset << ' ';
        cout<<resetiosflags(ios::right);
        cout << setfill(' ');
        cout << setw(8) << "size of ";
        cout << setw(25) << MY_OPTIONAL_HEADER::m_pszDataDirectoryTable[i];
        cout << setw(10) << "DWORD";
        cout << setfill('0') << setiosflags(ios::right);
        for(j = 0; j < sizeof(DWORD); j++)
            cout << setw(2) << hex << (unsigned int)(unsigned char)*content++ << ' ';
        cout<<resetiosflags(ios::right) << endl;
        offset += sizeof(DWORD);
    }
    cout << setfill(' ') << resetiosflags(ios::right) << endl;
    return 1;
}
