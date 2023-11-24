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
        int32_t line;
        led_dev >> line;
        ALOGD("Led service: getLed: %d", line);
        *_aidl_return =  line;
    } else {
        ALOGE("getLed: can not open /sys/devices/platform/demo_led/demo_led");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Led::setLed(int32_t in_status) {
    std::ofstream led_dev;
    led_dev.open ("/sys/devices/platform/demo_led/demo_led");
    if(led_dev.good()) {
        led_dev << in_status;
        ALOGD("Invcase service: putChars: %d", in_status);
    } else {
        ALOGE("setLed: can not open /sys/devices/platform/demo_led/demo_led");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    return ndk::ScopedAStatus::ok();
}

}  // namespace led
}  // namespace hardware
}  // namespace cocktail
}  // namespace vendor
}  // namespace aidl