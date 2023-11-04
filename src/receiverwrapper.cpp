#include "receiverwrapper.h"
#include "receiverhwimpl.h"
#include "receiversoftimpl.h"

std::unique_ptr< IReceiver > ReceiverWrapper::getReceiverByName( std::string name ) {
    if( name == "hw" )
        return std::make_unique< ReceiverHWImpl >();

    if( name == "fake" )
        return std::make_unique< FakeReceiver >();

    return nullptr;
}
