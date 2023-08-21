#include <arpi/hardware/demoled/1.0/IDemoled.h>
#include <hidl/LegacySupport.h>
#include <hidl/HidlSupport.h>
#include <stdio.h>
#include <unistd.h>
#include <log/log.h>

using arpi::hardware::demoled::V1_0::IDemoled;
using android::status_t;
using android::sp;

int main()
{
	printf("Starting test\n");
	sp<IDemoled> service = IDemoled::getService();
	if ( service == nullptr ) {
		printf("Can't find Demoled service...");
		return -1;
	}
	printf("Get service successfully\n");
	printf("Turn On the LED\n");
	service->turn_led_on();
	sleep(1);
	printf("Get status of LED\n");
	printf("Status: %d\n", int(service->read_led_status()));
	sleep(1);
	printf("Turn Off the LED\n");
	service->turn_led_off();
	sleep(1);
	printf("Status: %d\n", int(service->read_led_status()));
	return 0;
}
