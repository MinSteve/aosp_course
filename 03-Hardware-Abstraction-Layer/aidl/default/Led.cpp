/*
 * Copyright (C) 2023 Dung Tran Anh
 */

#define LOG_TAG "Led"

#include <utils/Log.h>
#include <iostream>
#include <fstream>
#include "Led.h"

namespace aidl {
namespace vendor {
namespace cocktail {
namespace hardware {
namespace led {

ndk::ScopedAStatus Led::getLed(int32_t* _aidl_return) {
    std::ifstream led_dev;
    led_dev.open("/sys/devices/platform/demo_led/demo_led");
    if(led_dev.good()) {
        int32_t value;
        led_dev >> value;
        ALOGD("Led service: getLed: %d", value);
        *_aidl_return =  value;
    } else {
        ALOGE("getLed: can not open /sys/devices/platform/demo_led/demo_led");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Led::setLed(int32_t in_status) {
    std::ofstream led_dev;
    led_dev.open("/sys/devices/platform/demo_led/demo_led");
    if(led_dev.good()) {
        led_dev << in_status;
        ALOGD("Led service: setLed: %d", in_status);
    } else {
        ALOGE("setLed: Can not open /sys/devices/platform/demo_led/demo_led");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    return ndk::ScopedAStatus::ok();
}

}  // namespace led
}  // namespace hardware
}  // namespace cocktail
}  // namespace vendor
}  // namespace aidl