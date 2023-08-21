#include <unistd.h>
#include "demoled_ctrl.h"

struct DemoLed {
	DemoLed()
	{
		demo_led = demo_led_init();
	}
	~DemoLed()
	{
		demo_led_cleanup(&demo_led);
	}
	int read_led_stat()
	{
		int status;
		status = demo_led.get_led_status(demo_led);
		return status;
	}
	void turn_led_on()
	{
		demo_led.turn_on_led(demo_led);
	}
	void turn_led_off()
	{
		demo_led.turn_off_led(demo_led);
	}
	private:
		struct demo_led_ctrl demo_led;
};

int main()
{
	int stat;
	DemoLed *led = new DemoLed();
	
	printf("Turn on the LED\n");
	led->turn_led_on();
	stat = led->read_led_stat();
	printf("Status: %d\n", stat);
	sleep(1);
	printf("Turn off the LED\n");
	led->turn_led_off();
	stat = led->read_led_stat();
	printf("Status: %d\n", stat);
	return 0;
}
