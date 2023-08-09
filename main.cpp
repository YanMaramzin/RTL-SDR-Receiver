#include <iostream>
#include "receiverwrapper.h"

#include <vector>

using namespace std;
// real complex and spectrum is working
// fake: complex and spectrum writing in file and have 2nd version (wtout settings), complex

int main() {


// auto recImpl = ReceiverWrapper::getReceiverByName( "hw" );
// uint32_t centralFreq = 103.802e6;
// uint32_t sampleFreq = 2.6e6;
// RfSettings sett { centralFreq, sampleFreq, 400 };

// ReceiverSettings recset;
// recset.sampleCount = ( uint32_t )4194304; // must be 512 or higher
// recset.rfSettings = sett;
// BaseSettings* rp = &recset;
// recImpl->setSettings( rp );

// std::vector< Complex< uint8_t > > Buf;
// recImpl->getComplex( rp, Buf );

// std::vector< Complex< double > > SpBuf;
// recImpl->getSpectrum( rp, SpBuf );

// uint32_t N = Buf.size();
// std::ofstream fileOut( "/home/ann/WORK/work_mtlb/comsig.iqc", std::fstream::binary );

// for( uint32_t i = 0; i < 5; i++ ) {
// recImpl->getComplex( rp, Buf );
// fileOut.write( ( char* )( Buf.data() ), sizeof( uint8_t ) * 2 * N );
// }
// fileOut.close();


    sinParams sin1 { 0, 10 };
    // sinParams sin2 { 2, 20 };

    auto fakeImpl = ReceiverWrapper::getReceiverByName( "fake" );


    fakeParams fakeset;
    fakeset.fd = 1600;
    fakeset.sampleCount = 1000;
    fakeset.noiseLVL = 0;

    fakeset.sinPar = { sin1 };

    BaseSettings* fp = &fakeset;
    fakeImpl->setSettings( fp );

    std::vector< Complex< uint8_t > > Buf2;
    fakeImpl->getComplex( fp, Buf2 );

    std::vector< Complex< double > > SpecBuf;
    fakeImpl->getSpectrum( fp, SpecBuf );

    uint32_t N2 = Buf2.size();
    std::ofstream fileOut( "/home/ann/WORK/work_mtlb/comsig2.iqc", std::fstream::binary );

    fileOut.write( ( char* )( Buf2.data() ), sizeof( uint8_t ) * 2 * N2 );

    fileOut.close();

    return 0;
}

