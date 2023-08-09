#ifndef GEN_NOISE_H
#define GEN_NOISE_H

#include <vector>
#include <ctime>
#include <cstdint>
#include "include/complex.h"


class GenNoise {
public:
    template < typename Type >
    std::vector< Complex< Type > > GenWN( float W, uint32_t size ) {
        srand( time( 0 ) );
        float A = sqrt( 1.5 / size ) * pow( 10, W / 20 );
        std::vector< Complex< Type > > data( size );

        for( uint32_t i = 0; i < size; i++ ) {
            data[ i ].re =   2 * ( ( rand() / ( static_cast< Type >( RAND_MAX ) ) ) - 0.5 );
            data[ i ].im =  (  rand()  / ( static_cast< Type >( RAND_MAX ) ) * 2 - 1  );
        }
        return data;
    }
private:
};


#endif // GEN_NOISE_H
