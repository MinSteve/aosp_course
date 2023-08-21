#define LOG_TAG "arpi.hardware.demoled@1.0-service"

#include <hidl/HidlSupport.h>
#include <hidl/HidlTransportSupport.h>

#include "Demoled.h"

using ::android::OK;
using ::android::sp;
using ::android::hardware::configureRpcThreadpool;
using ::android::hardware::joinRpcThreadpool;
using ::arpi::hardware::demoled::V1_0::IDemoled;
using ::arpi::hardware::demoled::implementation::Demoled;

int main(int /* argc */, char* /* argv */ []) {
	sp<IDemoled> demoled = new Demoled;
	configureRpcThreadpool(1, true /* will join */);
	if (demoled->registerAsService() != OK) {
		ALOGE("Could not register service.");
		return 1;
	}
	joinRpcThreadpool();

	ALOGE("Service exited!");
	return 1;
}
