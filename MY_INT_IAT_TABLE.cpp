#include "head.h"

int MY_INT_IAT_TABLE::Read(FILE *fp, MY_IMPORT_DIRECTORY_TABLE IDT, MY_SECTION_HEADERS SH)
{
    char *temp = reinterpret_cast<char *>(IDT.m_pContent);
    DWORD offset;
    int i, j;
    char ch;
    this->number = IDT.number;
    this->m_pszDllName = (char**)malloc(sizeof(char*) * IDT.number);
    for(int i = 0; i < IDT.number; i++)
        this->m_pszDllName[i] = (char*)malloc(sizeof(char) * 50);
    this->m_pINToffset = (DWORD*)malloc(sizeof(DWORD) * IDT.number);
    this->m_pIAToffset = (DWORD*)malloc(sizeof(DWORD) * IDT.number);
    for(i = 0; i < IDT.number; i++)
    {
        this->m_pINToffset[i] = *(reinterpret_cast<DWORD *>(temp + i * sizeof(_MY_IMAGE_IMPORT_DESCRIPTOR)));
        this->m_pINToffset[i] = RVAtoRAW(SH, this->m_pINToffset[i]);
        this->m_pIAToffset[i] = *(reinterpret_cast<DWORD *>(temp + 16 +i * sizeof(_MY_IMAGE_IMPORT_DESCRIPTOR)));
        this->m_pIAToffset[i] = RVAtoRAW(SH, this->m_pIAToffset[i]);
        offset = *(reinterpret_cast<DWORD *>(temp + 0xc + i * sizeof(_MY_IMAGE_IMPORT_DESCRIPTOR)));
        offset = RVAtoRAW(SH, offset);
        fseek(fp, (long)(offset), SEEK_SET);
        fread(&ch, sizeof(char), 1, fp);
        for(j = 0; ch != '\0'; j++)
        {
            this->m_pszDllName[i][j] = ch;
            fread(&ch, sizeof(char), 1, fp);
        }
        this->m_pszDllName[i][j] = '\0';
    }
    return 1;
}


int MY_INT_IAT_TABLE::Paint(FILE *fp, MY_OPTIONAL_HEADER OH, MY_SECTION_HEADERS SH)
{
    using namespace std;
    int i, j = 0;
    DWORD offsetINT;
    DWORD offsetIAT;
    ULONGLONG offsetIAT64;

    WORD Ordinal;
    char funName[100+1] = {0};
    cout << "\nImport Name Table:\n";
    cout << setiosflags(ios::left);
    cout << "_______________________________________________________________" << endl;
    if(OH.Is64)
    {
        for(i = 0; i < this->number; i++)
        {
            cout << "Functions imported from ";
            cout << this->m_pszDllName[i] << ":" << endl;
            cout << "________________________________________________________\n";
            cout << setw(12) << "RVA(INT)";
            cout << setw(12) << "RAW(INT)";
            cout << setw(13)  << "RAW(IAT)    ";
            cout << setw(8)  << "Ordinal";
            cout << "FuctionName" << endl;
            cout << "---------------------------------------------------------";
            fseek(fp, (long)(this->m_pIAToffset[i]), SEEK_SET);
            fread(&offsetINT, sizeof(DWORD), 1, fp);
            fseek(fp, (long)(this->m_pINToffset[i]), SEEK_SET);
            fread(&offsetIAT64, sizeof(ULONGLONG), 1, fp);
            while(offsetIAT64 != 0)
            {
                j++;
                cout << setfill('0') << setiosflags(ios::right) << endl;
                cout << "0x" << setw(4) << hex << offsetIAT64 << " ";
                offsetIAT64 = RVAtoRAW(SH, (DWORD)offsetIAT64);
                cout << setfill(' ') << resetiosflags(ios::right) << setw(5) << " ";

                cout << setfill('0') << setiosflags(ios::right);
                cout << "0x" << setw(4) << hex << offsetIAT64 << " ";
                cout << setfill(' ') << resetiosflags(ios::right) << setw(5) << " ";

                cout << setfill('0') << setiosflags(ios::right);
                cout << "0x" << setw(4) << hex << offsetIAT64 << " ";
                cout << setfill(' ') << resetiosflags(ios::right) << setw(5) << " ";

                fseek(fp, (long)(offsetIAT64), SEEK_SET);
                fread(&Ordinal, sizeof(WORD), 1, fp);
                cout << setfill('0');
                cout << setw(4) << hex << Ordinal;
                cout << setfill(' ')<< setw(5) << " ";

                fgets(funName, 100, fp);
                cout << funName;
                fseek(fp, (long)(this->m_pIAToffset[i] + j * sizeof(ULONGLONG)), SEEK_SET);
                fread(&offsetINT, sizeof(DWORD), 1, fp);
                fseek(fp, (long)(this->m_pINToffset[i] + j * sizeof(ULONGLONG)), SEEK_SET);
                fread(&offsetIAT64, sizeof(ULONGLONG), 1, fp);
            }
            j = 0;
            cout << '\n' << endl;
        }
    }
    else
    {
        for(i = 0; i < this->number; i++)
        {
            cout << "Functions imported from ";
            cout << this->m_pszDllName[i] << ":" << endl;
            cout << "________________________________________________________\n";
            cout << setw(12) << "RVA(INT)";
            cout << setw(12) << "RAW(INT)";
            cout << setw(13)  << "RAW(IAT)    ";
            cout << setw(8)  << "Ordinal";
            cout << "FuctionName" << endl;
            cout << "---------------------------------------------------------";
            fseek(fp, (long)(this->m_pIAToffset[i]), SEEK_SET);
            fread(&offsetINT, sizeof(DWORD), 1, fp);
            fseek(fp, (long)(this->m_pINToffset[i]), SEEK_SET);
            fread(&offsetIAT, sizeof(LONG), 1, fp);
            while(offsetIAT != 0)
            {
                j++;
                cout << setfill('0') << setiosflags(ios::right) << "\n";
                cout << "0x" << setw(4) << hex << offsetIAT << " ";
                offsetIAT = RVAtoRAW(SH, (DWORD)offsetIAT);
                cout << setfill(' ') << resetiosflags(ios::right) << setw(5) << " ";

                cout << setfill('0') << setiosflags(ios::right);
                cout << "0x" << setw(4) << hex << offsetIAT << " ";
                cout << setfill(' ') << resetiosflags(ios::right) << setw(5) << " ";

                cout << setfill('0') << setiosflags(ios::right);
                cout << "0x" << setw(4) << hex << offsetIAT << " ";
                cout << setfill(' ') << resetiosflags(ios::right) << setw(5) << " ";

                fseek(fp, (long)(offsetIAT), SEEK_SET);
                fread(&Ordinal, sizeof(WORD), 1, fp);
                cout << setfill('0');
                cout << setw(4) << hex << Ordinal;
                cout << setfill(' ')<< setw(5) << " ";

                fgets(funName, 100, fp);
                cout << funName ;
                fseek(fp, (long)(this->m_pIAToffset[i] + j * sizeof(LONG)), SEEK_SET);
                fread(&offsetINT, sizeof(DWORD), 1, fp);
                fseek(fp, (long)(this->m_pINToffset[i] + j * sizeof(LONG)), SEEK_SET);
                fread(&offsetIAT, sizeof(LONG), 1, fp);
            }
            j = 0;
            cout << '\n' << endl;
        }
    }
    cout << "---------------------------------------------------------------" << endl;
    return 0;
}
