#include "receiversoftimpl.h"


FakeReceiver::FakeReceiver() {

}

FakeReceiver::~FakeReceiver() {


    delete f_p;
}

// void FakeReceiver::set(  fakeParams* fakeset ) {

// this->f_p  = fakeset;
// }


void FakeReceiver::setSettings( BaseSettings* settings ) {

    fakeParams* fakeset =  dynamic_cast<  fakeParams* >( settings );
    // set( fakeset );
}


template < typename Type >
std::vector< Complex< Type > > FakeReceiver::GenSignal( const fakeParams* fakeset ) {
    GenNoise WNGen;
    Generator_sin SnGen;
    std::vector< Complex< Type > > data = WNGen.GenWN< Type >( fakeset->noiseLVL, fakeset->sampleCount );
    // for( uint32_t i = 0; i < fakeset->sinPar.size(); i++ ) {
    std::vector< Complex< Type > > dataSin = SnGen.gen_sin< Type >( fakeset->sinPar.amp,  fakeset->sinPar.freq, fakeset->fd,  fakeset->sampleCount );
    for( uint64_t j = 0; j < fakeset->sampleCount; j++ ) {
        data[ j ] += dataSin[ j ];
    }

    return data;
}


bool FakeReceiver::getComplex( const BaseSettings* settings, Buffer& out ) {

    const fakeParams* fakeset =  dynamic_cast< const fakeParams* >( settings );
    std::vector< Complex< uint8_t > > data = this->GenSignal< uint8_t >( fakeset );
    for( uint64_t i = 0; i < fakeset->sampleCount; i++ ) {
        out[ i ] = data[ i ];
    }
    return 1;
}

void FakeReceiver::getSpectrum( const BaseSettings* settings, SpectBuff& out ) {

    const fakeParams* fakeset =  dynamic_cast< const fakeParams* >( settings );
    SpectBuff dataIN = this->GenSignal< double >( fakeset );
    // SpectBuff dataOUT;
    fft( dataIN, out, fakeset->sampleCount );
    // for( uint64_t i = 0; i < fakeSettings.sampleCount; i++ ) {
    // out[ i ] = dataOUT[ i ];
    // }

}

/*
   bool FakeReceiver::getComplex(  Buffer& ) {

    std::vector< Complex< uint8_t > > data = this->GenSignal< uint8_t >();
    for( uint64_t i = 0; i < fakeSettings.sampleCount; i++ ) {
        out[ i ] = data[ i ];
    }
    return 1;
   }

   void FakeReceiver::getSpectrum(  SpectBuff& ) {

    SpectBuff dataIN = this->GenSignal< double >();
    fft( dataIN, out, fakeSettings.sampleCount );

   }
 */




