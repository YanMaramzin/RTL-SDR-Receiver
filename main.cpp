#include <iostream>
#include "receiverwrapper.h"

#include <vector>

using namespace std;

int main() {


// real complex and spectrum is working
// fake complex and spectrum is working

    auto recImpl = ReceiverWrapper::getReceiverByName( "hw" );
    uint32_t centralFreq = 88e6;
    uint32_t sampleFreq = 2.6e6;
    RfSettings sett { centralFreq, sampleFreq, 400 };

    ReceiverSettings recset;
    recset.sampleCount = ( uint32_t )1000; // to avoid errors set this 1000 or higher
    recset.rfSettings = sett;
    BaseSettings* rp = &recset;
    recImpl->setSettings( rp );

// std::vector< Complex< uint8_t > > Buf;
// recImpl->getComplex( rp, Buf );

    std::vector< Complex< double > > SpBuf;
    recImpl->getSpectrum( rp, SpBuf );

// uint32_t N = Buf.size();
// std::ofstream fileOut( "/home/ann/WORK/work_mtlb/comsig.iqc", std::fstream::binary );
// for( uint32_t i = 0; i < 2; i++ ) {
// recImpl->getComplex( rp, Buf );
// fileOut.write( ( char* )( Buf.data() ), sizeof( uint8_t ) * 2 * N );
// }
// fileOut.close();


// sinParams sin1 { 5, 10 };
// sinParams sin2 { 2, 20 };

// auto fakeImpl = ReceiverWrapper::getReceiverByName( "fake" );


// fakeParams fakeset;
// fakeset.sampleCount = 20;
// fakeset.fd = 1600;
// fakeset.noiseLVL = 1;

// fakeset.sinPar = { sin1, sin2 };

// BaseSettings* fp = &fakeset;
// fakeImpl->setSettings( fp );

// std::vector< Complex< uint8_t > > Buf2;
// fakeImpl->getComplex( fp, Buf2 );

// std::vector< Complex< double > > SpecBuf;
// fakeImpl->getSpectrum( fp, SpecBuf );

    return 0;
}

