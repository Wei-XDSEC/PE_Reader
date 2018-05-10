#include "head.h"
DWORD RVAtoRAW(MY_SECTION_HEADERS section_header, DWORD RVA)
{
    int i;
    for(i = 0; i < section_header.numberOfsections; i++)
    {
        if(RVA < section_header.m_pVirtualAdresses[i])
            return RVA-section_header.m_pVirtualAdresses[i-1]+section_header.m_pPointerToRawDatas[i-1];
    }
    return -1;
}

int main(int argc, char *argv[])
{
    char path[260];
    FILE *fp;
    MY_DOS_HEADER DOS_Header;
    MY_DOS_STUB DOS_Stub;
    MY_NT_HEADERS NT_Headers;
    MY_FILE_HEADER File_Header;
    MY_OPTIONAL_HEADER Optional_Header;
    MY_SECTION_HEADERS Section_Headers;
    MY_IMPORT_DIRECTORY_TABLE Import_Directory_Table;
    MY_INT_IAT_TABLE INT_IAT_table;

    if(argc < 2)
    {
        std::cout << "Enter the filename(.exe):" << std::endl;
        std::cin >> path;
        if((fp = fopen(path, "rb")) == NULL)
        {
            std::cout << "Cant' open it: " << path << std::endl;;
            return 0;
        }
    }
    else
    {
        if((fp = fopen(argv[1], "rb")) == NULL)
        {
            std::cout << "Cant' open it: " << path << std::endl;;
            return 0;
        }
    }
    DOS_Header.Read(fp);
    MY_DOS_STUB::m_lpOffset_Of_NT_header = DOS_Header.m_pDOS_Header->e_lfanew;
    DOS_Stub.Read(fp);
    NT_Headers.Read(fp);
    File_Header.Read(fp);
    if(File_Header.m_pFile_header->SizeOfOptionalHeader == 0xf0)
        Optional_Header.Is64 = true;
    else
        Optional_Header.Is64 = false;
    Optional_Header.Read(fp);
    Section_Headers.Read(fp, Optional_Header);
    Import_Directory_Table.Read(fp, Optional_Header, Section_Headers);
    INT_IAT_table.Read(fp, Import_Directory_Table, Section_Headers);


    DOS_Header.Paint();
    DOS_Stub.Paint();
    NT_Headers.Paint();
    File_Header.Paint();
    Optional_Header.Paint();
    Section_Headers.Paint(Optional_Header);
    Import_Directory_Table.Paint();
    INT_IAT_table.Paint(fp, Optional_Header, Section_Headers);
    return 0;
}
