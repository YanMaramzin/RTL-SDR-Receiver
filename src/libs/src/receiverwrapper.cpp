#include "include/receiverwrapper.h"
#include "receiverhwimpl.h"


IReceiver* ReceiverWrapper::getReceiverByName(std::string name)
{
    if (name == "hw")
        return new ReceiverHWImpl();
}
