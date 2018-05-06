#include "head.h"

LONG MY_DOS_STUB::m_lpOffset_Of_NT_header = 0;

int MY_DOS_STUB::Read(FILE *fp)
{
    int Size = MY_DOS_STUB::m_lpOffset_Of_NT_header - SIZE_OF_DOS_HEADER;
    if(Size <= 0)
        return 0;
    char *temp = (char*)malloc(Size);
    fseek(fp, (long)(SIZE_OF_DOS_HEADER), SEEK_SET);
    fread(temp, sizeof(char), (size_t)Size, fp);
    this->m_pcontent = temp;
    return 1;
}

int MY_DOS_STUB::Paint()
{
    using namespace std;
    cout << "\n_________________DOS Stub:\n";
    if(MY_DOS_STUB::m_lpOffset_Of_NT_header == 0)
        cout << "No DOS stub or Packed file" << endl;

    int i, Size = MY_DOS_STUB::m_lpOffset_Of_NT_header - SIZE_OF_DOS_HEADER;
    int offset = SIZE_OF_DOS_HEADER;
    char *content = this->m_pcontent;
    char ascii[0x10 + 1] = {0};

    cout << setw(11) << "Offset";
    cout << setw(48) << "Content";
    cout << setw(17) << "Ascii" << endl;
    for(i = 0; i < 11+48+5; i++) cout << '-';
    cout << endl;
    cout << setfill('0') << setiosflags(ios::right);
    cout << "0x" << setw(8) << hex << (LONG)offset << ' ';
    for(i = 0; i < Size; i++)
    {
        ascii[i%0x10] = (*content >= 0x20 && *content <= 0x7E)?(*content):('.');
        cout << setw(2) << hex << (unsigned int)(unsigned char)*content++ << ' ';
        if(i % 0x10 == 0x10 -1)
        {
            cout << ascii << endl;
            offset += 0x10;
            cout << "0x" << setw(8) << hex << (LONG)offset << ' ';
        }
    }
    cout << setfill(' ') << resetiosflags(ios::right) ;
    return 1;
}
