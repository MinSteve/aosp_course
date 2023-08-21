#include <IMyLight.h>
#include <binder/Parcel.h>

using namespace android;

class BpMyLight : public BpInterface<IMyLight> {

public:
    BpMyLight(const sp<IBinder>& remote) : BpInterface<IMyLight>(remote) { }

    virtual void turnOn(void) {
        Parcel data, reply;
        data.writeInterfaceToken(getInterfaceDescriptor());
        remote()->transact(TRANSACTION_turnOn, data, &reply, IBinder::FLAG_ONEWAY);
    }
    virtual void turnOff(void) {
        Parcel data, reply;
        data.writeInterfaceToken(getInterfaceDescriptor());
        remote()->transact(TRANSACTION_turnOff, data, &reply, IBinder::FLAG_ONEWAY);
    }
};
IMPLEMENT_META_INTERFACE(MyLight, "my_light");
