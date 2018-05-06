#include "head.h"

int main()
{
    MY_DOS_HEADER DOS_Header;
    MY_DOS_STUB DOS_Stub;
    MY_NT_HEADERS NT_Headers;
    MY_FILE_HEADER File_Header;
    MY_OPTIONAL_HEADER Optional_Header;
    MY_SECTION_HEADERS Section_Headers;

    FILE *fp = fopen("D:\\test2.exe", "r");
    DOS_Header.Read(fp, 0);
    DOS_Header.Paint();
    MY_DOS_STUB::m_lpOffset_Of_NT_header = DOS_Header.m_pDOS_Header->e_lfanew;
    DOS_Stub.Read(fp);
    DOS_Stub.Paint();
    NT_Headers.Read(fp);
    NT_Headers.Paint();
    File_Header.Read(fp);
    File_Header.Paint();
    if(File_Header.m_pFile_header->SizeOfOptionalHeader == 0xf0)
        Optional_Header.Is64 = true;
    Optional_Header.Read(fp);
    Optional_Header.Paint();
    Section_Headers.Read(fp);
    Section_Headers.Paint();
    return 0;
}
