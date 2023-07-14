#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include "include/ireceiver.h"
#include "rtl-sdr.h"
#include "fft.h"

class ReceiverHWImpl : public IReceiver
{
public:
    ReceiverHWImpl();
    ~ReceiverHWImpl() override;

    bool getComplex(const ReceiverSettings &settings, Buffer &out) override;
    void getSpectrum(const ReceiverSettings &settings, SpectBuff &out) override;

private:
    void set(const ReceiverSettings &settings);
    void open();
    int n_read;
    int dev_index {0};
    int dev_given {0};
    rtlsdr_dev_t *dev {nullptr};
    int do_exit {0};

    int deviceSearch(char const *s);
    int setCenterFreq(uint32_t freq);
    int setSampleRate(uint32_t samp_rate);
    int setAutoGain();
    int nearestGain(int gain);
    int setGain(int gain);
    int setDirectSampling(int on);
    int setPpm(int ppm_error);
    void setAgcMode(int on);
    void setOffsetTuningOn();
    int resetBuffer();

    uint32_t roundPowerTwo(uint32_t &size);
};


