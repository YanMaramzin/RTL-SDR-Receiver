#include "include/receiver/receiverwrapper.h"
#include "include/receiver/receiverhwimpl.h"


std::unique_ptr<IReceiver> ReceiverWrapper::getReceiverByName(std::string name)
{
    if (name == "hw")
        return std::make_unique<ReceiverHWImpl>();

    return nullptr;
}
