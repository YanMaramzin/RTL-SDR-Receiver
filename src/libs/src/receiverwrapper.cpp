#include "include/receiverwrapper.h"
#include "receiverhwimpl.h"


std::unique_ptr<IReceiver> ReceiverWrapper::getReceiverByName(std::string name)
{
    if (name == "hw")
        return std::make_unique<ReceiverHWImpl>();

    return nullptr;
}
