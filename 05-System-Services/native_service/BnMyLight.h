#include <IMyLight.h>
#include <binder/Parcel.h>

using namespace android;

class BnMyLight : public BnInterface<IMyLight> {

public:
    virtual status_t onTransact( uint32_t code,
                                 const Parcel& data,
                                 Parcel* reply,
                                 uint32_t flags = 0);
};
