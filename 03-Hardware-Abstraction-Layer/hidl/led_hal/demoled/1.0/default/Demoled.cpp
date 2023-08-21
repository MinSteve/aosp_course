// FIXME: your file license if you have one

#define LOG_TAG "Demoled"

#include <log/log.h>
#include "Demoled.h"

namespace arpi::hardware::demoled::implementation {

Demoled::Demoled() {
	demo_led = demo_led_init();
}

Demoled::~Demoled() {
	demo_led_cleanup(&demo_led);
}
// Methods from ::arpi::hardware::demoled::V1_0::IDemoled follow.
Return<int32_t> Demoled::read_led_status() {
	int32_t status;

	status = demo_led.get_led_status(demo_led);
	ALOGI("LED status: %d\n", status);

	return status;
}

Return<void> Demoled::turn_led_on() {
	ALOGI("turn_led_on\n");
	demo_led.turn_on_led(demo_led);
	return Void();
}

Return<void> Demoled::turn_led_off() {
	ALOGI("turn_led_off\n");
	demo_led.turn_off_led(demo_led);
	return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//IDemoled* HIDL_FETCH_IDemoled(const char* /* name */) {
    //return new Demoled();
//}
//
}  // namespace arpi::hardware::demoled::implementation
