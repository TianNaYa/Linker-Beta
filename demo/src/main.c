#include <stdio.h>
#include <parse.h>

void go( void* buffer, int length )
{
    PARSER parser;
    char*  data;
    int    size;

    /* create parser */
    ParserCreate( &parser, buffer, length );

    /* format 'z' */
    data = ParserExtract( &parser, &size );
    printf( "z -> %d | %s\n", size, data );

    /* format 'b' */
    printf( "b -> %d\n", ParserByte( &parser ) );

    /* format 's' */
    printf( "s -> %d\n", ParserWord( &parser ) );

    /* format 'i' */
    printf( "i -> %d\n", ParserInt( &parser ) );

    /* format 'f' */
    data = ParserExtract( &parser, &size );
    printf( "f -> %d | %s\n", size, data );

    /* format 'n' */
    printf( "n -> %s\n", ParserBool( &parser ) ? "true" : "false" );
}
