/*
 * Copyright (C) 2023 Dung Tran Anh
 */

#define LOG_TAG "Led"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "Led.h"

using aidl::vendor::cocktail::hardware::led::Led;

int main() {
    // Enable vndbinder to allow vendor-to-venfor binder call
    android::ProcessState::initWithDriver("/dev/vndbinder");

    ABinderProcess_setThreadPoolMaxThreadCount(0);
    ABinderProcess_startThreadPool();

    std::shared_ptr<Led> ledService = ndk::SharedRefBase::make<Led>();
    const std::string name = std::string() + Led::descriptor + "/default";

    if (ledService != nullptr) {
        if(AServiceManager_addService(ledService->asBinder().get(), name.c_str()) != STATUS_OK) {
            ALOGE("Failed to register ILed service");
            return -1;
        }
    } else {
        ALOGE("Failed to get ILed instance");
        return -1;
    }

    ALOGD("ILed service starts to join service pool");
    ABinderProcess_joinThreadPool();

    return EXIT_FAILURE;  // should not reached
}