#include "BnMyLight.h"
#include <binder/Parcel.h>

#undef LOG_TAG
#define LOG_TAG "MyLightService"

using namespace android;

class MyLightService : public BnMyLight {

private:
    int status;
public:
    MyLightService() {
        status = 0;
    }

    virtual void turnOn(){
        if(status == 0) {
            ALOGI("set_light on");
            status = 1;
        } else {
            ALOGE("light alread turn on");
        }
    }

    virtual void turnOff(){
        if(status == 1) {
            ALOGI("set_light off");
            status = 0;
        } else {
            ALOGE("light alread turn off");
        }
    }
};

