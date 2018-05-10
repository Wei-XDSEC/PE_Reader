#include "head.h"

const char *MY_IMPORT_DIRECTORY_TABLE::m_pszTypeTable[]=
{
    "union", "DWORD", "DWORD", "DWORD",
    "DWORD"
};

const char *MY_IMPORT_DIRECTORY_TABLE::m_pszNameTable[]=
{
    "INT address", "TimeDataStamp", "ForwarderChain", "Name",
    "FirstThunk"

};

const size_t MY_IMPORT_DIRECTORY_TABLE::m_pnSizeTable[]=
{
    sizeof(DWORD), sizeof(DWORD), sizeof(DWORD), sizeof(DWORD),
    sizeof(DWORD)
};


int MY_IMPORT_DIRECTORY_TABLE::Read(FILE *fp, MY_OPTIONAL_HEADER OH, MY_SECTION_HEADERS SH)
{
    int Size = SIZE_OF_IMAGE_IMPORT_DESCRIPTOR, number = 0, i;
    char *temp = (char*)malloc(Size), *tem;
    DWORD offset;
    if(OH.Is64)
    {
        tem = reinterpret_cast<char *>(OH.m_pOptional_header64);
        offset = *(reinterpret_cast<DWORD *>(tem + 0x78));
        offset = RVAtoRAW(SH, offset);
    }
    else
    {
        tem = reinterpret_cast<char *>(OH.m_pOptional_header32);
        offset = *(reinterpret_cast<DWORD *>(tem + 0x68));
        offset = RVAtoRAW(SH, offset);
    }
    this->offset = offset;
    long start = offset;
    fseek(fp, start, SEEK_SET);
    while(1)
    {
        fread(temp, sizeof(char), (size_t)Size, fp);
        number++;
        for(i = 0; i < SIZE_OF_IMAGE_IMPORT_DESCRIPTOR; i++)
            if(*(temp+i) != 0)
                break;
        if(i == SIZE_OF_IMAGE_IMPORT_DESCRIPTOR)
            break;
    }
    this->number = number-1;
    free(temp);
    temp = (char*)malloc(Size*(this->number));
    fseek(fp, (long)(start), SEEK_SET);
    fread(temp, sizeof(char), (size_t)(Size*(this->number)), fp);
    this->m_pContent = temp;
    return 1;
}


int MY_IMPORT_DIRECTORY_TABLE::Paint()
{
    using namespace std;
    unsigned int i, j, k;
    LONG offset = this->offset;
    char *content = this->m_pContent;

    cout << "\nImport Directory Table:\n";
    cout << setiosflags(ios::left);
    cout << "_______________________________________________________________" << endl;
    cout << setw(11) << "Offset";
    cout << setw(33) << "Descption";
    cout << setw(14) << "Type";
    cout << setw(3) << "Value\n";
    cout << "---------------------------------------------------------------" << endl;

    for(k = 0; k < this->number; k++)
    {
        for(i = 0; i < NUMBER_OF_IID; i++)
        {
            cout << setfill('0') << setiosflags(ios::right);
            cout << "0x" << setw(8) << hex << (LONG)offset << ' ';
            cout<<resetiosflags(ios::right);
            cout << setfill(' ');
            cout << setw(33) << MY_IMPORT_DIRECTORY_TABLE::m_pszNameTable[i];
            cout << setw(14) << MY_IMPORT_DIRECTORY_TABLE::m_pszTypeTable[i];
            cout << setfill('0') << setiosflags(ios::right);
            content += m_pnSizeTable[i] - 1;
            for(j = 0; j < MY_IMPORT_DIRECTORY_TABLE::m_pnSizeTable[i]; j++)
            {
                cout << setw(2) << hex << (unsigned int)(unsigned char)*(content-j);
            }
            content += 1;
            cout<<resetiosflags(ios::right) << endl;
            offset += MY_IMPORT_DIRECTORY_TABLE::m_pnSizeTable[i];
        }
        cout << endl;
    }
    cout << setfill(' ') << resetiosflags(ios::right) << endl;
    return 1;
}
