#include "BnMyLight.h"
#include "BpMyLight.h"
#include <binder/Parcel.h>

#undef LOG_TAG
#define LOG_TAG "IMyLight"

using namespace android;

status_t BnMyLight::onTransact( uint32_t code,
                                 const Parcel& data,
                                 Parcel* reply,
                                 uint32_t flags){
    ALOGD("BnMyLight::onTransact invoked");
    CHECK_INTERFACE(IMyLight, data, reply);
    switch(code){
        case INTERFACE_TRANSACTION: {
            reply->writeString16(IMyLight::getInterfaceDescriptor() );
            return NO_ERROR;
            } break;

        case TRANSACTION_turnOn: {
            turnOn();
            return NO_ERROR;
            } break;

        case TRANSACTION_turnOff: {
            turnOff();
            return NO_ERROR;
            } break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}
