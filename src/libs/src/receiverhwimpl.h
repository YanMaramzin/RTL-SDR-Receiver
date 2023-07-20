#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <memory>
#include "include/ireceiver.h"

class ReceiverHWImpl : public IReceiver
{
public:
    ReceiverHWImpl();
    ~ReceiverHWImpl() override;

    bool getComplex(const ReceiverSettings &settings, Buffer &out) override;
    void getSpectrum(const ReceiverSettings &settings, SpectBuff &out) override;

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> m_d;

};


