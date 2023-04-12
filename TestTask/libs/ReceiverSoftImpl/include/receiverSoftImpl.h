#ifndef RECEIVERSOFTIMPL_H
#define RECEIVERSOFTIMPL_H

#include <stdio.h>
#include "rtl-sdr.h"
#include "ireceiver.h"
#include "convenience.h"
#include <string.h>
#include <stdlib.h>

struct Param{
};

class ReceiverSoftImpl:public IReceiver{
public:
    void set(const ReceiverSettings &settings) override;
    void start() override;
    void stop() override;
    ~ReceiverSoftImpl() override;
};

#endif // RECEIVERSOFTIMPL_H
