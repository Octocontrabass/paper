#include <inttypes.h>
#include <stdlib.h>
#include <strings.h>
#include "decoder.h"
#include "util.h"

const uint8_t signature[4] = { 0x80, 0x37, 0x12, 0x40 };
const uint8_t id_j[5] = { 'N', 'M', 'Q', 'J', 0x00 };
const uint8_t id_e[5] = { 'N', 'M', 'Q', 'E', 0x00 };
const uint8_t id_p[5] = { 'N', 'M', 'Q', 'P', 0x00 };

int main(int argc, char **argv)
{
    if( argc < 2 )
    {
        fprintf( stderr, "Usage: %s romfile.z64\n", argv[0] );
        return EXIT_FAILURE;
    }
    FILE * romfile = fopen( argv[1], "rb" );
    if( !romfile )
    {
        fprintf( stderr, "Couldn't open file: %s\n", argv[1] );
    }
    uint8_t header[0x40];
    checked_fread( header, 1, 0x40, romfile );
    if( memcmp( &header[0x00], signature, 4 ) )
    {
        fprintf( stderr, "Is your ROM byteswapped?\nExpected 80 37 12 40 but got %02" PRIX8 " %02" PRIX8 " %02" PRIX8 " %02" PRIX8 "\n", header[0], header[1], header[2], header[3] );
        return EXIT_FAILURE;
    }
    if( !memcmp( &header[0x3B], id_j, 5 ) )
    {
        fprintf( stdout, "Japanese script\n\n" );
        decode( romfile, 0x1D40000, 0 );
    }
    else if( !memcmp( &header[0x3B], id_e, 5 ) )
    {
        fprintf( stdout, "English (North America) script\n\n" );
        decode( romfile, 0x1B83000, 1 );
    }
    else if( !memcmp( &header[0x3B], id_p, 5 ) )
    {
        fprintf( stdout, "English (Europe) script\n\n" );
        decode( romfile, 0x2030000, 1 );
        fprintf( stdout, "\n\nGerman script\n\n" );
        decode( romfile, 0x31B0000, 1 );
        fprintf( stdout, "\n\nFrench script\n\n" );
        decode( romfile, 0x3330000, 1 );
        fprintf( stdout, "\n\nSpanish script\n\n" );
        decode( romfile, 0x34B0000, 1 );
    }
    else
    {
        fprintf( stderr, "Unsupported ROM!\nExpected NMQJ 1.0, NMQE 1.0, or NMQP 1.0 but got %c%c%c%c 1.%" PRId8 "\n", header[0x3B], header[0x3C], header[0x3D], header[0x3E], header[0x3F] );
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
