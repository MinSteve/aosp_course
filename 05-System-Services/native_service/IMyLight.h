#ifndef I_MYLIGHT_H
#define I_MYLIGHT_H

#include <binder/IInterface.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>

using namespace android;

class IMyLight : public IInterface {

public:
    DECLARE_META_INTERFACE(MyLight);

    virtual void turnOn(void) = 0;
    virtual void turnOff(void) = 0;
};

#define TRANSACTION_turnOn (IBinder::FIRST_CALL_TRANSACTION + 0)
#define TRANSACTION_turnOff (IBinder::FIRST_CALL_TRANSACTION + 1)

#endif  // I_MYLIGHT_H
