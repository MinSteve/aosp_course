#ifndef __DEMOLED__
#define __DEMOLED__
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

struct demo_led_ctrl {
	const char *demoled_path;
	int (*get_led_status)(struct demo_led_ctrl self);
	void (*turn_on_led)(struct demo_led_ctrl self);
	void (*turn_off_led)(struct demo_led_ctrl self);
	
};

struct demo_led_ctrl demo_led_init();

void demo_led_cleanup(struct demo_led_ctrl *self);

int demo_get_led_status(struct demo_led_ctrl self);
void demo_turn_on_led(struct demo_led_ctrl self);
void demo_turn_off_led(struct demo_led_ctrl self);

#ifdef __cplusplus
}
#endif


#endif
