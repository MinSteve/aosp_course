#define LOG_TAG "Led"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "Led.h"

using aidl::vendor::cocktail::hardware::led::Led;
using std::string_literals::operator""s;

void logd(std::string msg) {
    std::cout << msg << std::endl;
    ALOGD("%s", msg.c_str());
}

void loge(std::string msg) {
    std::cout << msg << std::endl;
    ALOGE("%s", msg.c_str());
}

int main() {
    // Enable vndbinder to allow vendor-to-venfor binder call
    android::ProcessState::initWithDriver("/dev/vndbinder");

    ABinderProcess_setThreadPoolMaxThreadCount(0);
    ABinderProcess_startThreadPool();

    std::shared_ptr<Led> ledService = ndk::SharedRefBase::make<Led>();
    const std::string name = Led::descriptor + "/default"s;

    if (ledService != nullptr) {
        if(AServiceManager_addService(ledService->asBinder().get(), name.c_str()) != STATUS_OK) {
            loge("Failed to register ILed service");
            return -1;
        }
    } else {
        loge("Failed to get ILed instance");
        return -1;
    }

    logd("ILed service starts to join service pool");
    ABinderProcess_joinThreadPool();

    return EXIT_FAILURE;  // should not reached
}