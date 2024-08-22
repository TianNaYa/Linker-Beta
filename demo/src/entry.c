#include <entry.h>
#include <parse.h>
#include <a.h>

void go( PVOID Buffer, INT Length, PDATA Sections )
{
    PARSER Parser = { 0 };
    LPVOID Data   = NULL;
    SIZE_T Size   = 0x1000;

    ParserCreate( &Parser, Buffer, Length );

    printf( "%s\n", ParserExtract( &Parser, NULL ) );           // 'z'
    printf( "%d\n", ParserInt( &Parser ) );                     // 'i'
    printf( "%d\n", ParserWord( &Parser ) );                    // 's'
    printf( "%d\n", ParserByte( &Parser ) );                    // 'b'
    printf( "%s\n", ParserBool( &Parser ) ? "true" : "false" ); // 'n'
    printf( "%s\n", ParserExtract( &Parser, NULL ) );           // 'f'

    // 'w'
    MessageBoxW( 0, ParserExtract( &Parser, NULL ), L"WCHAR String", MB_OK );

    NtAllocateVirtualMemory( GetCurrentProcess(), &Data, 0, &Size, MEM_COMMIT, PAGE_READWRITE );

    memset( Data, 0, Size );

    sprintf( Data, "Hello World 11111" );

    printf( "%s\n", Data );

    a();
    b();
    c();
    d();
}
