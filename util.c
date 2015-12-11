#include <stdlib.h>
#include "util.h"

void checked_fread( void * ptr, size_t size, size_t count, FILE * stream )
{
    if( fread( ptr, size, count, stream ) != count )
    {
        fprintf( stderr, "Error reading file.\n" );
        exit( EXIT_FAILURE );
    }
}

uint8_t checked_fget8( FILE * stream )
{
    int temp = fgetc( stream );
    if( temp == EOF )
    {
        fprintf( stderr, "Error reading file.\n" );
        exit( EXIT_FAILURE );
    }
    return (uint8_t)temp;
}

uint32_t checked_fget32( FILE * stream )
{
    uint32_t retval = checked_fget8( stream ) << 24;
    retval |= checked_fget8( stream ) << 16;
    retval |= checked_fget8( stream ) << 8;
    retval |= checked_fget8( stream );
    return retval;
}
