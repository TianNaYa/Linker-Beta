#ifndef _PARSER_H_
#define _PARSER_H_

#include <windows.h>

typedef struct {
    INT   Available;
    INT   Length;
    PVOID Data;
    PVOID Buffer;
} PARSER, *PARSER_PTR;

VOID  ParserCreate( PARSER_PTR Parser, PVOID Buffer, INT Length );
VOID  ParserReset( PARSER_PTR Parser );
BYTE  ParserByte( PARSER_PTR Parser );
WORD  ParserWord( PARSER_PTR Parser );
INT   ParserInt( PARSER_PTR Parser );
FLOAT ParserFloat( PARSER_PTR parser );
BOOL  ParserBool( PARSER_PTR Parser );
PVOID ParserPtr( PARSER_PTR Parser, INT Length );
PVOID ParserExtract( PARSER_PTR Parser, PINT Length );
PVOID ParserNext( PARSER_PTR Parser, INT Length );
INT   ParserAvailableLength( PARSER_PTR Parser );
VOID  ParserPointerOffsetIncreases( PARSER_PTR Parser, INT size );

#endif
