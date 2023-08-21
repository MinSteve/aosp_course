// FIXME: your file license if you have one

#pragma once

#include <arpi/hardware/demoled/1.0/IDemoled.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include "demoled_ctrl.h"

namespace arpi::hardware::demoled::implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Demoled : public V1_0::IDemoled {
	Demoled();
	// Methods from ::arpi::hardware::demoled::V1_0::IDemoled follow.
	Return<int32_t> read_led_status() override;
	Return<void> turn_led_on() override;
	Return<void> turn_led_off() override;
	~Demoled();

	// Methods from ::android::hidl::base::V1_0::IBase follow.
	private:
		struct demo_led_ctrl demo_led;

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" IDemoled* HIDL_FETCH_IDemoled(const char* name);

}  // namespace arpi::hardware::demoled::implementation
