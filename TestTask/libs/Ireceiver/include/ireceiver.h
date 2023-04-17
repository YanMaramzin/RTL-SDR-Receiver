#ifndef IRECEIVER_H
#define IRECEIVER_H

#include <cstdint>
#include "Complex.h"




struct RfSettings{
  uint32_t centralFreq;
  uint32_t sampleFreq;
};

struct ReceiverSettings{
    RfSettings rfSettings;
    uint32_t sampleCount;
    Complex<uint8_t> *outputBuffer;
//    Complex<int8_t> *outputBuffer;
    char const *fileName;
    uint32_t bytes_to_read;
    uint32_t n_read;
    int sync_mode;
    int direct_sampling;
    //..
};


class IReceiver
{
public:
    IReceiver(){};
    virtual void set(const ReceiverSettings &settings)=0;
//    virtual void set_freq(int freq)=0;
//    virtual void init()=0;

    virtual void start()=0;
    virtual void stop()=0;
    virtual ~IReceiver()=default;
};

#endif // IRECEIVER_H
