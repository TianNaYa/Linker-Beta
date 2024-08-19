#include <parse.h>

VOID ParserCreate( PARSER_PTR parser, PVOID buffer, INT length )
{
    parser->Buffer    = buffer;
    parser->Length    = length;
    parser->Available = length;
    parser->Data      = buffer;
}

VOID ParserReset( PARSER_PTR parser )
{
    parser->Available = parser->Length;
    parser->Data      = parser->Buffer;
}

INT ParserAvailableLength( PARSER_PTR parser )
{
    return parser->Available;
}

VOID ParserPointerOffsetIncreases( PARSER_PTR parser, INT size )
{
    parser->Data      += size;
    parser->Available -= size;
}

BYTE ParserByte( PARSER_PTR parser )
{
    if ( ParserAvailableLength( parser ) < sizeof( BYTE ) )
    {
        return 0;
    }
    
    BYTE Result = *( PBYTE )( parser->Data );
    
    ParserPointerOffsetIncreases( parser , sizeof( BYTE ) );
    
    return Result;
}

WORD ParserWord( PARSER_PTR parser )
{
    if ( ParserAvailableLength( parser ) < sizeof( WORD ) )
    {
        return 0;
    }
    
    WORD Result = *( PWORD )( parser->Data );
    
    ParserPointerOffsetIncreases( parser , sizeof( WORD ) );
    
    return Result;
}

INT ParserInt( PARSER_PTR parser )
{
    if ( ParserAvailableLength( parser ) < sizeof( INT ) )
    {
        return 0;
    }
    
    INT Result = *( PINT )( parser->Data );
    
    ParserPointerOffsetIncreases( parser , sizeof( INT ) );
    
    return Result;
}

BOOL ParserBool( PARSER_PTR parser )
{
    return ParserInt( parser ) != 0;
}

FLOAT ParserFloat( PARSER_PTR parser )
{
    if ( ParserAvailableLength( parser ) < sizeof( FLOAT ) )
    {
        return 0;
    }
    
    FLOAT Result = *( PFLOAT )( parser->Data );
    
    ParserPointerOffsetIncreases( parser , sizeof( FLOAT ) );
    
    return Result;
}

PVOID ParserPtr( PARSER_PTR parser, INT length )
{
    if ( ParserAvailableLength( parser ) < length || length == 0 )
    {
        return NULL;
    }
    
    PVOID Result = parser->Data;
    
    ParserPointerOffsetIncreases( parser , length );
    
    return Result;
}

PVOID ParserExtract( PARSER_PTR parser, PINT length )
{
    if ( ParserAvailableLength( parser ) < sizeof( INT ) )
    {
        return NULL;
    }
    
    INT   Size   = ParserInt( parser );
    PVOID Result = ParserPtr( parser , Size );
    
    if ( Size == 0 || Result == NULL )
    {
        return NULL;
    }
    
    if ( length != NULL )
    {
        *length = Size;
    }
    
    return Result;
}

PVOID ParserNext( PARSER_PTR parser, INT Length )
{
    return ParserPtr( parser , Length );
}
