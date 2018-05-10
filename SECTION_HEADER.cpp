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
    sizeof(BYTE)*MYIMAGE_SIZEOF_SHORT_NAME, sizeof(DWORD), sizeof(DWORD), sizeof(DWORD),
    sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(WORD),
    sizeof(WORD), sizeof(DWORD)
};

int MY_SECTION_HEADERS::Read(FILE *fp, MY_OPTIONAL_HEADER OH)
{
    int Size = SIZE_OF_SECTION_HEADER, number = 0, i, j;
    char *temp = (char*)malloc(Size);
    long start = MY_DOS_STUB::m_lpOffset_Of_NT_header+SIZE_OF_SIGNATURE
                 +SIZE_OF_FILE_HEADER;
    if(OH.Is64)
        start += SIZE_OF_OPTIONAL_HEADER64;
    else
        start += SIZE_OF_OPTIONAL_HEADER32;
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

    this->m_pszSectionNames = (char**)malloc(sizeof(char*)*(this->numberOfsections));
    for(i = 0; i < this->numberOfsections; i++)
        this->m_pszSectionNames[i] = (char*)malloc(sizeof(char) * (MYIMAGE_SIZEOF_SHORT_NAME+1));
    this->m_pVirtualAdresses = (DWORD*)malloc((this->numberOfsections)*sizeof(DWORD));
    this->m_pPointerToRawDatas = (DWORD*)malloc((this->numberOfsections)*sizeof(DWORD));
    for(i = 0; i < this->numberOfsections; i++)
    {
        for(j = 0; j < MYIMAGE_SIZEOF_SHORT_NAME; j++)
            this->m_pszSectionNames[i][j] = this->m_pcontent[j+i*SIZE_OF_SECTION_HEADER];
        this->m_pszSectionNames[i][j] = '\0';
        m_pVirtualAdresses[i] = *(reinterpret_cast<DWORD*>(this->m_pcontent+0xC+i*SIZE_OF_SECTION_HEADER));
        m_pPointerToRawDatas[i] = *(reinterpret_cast<DWORD*>(this->m_pcontent+0x14+i*SIZE_OF_SECTION_HEADER));
    }
    return 1;
}


int MY_SECTION_HEADERS::Paint(MY_OPTIONAL_HEADER OH)
{
    using namespace std;
    unsigned int i, j, k;
    LONG offset = MY_DOS_STUB::m_lpOffset_Of_NT_header+SIZE_OF_SIGNATURE
                +SIZE_OF_FILE_HEADER;
    if(OH.Is64)
        offset += SIZE_OF_OPTIONAL_HEADER64;
    else
        offset += SIZE_OF_OPTIONAL_HEADER32;

    char *content = this->m_pcontent;
    char ascii[MYIMAGE_SIZEOF_SHORT_NAME+1];
    ascii[MYIMAGE_SIZEOF_SHORT_NAME] = '\0';

    cout << "\nSection headers:\n";
    cout << setiosflags(ios::left);
    cout << "_______________________________________________________________" << endl;
    cout << setw(11) << "Offset";
    cout << setw(33) << "Descption";
    cout << setw(14) << "Type";
    cout << setw(3) << "Value\n";
    cout << "---------------------------------------------------------------" << endl;
    for(k = 0; k < this->numberOfsections; k++)
    {
        for(i = 0; i < NUMBER_OF_SECTION_HEADER; i++)
        {
            cout << setfill('0') << setiosflags(ios::right);
            cout << "0x" << setw(8) << hex << (LONG)offset << ' ';
            cout<<resetiosflags(ios::right);
            cout << setfill(' ');
            cout << setw(33) << MY_SECTION_HEADERS::m_pszNameTable[i];
            cout << setw(14) << MY_SECTION_HEADERS::m_pszTypeTable[i];
            cout << setfill('0') << setiosflags(ios::right);

            if(i % NUMBER_OF_SECTION_HEADER == 0)
            {
                for(j = 0; j < MY_SECTION_HEADERS::m_pnSizeTable[i]; j++)
                {
                    ascii[j] = (*content >= 0x20 && *content <= 0x7E)?(*content):(' ');;
                    cout << setw(2) << hex << (unsigned int)(unsigned char)*content++ << " ";
                }
                    cout << " #Ascii:";
                    for(j = 0; ascii[j]; j++)
                        cout << ascii[j];
            }
            else
            {
                content += m_pnSizeTable[i] - 1;
                for(j = 0; j < MY_SECTION_HEADERS::m_pnSizeTable[i]; j++)
                {
                    ascii[j] = (*content >= 0x20 && *content <= 0x7E)?(*content):(' ');;
                    cout << setw(2) << hex << (unsigned int)(unsigned char)*(content-j);
                }
                content += 1;
            }
            cout<<resetiosflags(ios::right) << endl;
            offset += MY_SECTION_HEADERS::m_pnSizeTable[i];
        }
        cout << endl;
    }
    cout << setfill(' ') << resetiosflags(ios::right) << endl;
    return 1;
}
