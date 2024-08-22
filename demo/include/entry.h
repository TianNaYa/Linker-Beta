#ifndef _ENTRY_H
#define _ENTRY_H

#include <stdio.h>
#include <windows.h>

typedef struct
{
    INT   Size;
    PVOID Data;
} DATA, *PDATA;

#define SEC_TEXT  ( 0x0000 )
#define SEC_DATA  ( 0x0001 )
#define SEC_RDATA ( 0x0002 )
#define SEC_BSS   ( 0x0003 )

#endif
