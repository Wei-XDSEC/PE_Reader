#include "head.h"


const char *MY_DOS_HEADER::m_pszTypeTable[] =
{
    "WORD", "WORD", "WORD", "WORD",
    "WORD", "WORD", "WORD", "WORD",
    "WORD", "WORD", "WORD", "WORD",
    "WORD", "WORD", "WORD*", "WORD",
    "WORD", "WORD*", "LONG"
};

const char *MY_DOS_HEADER::m_pszNameTable[] =
{
    "e_magic", "e_cblp", "e_cp", "e_crlc",
    "e_cparhdr", "e_minalloc", "e_maxalloc", "e_ss",
    "e_sp", "e_csum", "e_ip", "e_cs",
    "e_lfarlc", "e_ovno", "e_res", "e_oemid",
    "e_oeminfo", "e_res2", "e_lfanew"
};

const size_t MY_DOS_HEADER::m_pnSizeTable[] =
{
    sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD),
    sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD),
    sizeof(WORD), sizeof(WORD), sizeof(WORD), sizeof(WORD),
    sizeof(WORD), sizeof(WORD), sizeof(WORD)*4, sizeof(WORD),
    sizeof(WORD), sizeof(WORD)*10, sizeof(LONG)
};

int MY_DOS_HEADER::Read(FILE* fp)
{
    char *temp = (char*)malloc(sizeof(_MY_IMAGE_DOS_HEADER));
    fseek(fp, (long)0, SEEK_SET);
    fread(temp, sizeof(char), sizeof(_MY_IMAGE_DOS_HEADER), fp);
    this->m_pDOS_Header = reinterpret_cast<MY_PIMAGE_DOS_HEADER>(temp);
    return 1;
}

int MY_DOS_HEADER::Paint()
{
    using namespace std;
    unsigned int i, j;
    LONG offset = 0;
    char *content = reinterpret_cast<char *>(this->m_pDOS_Header);
    cout << setfill(' ') <<setiosflags(ios::left);
    cout << "DOS header:\n";
    cout << "_______________________________________________________________" << endl;
    cout << setw(11) << "Offset";
    cout << setw(33) << "Name of member";
    cout << setw(14) << "Type";
    cout << setw(3) << "Value\n";
    cout << "---------------------------------------------------------------" << endl;
    for(i = 0; i < NUMBER_OF_FILE_HEADER; i++)
    {
        cout << setfill('0') << setiosflags(ios::right);
        cout << "0x" << setw(8) << hex << (LONG)offset << ' ';
        cout << setfill(' ') <<resetiosflags(ios::right);
        cout << setw(33) << MY_DOS_HEADER::m_pszNameTable[i];
        cout << setw(14) << MY_DOS_HEADER::m_pszTypeTable[i];
        cout << setfill('0') << setiosflags(ios::right);
        content += MY_DOS_HEADER::m_pnSizeTable[i]-1;
        for(j = 0; j < MY_DOS_HEADER::m_pnSizeTable[i]; j++)
            cout << setw(2) << hex << (unsigned int)(unsigned char)*(content-j);
        content += 1;
        cout<<resetiosflags(ios::right);
       Comment(i);
        cout << endl;
        offset += MY_DOS_HEADER::m_pnSizeTable[i];
    }
    cout << setfill(' ') << resetiosflags(ios::right) << endl;
    return 1;
}

int MY_DOS_HEADER::Comment(int index)
{
    using namespace std;
    cout << "    ";
    switch(index)
    {
    case 0:
        if(this->m_pDOS_Header->e_magic == 0x5a4d)
            cout << "#DOS signature: \"MZ\"";
        break;
    case 18:
        cout << "#offset to NT header";
        break;
    default:
        break;
    }
    return 0;
}
