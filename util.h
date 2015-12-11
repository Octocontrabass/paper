#include <stdint.h>
#include <stdio.h>

void checked_fread( void * ptr, size_t size, size_t count, FILE * stream );
uint8_t checked_fget8( FILE * stream );
uint32_t checked_fget32( FILE * stream );
