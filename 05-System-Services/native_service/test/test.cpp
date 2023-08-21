#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <utils/Log.h>

#include "../IMyLight.h"

int main(int argc, char *argv[]) {

    android::sp<android::IServiceManager> sm = android::defaultServiceManager();
    android::sp<android::IBinder> binder= sm->getService(android::String16("my_light"));
    if (binder == 0) {
        printf("Failed to get service\n");
        return -1;
    }

    android::sp<IMyLight> myLightService = android::interface_cast<IMyLight>(binder);
    myLightService->turnOn();

    myLightService->turnOff();

    return 0;
}
