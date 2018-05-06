#include "head.h"


const char *MY_SECTION_HEADERS::m_pszTypeTable[]=
{
    "array of BYTE", "union", "DWORD", "DWORD",
    "DWORD", "DWORD", "DWORD", "WORD",
    "WORD", "DWORD"
};
const char *MY_SECTION_HEADERS::m_pszNameTable[]=
{
    "Name", "Misc", "VirtualAddress", "SizeOfRawData",
    "PointerToRawData", "PointerToRelocations", "PointerToLinenumbers", "NumberOfRelocations",
    "NumberOfLinenumbers", "Characteristics"
};
const size_t MY_SECTION_HEADERS::m_pnSizeTable[]=
{
    sizeof(BYTE)*8, sizeof(DWORD), sizeof(DWORD), sizeof(DWORD),
    sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(WORD),
    sizeof(WORD), sizeof(DWORD)
};


int MY_SECTION_HEADERS::Read(FILE *fp)
{
    int Size = SIZE_OF_SECTION_HEADER, number = 0, i;
    char *temp = (char*)malloc(Size);
    long start = MY_DOS_STUB::m_lpOffset_Of_NT_header+SIZE_OF_SIGNATURE
                 +SIZE_OF_FILE_HEADER +SIZE_OF_OPTIONAL_HEADER64;
    fseek(fp, (long)(start), SEEK_SET);
    while(1)
    {
        fread(temp, sizeof(char), (size_t)Size, fp);
        number++;
        for(i = 0; i < SIZE_OF_SECTION_HEADER; i++)
            if(*(temp+i) != 0)
                break;
        if(i == SIZE_OF_SECTION_HEADER)
            break;
    }
    this->numberOfsections = number-1;
    free(temp);
    temp = (char*)malloc(Size*(this->numberOfsections));
    fseek(fp, (long)(start), SEEK_SET);
    fread(temp, sizeof(char), (size_t)(Size*(this->numberOfsections)), fp);
    this->m_pcontent = temp;
    return 1;
}


int MY_SECTION_HEADERS::Paint()
{
    using namespace std;
    unsigned int i, j, k;
    LONG offset = MY_DOS_STUB::m_lpOffset_Of_NT_header+SIZE_OF_SIGNATURE
                +SIZE_OF_FILE_HEADER+SIZE_OF_OPTIONAL_HEADER64;
    cout <<MY_DOS_STUB::m_lpOffset_Of_NT_header<< endl;
    char *content = this->m_pcontent;
    cout << "_________________Section headers:\n";
    cout << setiosflags(ios::left);
    cout << setw(11) << "Offset";
    cout << setw(22) << "Descption";
    cout << setw(10) << "Type";
    cout << setw(3) << "Content\n";
    cout << "--------------------------------------------------" << endl;
    for(k = 0; k < this->numberOfsections; k++)
    {
        for(i = 0; i < NUMBER_OF_SECTION_HEADER; i++)
        {
            cout << setfill('0') << setiosflags(ios::right);
            cout << "0x" << setw(8) << hex << (LONG)offset << ' ';
            cout<<resetiosflags(ios::right);
            cout << setfill(' ');
            cout << setw(22) << MY_SECTION_HEADERS::m_pszNameTable[i];
            cout << setw(10) << MY_SECTION_HEADERS::m_pszTypeTable[i];
            cout << setfill('0') << setiosflags(ios::right);
            for(j = 0; j < MY_SECTION_HEADERS::m_pnSizeTable[i]; j++)
                cout << setw(2) << hex << (unsigned int)(unsigned char)*content++ << ' ';
            cout<<resetiosflags(ios::right);
            // Comment(i);
            cout << endl;
            offset += MY_SECTION_HEADERS::m_pnSizeTable[i];
        }
        cout << endl;
    }
    cout << setfill(' ') << resetiosflags(ios::right) << endl;
    return 1;
}

