#include <stdio.h>
#include <unistd.h>

#include "demoled_ctrl.h"

int main()
{
	int stat;

	struct demo_led_ctrl led;
	printf("Start the test\n");
	led = demo_led_init();

	stat = led.get_led_status(led);
	printf("led status: %d\n", stat);
	sleep(2);
	printf("Turn on the led\n");
	led.turn_on_led(led);
	stat = led.get_led_status(led);
	printf("led status: %d\n", stat);
	sleep(2);
	printf("Turn off the led\n");
	led.turn_off_led(led);
	printf("led status: %d\n", stat);

	demo_led_cleanup(&led);

	return 0;
}
