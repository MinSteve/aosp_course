/*
 * Copyright (C) 2023 Dung Tran Anh
 */

#pragma once

#include <aidl/vendor/cocktail/hardware/led/BnLed.h>

namespace aidl {
namespace vendor {
namespace cocktail {
namespace hardware {
namespace led {

class Led : public BnLed {
    public:
        ndk::ScopedAStatus getLed(int32_t* _aidl_return);
        ndk::ScopedAStatus setLed(int32_t in_status);
};

}  // namespace led
}  // namespace hardware
}  // namespace cocktail
}  // namespace vendor
}  // namespace aidl
