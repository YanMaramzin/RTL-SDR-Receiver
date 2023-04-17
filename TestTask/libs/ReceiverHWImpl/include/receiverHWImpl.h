#ifndef RECEIVERHWIMPL_H
#define RECEIVERHWIMPL_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include "ireceiver.h"
#include "rtl-sdr.h"
#include <QObject>

extern "C"{
#include "convenience.h"
}


struct RcvHwImplParams{
};

class ReceiverHWImpl:public IReceiver
{
public:
    ReceiverHWImpl();
    void set(const ReceiverSettings &settings) override;
    void start() override;
    void stop() override;

    ~ReceiverHWImpl() override{
}



private:
    char const *filename;
    int n_read;
    int r, opt;
    int gain;
    int ppm_error;
    int sync_mode;
    int direct_sampling;
    int dithering;
    FILE *file;
    int dev_index;
    int dev_given;
    uint32_t frequency;
    uint32_t samp_rate;
    uint32_t out_block_size;
    rtlsdr_dev_t *dev;
    uint32_t bytes_to_read;
    int do_exit;
    Complex<uint8_t> *outputBuffer;
//    Complex<int8_t> *outputBuffer;
};


#endif // RECEIVERHWIMPL_H
