#include <iostream>
#include "receiverwrapper.h"

#include <vector>

using namespace std;

int main() {


    std::string recName( "hw" );
    auto recImpl = ReceiverWrapper::getReceiverByName( recName );
    uint32_t centralFreq = 102.2e6;
    uint32_t sampleFreq = 2.6e6;
    RfSettings sett { centralFreq, sampleFreq, 0 };

    ReceiverSettings recset;
    recset.sampleCount = ( uint32_t )4194304;
    recset.rfSettings = sett;
    BaseSettings* rp = &recset;
    recImpl->setSettings( rp );

    std::vector< Complex< uint8_t > > Buf;
// recImpl->getComplex( rp, Buf );

// uint32_t N = Buf.size();


// std::ofstream fileOut( "/home/ann/WORK/work_mtlb/comsig.iqc", std::fstream::binary );


// for( uint32_t i = 0; i < 2; i++ ) {

// recImpl->getComplex( rp, Buf );
// fileOut.write( ( char* )( Buf.data() ), sizeof( uint8_t ) * 2 * N );

// }
// fileOut.close();

// float ampl = 5;
// uint64_t freq = 10;
// sinParams sin1 { ampl, freq };


// std::string recName2( "fake" );
// auto fakeImpl = ReceiverWrapper::getReceiverByName( recName2 );

// uint64_t size = 20;
// uint32_t fd = 1600;
// float noiseLVL = 1;


// fakeParams fakeset;
// fakeset.sampleCount = size;
// fakeset.fd = fd;
// fakeset.noiseLVL = noiseLVL;
// fakeset.sinPar = sin1;

// std::cout << endl;
// std::cout << fakeset.fd << endl;


// BaseSettings* fp = &fakeset;
// fakeImpl->setSettings( fp );
// std::vector< Complex< uint8_t > > Buf2;
// fakeImpl->getComplex( fp, Buf2 );

// uint32_t N = Buf2.size();

// for( uint32_t i = 0; i < N; i++ ) {
// std::cout << endl;
// std::cout << Buf2[ i ];
// std::cout << endl;
// }


    return 0;
}

