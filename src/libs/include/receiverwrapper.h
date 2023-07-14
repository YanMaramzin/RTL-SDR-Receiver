#pragma once

#include "ireceiver.h"

class ReceiverWrapper
{
public:
    static IReceiver* getReceiverByName(std::string name);
};

